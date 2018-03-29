# Luna

## What is Luna?
* Luna is a simple game engine programmed in C++ and Lua which lets you create sketches and games in Lua

## Features
* Program in Lua, easy for non-programmers, kids, etc.
* Multiple options for programming: Simple or Object oriented
* Tutorials avaliable in multiple languages (soon)
* Cross-platform: Windows, Ubuntu/Debian and MacOS builds are released for each version

## Tutorials
* Check out the wiki [here](https://github.com/XyronLabs/Luna/wiki)

---

## Building Luna yourself (Linux and macOS)

### Building Luna

- You can install `libsfml-dev` in some distributions like Debian/Ubuntu in order not to build SFML yourself

- Debug build: `make d`
- Release build: `make r`
- Standalone build: `make s`
    - Standalone is the same as release but the resources folder must be in the same directory as the executable itself, this is useful for portable installations

### Building Lua
1. Make sure you have `curl` and `libreadline-dev` installed in your system
2. Open a terminal in the scripts folder
3. `chmod +x` the script called ```lua_setup.sh```
4. Execute the script `./lua_setup.sh`

### Building SFML
- Refer to [SFML and Linux](https://www.sfml-dev.org/tutorials/2.4/start-linux.php)