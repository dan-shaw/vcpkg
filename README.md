# vcpkg: the C/C++ package manager

[![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-Windows-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=9&branchName=master)

* Github: [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg)
* Slack: [https://cpplang.now.sh/](https://cpplang.now.sh/), the #vcpkg channel
* Docs: [https://github.com/microsoft/vcpkg/blob/master/docs/index.md](https://github.com/microsoft/vcpkg/blob/master/docs/index.md)

| Triplet  | Supported libraries |
| ------------- | ------------- |
| x64-windows  | 1151  |
| x86-windows  | 1136  |
| x64-windows-static  | 1061  |
| x64-linux  | 980  |
| x64-osx  | 939  |
| arm64-windows  | 766  |
| x64-uwp  | 624  |
| arm-uwp  | 594  |

## Install a library
Prerequisites:
- Windows 10, 8.1, 7, Linux, or MacOS
- Visual Studio 2015 Update 3 or newer (on Windows)

Clone the repo:
```
> git clone https://github.com/Microsoft/vcpkg.git
> cd vcpkg
```

Run the bootstrap script
* Windows 
```
.\bootstrap-vcpkg.bat
```
* Linux or MacOS
```
./bootstrap-vcpkg.sh
```

Install any package with
```
./vcpkg install zlib:x64-windows
```

## Using the installed package(s)
All installed libraries are immediately ready to be `#include`'d and used in your project without additional configuration. Libraries are located in the `installed/` folder. You just need to add the libraries to the right paths:

* For CMake projects:

```
cmake ../my/project -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
```
Projects configured with the toolchain file will have the appropriate vcpkg folders added to the CMake search paths. This makes all libraries available to be found through `find_package()`, `find_path()`, and `find_library()`.

* For Visual Studio/MSBuild projects:

Then, to hook up user-wide integration, run (note: requires admin on first use)
```
./vcpkg integrate install
```

For more information, see the documentation on [integration](docs/users/integration.md).

## Available Commands

For short description of available commands, run `vcpkg help`.
```
Commands:
  vcpkg search [pat]              Search for packages available to be built
  vcpkg install <pkg>...          Install a package
  vcpkg remove <pkg>...           Uninstall a package
  vcpkg list                      List installed packages
  vcpkg update                    Display list of packages for updating
  vcpkg integrate install         Make installed packages available user-wide. Requires admin privileges on first use
  vcpkg integrate project         Generate a referencing nuget package for individual VS project use
  ...
  vcpkg export <pkg>... [opt]...  Exports a package
  vcpkg import <pkg>              Import a pre-built library
  ...
Options:
  --triplet <t>                   Specify the target architecture triplet
                                  (default: %%VCPKG_DEFAULT_TRIPLET%%, see 'vcpkg help triplet')

  --overlay-ports=<path>          Specify directories to be used when searching for ports

  --overlay-triplets=<path>       Specify directories containing triplets files

```

## Contributing
Vcpkg is built with your contributions. Here are some ways you can contribute:

* [Submit Issues](https://github.com/Microsoft/vcpkg/issues) in vcpkg or existing packages
* [Submit Fixes and New Packages](https://github.com/Microsoft/vcpkg/pulls)

Please refer to our [Contribution guidelines](CONTRIBUTING.md) for more details.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

## License

Code licensed under the [MIT License](LICENSE.txt).
