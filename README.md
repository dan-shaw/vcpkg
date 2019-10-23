# vcpkg: the C++ package manager

[![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-Windows-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=9&branchName=master)

* Github: [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg)
* Slack: [https://cpplang.now.sh/](https://cpplang.now.sh/), the #vcpkg channel
* Docs: [https://github.com/microsoft/vcpkg/blob/master/docs/index.md](https://github.com/microsoft/vcpkg/blob/master/docs/index.md)

## Overview
Vcpkg helps you manage C and C++ libraries on Windows, Linux and MacOS. This tool and ecosystem are constantly evolving; your involvement is vital to its success!

## Quick Start
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
PS> .\bootstrap-vcpkg.bat
```
* Linux or MacOS
```
Linux:~/$ ./bootstrap-vcpkg.sh
```

Install any packages with
```
./vcpkg install zlib
```

## Using the installed package(s)
All installed libraries are immediately ready to be `#include`'d and used in your project without additional configuration. Libraries are located in the `installed/` folder. You just need to add the libraries to the right paths:

* For CMake projects:

```
cmake ../my/project -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
```

* For Visual Studio/MSBuild projects:

Then, to hook up user-wide integration, run (note: requires admin on first use)
```
PS> .\vcpkg integrate install
Linux:~/$ ./vcpkg integrate install
```

See the documentation on [integration](docs/users/integration.md).

For more information, see our [using a package](docs/examples/installing-and-using-packages.md) example for the specifics. If your library is not present in vcpkg catalog, you can open an [issue on the GitHub repo](https://github.com/microsoft/vcpkg/issues) where the dev team and the community can see it and potentially create the port file for this library.

## Available Commands

For short description of available commands, run `vcpkg help`.
```
Commands:
  vcpkg search [pat]              Search for packages available to be built
  vcpkg install <pkg>...          Install a package
  vcpkg remove <pkg>...           Uninstall a package
  vcpkg remove --outdated         Uninstall all out-of-date packages
  vcpkg list                      List installed packages
  vcpkg update                    Display list of packages for updating
  vcpkg upgrade                   Rebuild all outdated packages
  vcpkg x-history <pkg>           Shows the history of CONTROL versions of a package
  vcpkg hash <file> [alg]         Hash a file by specific algorithm, default SHA512
  vcpkg help topics               Display the list of help topics
  vcpkg help <topic>              Display help for a specific topic

  vcpkg integrate install         Make installed packages available user-wide. Requires admin privileges on first use
  vcpkg integrate remove          Remove user-wide integration
  vcpkg integrate project         Generate a referencing nuget package for individual VS project use
  vcpkg integrate powershell      Enable PowerShell tab-completion

  vcpkg export <pkg>... [opt]...  Exports a package
  vcpkg edit <pkg>                Open up a port for editing (uses %%EDITOR%%, default 'code')
  vcpkg import <pkg>              Import a pre-built library
  vcpkg create <pkg> <url>
             [archivename]        Create a new package
  vcpkg owns <pat>                Search for files in installed packages
  vcpkg depend-info [pkg]...      Display a list of dependencies for packages
  vcpkg env                       Creates a clean shell environment for development or compiling.
  vcpkg version                   Display version information
  vcpkg contact                   Display contact information to send feedback

Options:
  --triplet <t>                   Specify the target architecture triplet
                                  (default: %%VCPKG_DEFAULT_TRIPLET%%, see 'vcpkg help triplet')

  --overlay-ports=<path>          Specify directories to be used when searching for ports

  --overlay-triplets=<path>       Specify directories containing triplets files

  --vcpkg-root <path>             Specify the vcpkg root directory
                                  (default: %%VCPKG_ROOT%%)

  --x-scripts-root=<path>             (Experimental) Specify the scripts root directory

  @response_file                  Specify a response file to provide additional parameters
```

## Examples
See the [documentation](docs/index.md) for specific walkthroughs, including [installing and using a package](docs/examples/installing-and-using-packages.md), [adding a new package from a zipfile](docs/examples/packaging-zipfiles.md), and [adding a new package from a GitHub repo](docs/examples/packaging-github-repos.md).

Our docs are now also available online at ReadTheDocs: <https://vcpkg.readthedocs.io/>!

See a 4 minute [video demo](https://www.youtube.com/watch?v=y41WFKbQFTw).

## Contributing
Vcpkg is built with your contributions. Here are some ways you can contribute:

* [Submit Issues](https://github.com/Microsoft/vcpkg/issues) in vcpkg or existing packages
* [Submit Fixes and New Packages](https://github.com/Microsoft/vcpkg/pulls)

Please refer to our [Contribution guidelines](CONTRIBUTING.md) for more details.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

## License

Code licensed under the [MIT License](LICENSE.txt).
