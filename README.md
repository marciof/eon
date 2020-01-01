# Introduction

A free/libre open source (FLOSS) programming language for interactive use, scripting, and building small to large programs, that aims to be simple, powerful, and practical.

It includes a well-defined specification, a platform-agnostic implementation core, and an interpreter for various operating systems and environments.

# Installation

## Dependencies

### Linux

See `.travis.yml` for:

- `compiler`: List of supported compilers.
- `addons.apt.packages`: List of required packages.

(Tested on Debian 10, both 32-bit and 64-bit.)

### Windows

- [Visual Studio Build Tools](https://www.visualstudio.com/thank-you-downloading-visual-studio/?sku=BuildTools)

(Tested on Windows 10, both 32-bit and 64-bit.)

## Building

1. Create a new directory to store the build artifacts.
2. *Optionally* configure which builds to create. By default it will build a native standalone executable only. Selecting the builds can be done in several different ways using CMake.
  - Command-line:
    1. List options:
      ```
      $ cmake -LH path/to/sources
      ```
    2. Build a native standalone executable only (it's the default):
      ```
      $ cmake -D BUILD_FOR_NATIVE_HOST=ON path/to/sources
      ```
  - TUI:
    ```
    ccmake path/to/sources
    ```
  - GUI:
    ```
    cmake-gui path/to/sources
    ```
3. Invoke the build tool.
  ```
  $ cmake --build .
  ```

# Architecture

- `interpreter/`: Implementation of the language specification.
  - `core/`: Builds an embeddable library with the host-independent core of the implementation and host-dependent hooks.
  - `javascript/`: Builds a standalone executable to compile to JavaScript.
  - `native/`: Builds an embeddable library and a standalone executable to run natively (eg. on Windows).
  - `x86-32/`: Builds a Multiboot-compliant executable to run on an Intel x86 32-bit host.
- `spec/`: Language specification.
- `stdlib/`: Standard library for the interpreter.
