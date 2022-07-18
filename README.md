<p align="center"><img src="https://github.com/JustWhit3/ptc-print/blob/main/img/logo.svg" height=220></p>

<h3 align="center">A C++17 header-only implementation of the Python print function (with new features and personal improvements) </h3>
<p align="center">
  <img title="v0.0" alt="v0.0" src="https://img.shields.io/badge/version-v0.0-informational?style=flat-square">
  <img title="MIT License" alt="license" src="https://img.shields.io/badge/license-MIT-informational?style=flat-square">
	<img title="C++17" alt="C++17" src="https://img.shields.io/badge/c++-17-informational?style=flat-square"><br/>
	<img title="Code size" alt="code size" src="https://img.shields.io/github/languages/code-size/JustWhit3/ptc-print?color=red">
	<img title="Repo size" alt="repo size" src="https://img.shields.io/github/repo-size/JustWhit3/ptc-print?color=red">
	<img title="Lines of code" alt="total lines" src="https://img.shields.io/tokei/lines/github/JustWhit3/ptc-print?color=red"></br>
  <img title="codeq" alt="codeq" src="https://github.com/JustWhit3/ptc-print/actions/workflows/codeql-analysis.yml/badge.svg">
  <img title="doc" alt="doc" src="https://github.com/JustWhit3/ptc-print/actions/workflows/DocGenerator.yml/badge.svg">
</p>

***

## Table of contents

- [Introduction](#introduction)
- [Examples](#examples)
- [Install and use](#install-and-use)
- [Compile and run tests](#compile-and-run-tests)
- [Comparison with other libraries](#comparison-with-other-libraries)
- [Todo](#todo)
- [Credits](#credits)
  - [Project leaders](#project-leaders)
  - [Other contributors](#other-contributors)

## Introduction

`ptc::print` (*py-to-cpp print*) is a C++17 printing object inspired by the Python [`print`](https://realpython.com/python-print/) function, providing you a most comfortable way to print messages and logs in the output stream.

It is constructed through the [`__print__`](https://justwhit3.github.io/ptc-print/classptc_1_1____print____.html) functor which is a fully *type-* and *thread-safe* class with *automatic memory management*, implemented through an [header-only](https://github.com/JustWhit3/ptc-print/blob/main/ptc/print.hpp) library, with minimal and indispensable [dependencies](#install-and-use).

If you want to contribute to the repository, please read [this](https://github.com/JustWhit3/ptc-print/blob/main/CONTRIBUTING.md) file before.

Code documentation is generated using [*Doxygen*](https://www.doxygen.nl/manual/starting.html) and can be accessed [here](https://justwhit3.github.io/ptc-print/). Updates and news will be published at [this](https://github.com/JustWhit3/ptc-print/discussions/categories/announcements) discussion page.

The software is and will stay **free**, but if you want to support me with a donation it would be really appreciated!

<a href="https://www.buymeacoffee.com/JustWhit33" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="41" width="174"></a>

Supported operating systems are:

- **Linux**
  - *Ubuntu* (tested)
- **Windows** (release 10 or higher)
  - *Cygwin64* (tested)
  - *MSYS2* (tested)
  - *MinGW* (tested)
  - *WSL* (tested)
- **MacOS**

## Examples

To normally print messages to stdout:

```C++
#include <ptc/print.hpp>

int main()
 {
  const char* str = "bye!";

  ptc::print( "Printing to", "stdout!" );
  ptc::print();
  ptc::print( "Here I am", 123, str );
 }
```

```txt
Printing to stdout!

Here I am 123 bye!
```

Print to a different output stream:

```C++
#include <ptc/print.hpp>
#include <iostream>
#include <sstream>

int main()
 {
  // stderr
  ptc::print( std::cerr, "I am the", "stderr." );

  // ostringstream
  std::ostringstream strout;
  ptc::print( strout, "Printing", "with in an", "std::ostringstream" );
  ptc::print( strout.str() );
 }
```

```txt
I am the stderr!

Printing with in an std::ostringstream.
```

Or directly write into a file:

```C++
#include <ptc/print.hpp>
#include <fstream>

int main()
 {
  std::ofstream stream( "file.txt" );
  ptc::print( stream, "You can also write in a file! ", 1, 2, 3, 4.5, 7 );
  stream.close();
 }
```

To change the end-line character / instruction:

```C++
#include <ptc/print.hpp>

int main()
 {
  // Change end character
  ptc::print.setEnd( " " );
  ptc::print( "This is a" );
  ptc::print( "single row." );

  // Restore previous configuration
  ptc::print.setEnd( '\n' );
  ptc::print( "These are" );
  ptc::print( "two rows." );
 }
```

```txt
This is a single row.

These are
two rows.
```

To change the separator character / instruction:

```C++
#include <ptc/print.hpp>

int main()
 {
  ptc::print.setSep( "*" );
  ptc::print( "Changing", "the", "sep." );
 }
```

```txt
Changing*the*sep.
```

To allow output stream flush (false by default) use:

```C++
ptc::print.setFlush( true );
```

## Install and use

Steps:

1) Download one of the repository releases.
2) Unzip the downloaded directory and `cd` into it.
3) Copy the **ptc** folder in one of your projects or in a specific path or install into the system with this command:

```bash
./install.sh
```

Prerequisites are minimal and are automatically installed with the `install.sh` script. They are:

- g++ (like *gcc* or *clang*) compiler.
- C++17 standard.

4) Include the header into your project:

```C++
#include <ptc/print.hpp>
```

5) Compile without any extra flag and run:

```bash
g++ -std=c++17 program.cpp
./a.out
```

## Compile and run tests

Different tests are performed. To check them you need some prerequisites:

- [Valgrind](https://valgrind.org/).
- [doctest](https://github.com/onqtam/doctest) for testing.

They are installed in the second step of the installation through the `install.sh` script. Before running test codes you need to compile them:

```bash
cd tests
make
```

To run **unit tests**:

```bash
./bin/unit_tests
```

To run **system tests**:

```bash
./bin/system_tests
```

To run **include_tests**:

```bash
./include_tests.sh
```

To check the automatic memory management through *Memcheck*:

```bash
./valgrind.sh memcheck ./bin/system_tests
```

To check thread safety through *Helgrind*:

```bash
./valgrind.sh helgrind ./bin/system_tests
```

## Comparison with other libraries

Empty for the moment (work in progress).

## Todo

- Add support to the containers printing:

```C++
std::vector<int> v{1, 10, 100};
ptc::print(v);
```

Output:

```shell
[1,10,100]
```

- Enable string concatenation within the `ptc::print` object:

```C++
ptc::print("Supporting" + "this.");
```

Output:

```shell
Supporting this.
```

- Create a method to format the output given from the print function:

```C++
ptc::print("I would {}", "to print {} {}").format( "like", "this", 123 );
```

Output:

```shell
I would like to print this 123
```

## Credits

### Project leaders

<table>
  <tr>
    <td align="center"><a href="https://justwhit3.github.io/"><img src="https://avatars.githubusercontent.com/u/48323961?v=4" width="100px;" alt=""/><br /><sub><b>Gianluca Bianco</b></sub></a></td>
  </tr>
</table>

### Other contributors

Empty for the moment.

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->

<!-- ALL-CONTRIBUTORS-LIST:END -->