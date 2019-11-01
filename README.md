# vcpkg: the C/C++ package manager

Vcpkg helps you manage C and C++ libraries on Windows, Linux and MacOS. This tool and ecosystem are constantly evolving; your involvement is vital to its success!

For short description of available commands, run `vcpkg help`.

* Github: [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg)
* Slack: [https://cpplang.now.sh/](https://cpplang.now.sh/), the #vcpkg channel
* Docs: [Documentation](docs/index.md)

## Features:
* __Portable:__ Supports Windows, Linux, MacOS. 
* __Extensive library catalogue:__ Over 1200 libraries tested and supported and with more added every day. (See our monthly [releases](https://github.com/microsoft/vcpkg/releases) to learn which libraries have been added recently. You can also checkout older versions of libraries.
* __Avoid C++ dependency problems:__ vcpkg was designed so that libraries would work together out of the box. Worry less about dependency resolution, broken diamonds, ODR, and other library resolution problems.
* __Target-Agnostic:__ Use your own or community-supported toolchains to build for targets such as Android, iOS, FreeBSD. You can also package for various buildsystems such as Meson and Make. 
* __Active GitHub community:__ Our active GitHub community adds and updates libraries daily. Open an issue or ask a question on Slack!

| Windows (x86, x64, arm, uwp)  | MacOS | Linux |
| ------------- | ------------- | ------------- |
| [![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-Windows-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=9&branchName=master)  | [![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-osx-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=11&branchName=master) | [![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-Linux-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=6&branchName=master) |

## Quick Start
Prerequisites:
- Windows 10, 8.1, 7, Linux, or MacOS
- Visual Studio 2015 Update 3 or newer (on Windows)

To get started:
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

To set up user-wide IDE [integration](docs/users/integration.md) (for Visual Studio, and other IDEs), run (note: requires admin on first use)
```
./vcpkg integrate install
```

Install any packages with
```
./vcpkg install sdl2 curl
```
If you want a library to target a specific architecture/triplet such as `x64-windows`, append the triplet to the library name
```
./vcpkg install curl:x64-windows
```
See the list of community supported [triplets](triplets/)

The best way to use installed libraries with CMake is via the toolchain file `scripts\buildsystems\vcpkg.cmake`. To use this file, you simply need to add it onto your CMake command line as `-DCMAKE_TOOLCHAIN_FILE=[vcpkg root]\scripts\buildsystems\vcpkg.cmake`.

```
cmake path/to/project -DCMAKE_TOOLCHAIN_FILE=[vcpkg root]/scripts/buildsystems/vcpkg.cmake
```

In Visual Studio, you can create a New Project (or open an existing one). All installed libraries are immediately ready to be `#include`'d and used in your project without additional configuration.

For more information, see our [using a package](docs/examples/installing-and-using-packages.md) example for the specifics. If your library is not present in vcpkg catalog, you can open an [issue on the GitHub repo](https://github.com/microsoft/vcpkg/issues) where the dev team and the community can see it and potentially create the port file for this library.

Additional notes on macOS and Linux support can be found in the [official announcement](https://blogs.msdn.microsoft.com/vcblog/2018/04/24/announcing-a-single-c-library-manager-for-linux-macos-and-windows-vcpkg/).

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
