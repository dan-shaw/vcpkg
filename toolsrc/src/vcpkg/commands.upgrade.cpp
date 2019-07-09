#include "pch.h"

#include <vcpkg/commands.h>
#include <vcpkg/dependencies.h>
#include <vcpkg/globalstate.h>
#include <vcpkg/help.h>
#include <vcpkg/input.h>
#include <vcpkg/install.h>
#include <vcpkg/statusparagraphs.h>
#include <vcpkg/update.h>
#include <vcpkg/vcpkglib.h>

#include <vcpkg/base/system.print.h>
#include <vcpkg/base/util.h>

namespace vcpkg::Commands::Upgrade
{
    using Install::KeepGoing;
    using Install::to_keep_going;

    static constexpr StringLiteral OPTION_NO_DRY_RUN = "--no-dry-run";
    static constexpr StringLiteral OPTION_KEEP_GOING = "--keep-going";

    static constexpr std::array<CommandSwitch, 2> INSTALL_SWITCHES = {{
        {OPTION_NO_DRY_RUN, "Actually upgrade"},
        {OPTION_KEEP_GOING, "Continue installing packages on failure"},
    }};

    const CommandStructure COMMAND_STRUCTURE = {
        Help::create_example_string("upgrade --no-dry-run"),
        0,
        SIZE_MAX,
        {INSTALL_SWITCHES, {}},
        nullptr,
    };

    void perform_and_exit(const VcpkgCmdArguments& args,
                          const VcpkgPaths& paths,
                          const VcpkgPaths& upgrade_paths,
                          const Triplet& default_triplet)
    {
        const ParsedArguments options = args.parse_arguments(COMMAND_STRUCTURE);

        const bool no_dry_run = Util::Sets::contains(options.switches, OPTION_NO_DRY_RUN);
        const KeepGoing keep_going = to_keep_going(Util::Sets::contains(options.switches, OPTION_KEEP_GOING));

        StatusParagraphs status_db = database_load_check(paths);

        // Load ports from ports dirs
        Dependencies::PathsPortFileProvider provider(paths, args.overlay_ports.get());
        Dependencies::PackageGraph graph(provider, status_db);

        // input sanitization
        const std::vector<PackageSpec> specs = Util::fmap(args.command_arguments, [&](auto&& arg) {
            return Input::check_and_get_package_spec(std::string(arg), default_triplet, COMMAND_STRUCTURE.example_text);
        });

        for (auto&& spec : specs)
        {
            Input::check_triplet(spec.triplet(), paths);
        }

        if (specs.empty())
        {
            // If no packages specified, upgrade all outdated packages.
            auto outdated_packages = Update::find_outdated_packages(provider, status_db);

            if (outdated_packages.empty())
            {
                System::print2("All installed packages are up-to-date with the local portfiles.\n");
                Checks::exit_success(VCPKG_LINE_INFO);
            }

            for (auto&& outdated_package : outdated_packages)
                graph.upgrade(outdated_package.spec);
        }
        else
        {
            std::vector<PackageSpec> not_installed;
            std::vector<PackageSpec> no_portfile;
            std::vector<PackageSpec> to_upgrade;
            std::vector<PackageSpec> up_to_date;

            for (auto&& spec : specs)
            {
                auto it = status_db.find_installed(spec);
                if (it == status_db.end())
                {
                    not_installed.push_back(spec);
                }

                auto maybe_scfl = provider.get_control_file(spec.name());
                if (auto p_scfl = maybe_scfl.get())
                {
                    if (it != status_db.end())
                    {
                        if (p_scfl->source_control_file->core_paragraph->version != (*it)->package.version)
                        {
                            to_upgrade.push_back(spec);
                        }
                        else
                        {
                            up_to_date.push_back(spec);
                        }
                    }
                }
                else
                {
                    no_portfile.push_back(spec);
                }
            }

            Util::sort(not_installed);
            Util::sort(no_portfile);
            Util::sort(up_to_date);
            Util::sort(to_upgrade);

            if (!up_to_date.empty())
            {
                System::print2(System::Color::success, "The following packages are up-to-date:\n");
                System::print2(Strings::join("",
                                             up_to_date,
                                             [](const PackageSpec& spec) { return "    " + spec.to_string() + "\n"; }),
                               '\n');
            }

            if (!not_installed.empty())
            {
                System::print2(System::Color::error, "The following packages are not installed:\n");
                System::print2(Strings::join("",
                                             not_installed,
                                             [](const PackageSpec& spec) { return "    " + spec.to_string() + "\n"; }),
                               '\n');
            }

            if (!no_portfile.empty())
            {
                System::print2(System::Color::error, "The following packages do not have a valid portfile:\n");
                System::print2(Strings::join("",
                                             no_portfile,
                                             [](const PackageSpec& spec) { return "    " + spec.to_string() + "\n"; }),
                               '\n');
            }

            Checks::check_exit(VCPKG_LINE_INFO, not_installed.empty() && no_portfile.empty());

            if (to_upgrade.empty()) Checks::exit_success(VCPKG_LINE_INFO);

            for (auto&& spec : to_upgrade)
                graph.upgrade(spec);
        }

        auto plan = graph.serialize();

        Checks::check_exit(VCPKG_LINE_INFO, !plan.empty());

        const Build::BuildPackageOptions install_plan_options = {
            Build::UseHeadVersion::NO,
            Build::AllowDownloads::YES,
            Build::CleanBuildtrees::NO,
            Build::CleanPackages::NO,
            Build::CleanDownloads::NO,
            Build::DownloadTool::BUILT_IN,
            GlobalState::g_binary_caching ? Build::BinaryCaching::YES : Build::BinaryCaching::NO,
            Build::FailOnTombstone::NO,
        };

        // Set build settings for all install actions
        for (auto&& action : plan)
        {
            if (auto p_install = action.install_action.get())
            {
                p_install->build_options = install_plan_options;
            }
        }

        Dependencies::print_plan(plan, true, paths.ports);

        if (!no_dry_run)
        {
            System::print2(System::Color::warning,
                           "If you are sure you want to rebuild the above packages, run this command with the "
                           "--no-dry-run option.\n");
            Checks::exit_fail(VCPKG_LINE_INFO);
        }

        auto& fs = upgrade_paths.get_filesystem();
        std::error_code ec;

        StatusParagraphs status_db_upgrade = database_load_check(upgrade_paths);

        auto installed_packages = get_installed_ports(status_db);
        for (auto&& installed_package : installed_packages)
        {
            // copy packages that are not removed
            bool copy_package = true;
            for (auto&& action : plan)
            {
                if (auto p_remove = action.remove_action.get())
                {
                    if (installed_package.spec() == p_remove->spec)
                    {
                        copy_package = false;
                        break;
                    }
                }
            }

            if (copy_package)
            {
                auto maybe_lines = fs.read_lines(paths.listfile_path(installed_package.core->package));

                if (const auto lines = maybe_lines.get())
                {
                    for (auto&& suffix : *lines)
                    {
                        if (!suffix.empty() && suffix.back() == '\r') suffix.pop_back();

                        auto host = paths.installed / suffix;
                        auto target = upgrade_paths.installed / suffix;

                        const auto status = fs.symlink_status(host, ec);
                        if (ec)
                        {
                            System::print2(
                                System::Color::error, "failed: status(", host.u8string(), "): ", ec.message(), "\n");
                            continue;
                        }

                        if (fs::is_directory(status))
                        {
                            fs.create_directory(target, ec);
                        }
                        else if (fs::is_regular_file(status) || fs::is_symlink(status))
                        {
                            fs.copy(host, target, fs::copy_options::overwrite_existing);
                        }
                        else if (!fs::stdfs::exists(status))
                        {
                            System::printf(System::Color::warning, "Warning: %s: file not found\n", host.u8string());
                        }
                        else
                        {
                            System::printf(
                                System::Color::warning, "Warning: %s: cannot handle file type\n", host.u8string());
                        }
                    }
                }

                PackageSpec spec = installed_package.spec();

                auto installed_view = status_db.find_all_installed(spec).value_or_exit(VCPKG_LINE_INFO);

                fs.copy(paths.listfile_path(installed_view.core->package),
                        upgrade_paths.listfile_path(installed_view.core->package),
                        fs::copy_options::overwrite_existing);

                write_update(upgrade_paths, *installed_view.core);
                status_db_upgrade.insert(std::make_unique<StatusParagraph>(std::move(*installed_view.core)));
                for (auto&& feature_status_pgh : installed_view.features)
                {
                    write_update(upgrade_paths, *feature_status_pgh);
                    status_db_upgrade.insert(std::make_unique<StatusParagraph>(std::move(*feature_status_pgh)));
                }
            }
        }

        bool skip_remove_plan = true;
        const Install::InstallSummary summary =
            Install::perform(plan, keep_going, upgrade_paths, status_db_upgrade, skip_remove_plan);

        System::print2("\nTotal elapsed time: ", summary.total_elapsed_time, "\n\n");

        if (keep_going == KeepGoing::YES)
        {
            summary.print();
        }

        if (ec)
        {
            Checks::exit_with_message(VCPKG_LINE_INFO,
                                      "error updating installed directory %s: %s\n",
                                      paths.installed.u8string(),
                                      ec.message());
        }

        fs.rename(paths.installed, paths.root / "installed-old", VCPKG_LINE_INFO);
        fs.rename(upgrade_paths.installed, paths.installed, VCPKG_LINE_INFO);
        fs.remove_all(paths.root / "installed-old", ec);

        Checks::exit_success(VCPKG_LINE_INFO);
    }
}
