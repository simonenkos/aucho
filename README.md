# Auction House Application

## Build information

In order to build the project it requires [CMake](https://cmake.org/) and [Conan](https://conan.io/).
For Visual Studio 2019 a [CMake plugin](https://learn.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170) can be used.

By default, CMake configuration can identify `OS`, `compiler` and `build type` and install dependencies using Conan and profiles that are considering these parameters.
Please note that this project introduce a number of profiles in order to get a proper version of a dependency. It might be possible that other build environment might require changes in these profiles.

## Implementation details

Current implementation build on top of Boost.ASIO with coroutines support in order to serve client requests asynchronously.
There is no support for data storage that would allow to keep application state outside running cycle.

Application supports following set of commands that can be sent using raw sockets on port 55555:
```commandline
Commands description:
info       : show commands description to use on Auction House
account    : open account or create a new one; usage: account <name>
buy        : buy an item that was put on sale; usage: buy <item>
deposit    : deposit fund or item to account; usage: deposit fund <amount> | deposit item <name>
list       : list items on sale; usage: list
sell       : sell an item deposited on account; usage: sell <item> <price>
status     : report status of the account including deposited funds and items; usage: status
withdraw   : withdraw fund or item from account; usage: withdraw fund <amount> | withdraw item <name>
```