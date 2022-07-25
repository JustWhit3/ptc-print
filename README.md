<p align="center"><img src="https://github.com/JustWhit3/ptc-print/blob/main/img/logo.svg" height=220></p>

<h3 align="center">A C++17 header-only library for custom printing to the output stream (inspired by the Python print function) </h3>
<p align="center">
  <img title="v0.1" alt="v0.1" src="https://img.shields.io/badge/version-v0.1-informational?style=flat-square">
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
  - [Standard cases](#standard-cases)
  - [Printing with ANSI escape sequences](#printing-with-ansi-escape-sequences)
  - [Printing non-standard types](#printing-non-standard-types)
- [Install and use](#install-and-use)
- [Tests](#compile-and-run-tests)
- [Comparison with other libraries](#comparison-with-other-libraries)
  - [Benchmarking](#benchmarking)
- [Todo](#todo)
- [Credits](#credits)
  - [Project leaders](#project-leaders)
  - [Other contributors](#other-contributors)

## Introduction

`ptc::print` (*py-to-cpp print*) is a C++17 printing object inspired by the Python [`print`](https://realpython.com/python-print/) function, which provides you a most comfortable way to print messages and logs to the output stream.

It is constructed through the [`__print__`](https://justwhit3.github.io/ptc-print/classptc_1_1____print____.html) functor, which is a fully *type-* and *thread-safe* class with *automatic memory management*, implemented through an [header-only](https://github.com/JustWhit3/ptc-print/blob/main/ptc/print.hpp) library, with minimal and indispensable [dependencies](#install-and-use). It supports also the usage of [ANSI escape sequences](#printing-with-ansi-escape-sequences).

`ptc::print` supports the printing of all the standard types and some non-standard ones (list [here](#printing-non-standard-types)).

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

### Standard cases

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

### Printing with ANSI escape sequences

To color the output stream of a program:

```C++
#include <ptc/print.hpp>

int main()
 {
  ptc::print( "\033[31m", "This is a red bold string", "\033[0m" );
 }
```

<img src="https://github.com/JustWhit3/ptc-print/blob/main/img/red_string.png" width="200">

this holds also for all the other [ANSI escape sequences](https://en.wikipedia.org/wiki/ANSI_escape_code). To better manage them you can use external libraries like [`osmanip`](https://github.com/JustWhit3/osmanip). The stream is automatically reset when the `__print__` [destructor](https://justwhit3.github.io/ptc-print/classptc_1_1____print____.html#a563dbcebb12dcf529c54e6b93831bcf5) is met.

### Printing non-standard types

List of enabled types for printing:

- empty

Empty for the moment.

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

## Tests

Different tests are performed. To check them you need some prerequisites:

- [Valgrind](https://valgrind.org/) for profiling.
- [doctest](https://github.com/onqtam/doctest) for testing.

They are installed in the second step of the installation through the `install.sh` script. Before running test codes you need to compile them:

```bash
cd tests
make
```

To launch all tests simultaneously:

```bash
./all_tests.sh
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
./profiling.sh memcheck ./bin/system_tests
```

To check thread safety through *Helgrind*:

```bash
./profiling.sh helgrind ./bin/system_tests
```

## Comparison with other libraries

### Benchmarking

Benchmarking is performed using the [Google Benchmark](https://github.com/google/benchmark) framework. The script [studies/run.sh](https://github.com/JustWhit3/ptc-print/blob/main/studies/run.sh) is used to generate benchmark data.

Empty for the moment (work in progress).

## Todo

- Add support to all the containers printing (not only `std:.vector`):

```C++
std::vector<int> v{1, 10, 100};
ptc::print(v);
```

```shell
[1,10,100]
```

- Add support to complex numbers printing:

```C++
std::complex<int> no = (1,2)
ptc::print(no);
```

```shell
1 + 2j
```

- Enable string concatenation within the `ptc::print` object:

```C++
ptc::print("Supporting" + "this.");
```

```shell
Supporting this.
```

- Add support to date printing.

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
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/TedLyngmo"><img src="https://avatars.githubusercontent.com/u/2361158?v=4" width="100px;" alt=""/><br /><sub><b>Ted Lyngmo</b></sub></a></td>
  </tr>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->