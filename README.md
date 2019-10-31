# vcpkg: the C/C++ package manager

* Github: [https://github.com/microsoft/vcpkg](https://github.com/microsoft/vcpkg)
* Slack: [https://cpplang.now.sh/](https://cpplang.now.sh/), the #vcpkg channel
* Docs: [https://github.com/microsoft/vcpkg/blob/master/docs/index.md](https://github.com/microsoft/vcpkg/blob/master/docs/index.md)

## Features:
* __Portable:__ Supports Windows, Linux, MacOS. 
* __Extensive library catalogue:__ Over 1200 libraries tested and supported and with more added every day. (See our monthly [releases](https://github.com/microsoft/vcpkg/releases) to learn which libraries have been added recently. You can also checkout older versions of libraries.
* __Avoid C++ dependency problems:__ vcpkg was designed so that libraries would work together out of the box. Worry less about dependency resolution, broken diamonds, ODR, and other library resolution problems.
* __Target-Agnostic:__ Use your own or community-supported toolchains to build for targets such as Android, iOS, FreeBSD. You can also package for various buildsystems such as Meson and Make. 
* __Active GitHub community:__ Our active GitHub community adds and updates libraries daily. Open an issue or ask a question on Slack!

| Windows (x86, x64, arm, uwp)  | MacOS | Linux |
| ------------- | ------------- | ------------- |
| [![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-Windows-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=9&branchName=master)  | [![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-osx-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=11&branchName=master) | [![Build Status](https://dev.azure.com/vcpkg/public/_apis/build/status/vcpkg-Linux-master-CI?branchName=master)](https://dev.azure.com/vcpkg/public/_build/latest?definitionId=6&branchName=master) |

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

To set up user-wide IDE integration (for Visual Studio, and other IDEs), run (note: requires admin on first use)
```
./vcpkg integrate install
```

To use libraries with CMake, add the `CMAKE_TOOLCHAIN_FILE` variable to your CMake command line: 
```
cmake path/to/project -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg-directory>\scripts\buildsystems\vcpkg.cmake
```
Projects configured with the toolchain file will have the appropriate vcpkg folders added to the CMake search paths. Libraries can be found with `find_package()`, `find_path()`, and `find_library()`.

In Visual Studio, you can create a New Project (or open an existing one). All installed libraries are immediately ready to be #include'd and used in your project without additional configuration.

## Install a library
Install the `zlib` and `curl` libraries:
```
./vcpkg install zlib curl
```
If you want `zlib` to target a specific architecture/triplet such as `x64-windows` run `./vcpkg install zlib:x64-windows`

For more information, see the documentation on [integration](docs/users/integration.md).
For an end-to-end example, see the documentation for [installing sqlite](docs/examples/installing-and-using-packages.md).
Otherwise, see the [docs](https://github.com/microsoft/vcpkg/blob/master/docs/index.md) for more examples.

## Contributing
Vcpkg is built with your contributions. Here are some ways you can contribute:

* [Submit Issues](https://github.com/Microsoft/vcpkg/issues) in vcpkg or existing packages
* [Submit Fixes and New Packages](https://github.com/Microsoft/vcpkg/pulls)

Please refer to our [Contribution guidelines](CONTRIBUTING.md) for more details.

This project has adopted the [Microsoft Open Source Code of Conduct](https://opensource.microsoft.com/codeofconduct/). For more information see the [Code of Conduct FAQ](https://opensource.microsoft.com/codeofconduct/faq/) or contact [opencode@microsoft.com](mailto:opencode@microsoft.com) with any additional questions or comments.

## License

Code licensed under the [MIT License](LICENSE.txt).
