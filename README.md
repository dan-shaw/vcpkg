# vcpkg: the C/C++ package manager

* Github: [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg)
* Slack: [https://cpplang.now.sh/](https://cpplang.now.sh/), the #vcpkg channel
* Docs: [https://github.com/microsoft/vcpkg/blob/master/docs/index.md](https://github.com/microsoft/vcpkg/blob/master/docs/index.md)

| Host Platform  | Build Status |
| ------------- | ------------- |
| Windows (x86, x64, arm, uwp)  | [![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-Windows-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=9&branchName=master)  |
| Mac OSX  | [![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-osx-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=11&branchName=master)  |
| Linux | [![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-Linux-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=6&branchName=master) |

## What can vcpkg do?
* __Portable:__ Works on Windows, Linux, Mac OSX. Supports custom target platforms, you just need to provide vcpkg with custom toolchains and triplets to build your libraries for platforms like Android, iOS, FreeBSD.
* __Extensive library catalogue:__ Over 900 libraries for Windows, Linux, and MacOS; and with more being added every day! (See our monthly [releases](https://github.com/microsoft/vcpkg/releases) to learn which libraries have been added recently)
* __Avoid C++ dependency problems:__ vcpkg was designed so that almost all libraries work together out of the box. If you use vcpkg, you won't have to worry too much about dependency resolution, broken diamonds, ODR, and other library resolution problems.
* __Customizable:__ create your own port and triplet repositories and point vcpkg at them using our overlay features. We also support various buildsystems such as Meson and Make.
* __Active GitHub community:__ Our active GitHub community adds and updates libraries daily. Open an issue or ask a question on Slack!
* __Speed:__ We have parallel configure and build on by default. We also have local binary caching so you won't have to rebuild binaries you've already built! 

## Install vcpkg
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

## Install a library
Install a library for the `x64-windows` platform with:
```
./vcpkg install zlib:x64-windows
```

## Using the installed package(s)
All installed libraries are immediately ready to be `#include`'d and used in your project without additional configuration. Libraries are located in the `installed/` folder. You just need to add the libraries to the right paths:

* __For CMake projects:__

```
cmake ../my/project -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
```
Projects configured with the toolchain file will have the appropriate vcpkg folders added to the CMake search paths. This makes all libraries available to be found through `find_package()`, `find_path()`, and `find_library()`.

* __For Visual Studio/MSBuild projects:__

Then, to hook up user-wide integration, run (note: requires admin on first use)
```
./vcpkg integrate install
```

* __Other buildsystems__

The vcpkg directory layout was designed to make it easy to use it with any buildsystem. All installed packages are in the following directories:

| Directory Layout  | File Types |
| ------------- | ------------- |
| `installed\[triplet]\bin` | Shared libraries/DLLs/Shared objects |
| `installed\[triplet]\lib` | Static libraries/lib files |
| `installed\[triplet]\include`. | Header files |
| `installed\[triplet]\tools`. | Additional Binaries/executables/tools built |
| `installed\[triplet]\share` | License, Usage and CMake integration files |


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
