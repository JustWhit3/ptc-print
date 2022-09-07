<p align="center"><img src="https://github.com/JustWhit3/ptc-print/blob/main/img/images/logo.svg" height=220></p>

<h3 align="center">An header-only library for custom printing to the output stream. </h3>
<p align="center">
  <img title="v0.4" alt="v0.4" src="https://img.shields.io/badge/version-v0.4-informational?style=flat-square">
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
  - [Printing user-defined types](#printing-user-defined-types)
  - [Printing using different char types](#printing-using-different-char-types)
- [Install and use](#install-and-use)
  - [Install](#install)
  - [Performance improvements](#performance-improvements)
    - [Runtime](#runtime)
    - [Compilation](#compilation)
- [Tests](#tests)
- [Comparison with other libraries](#comparison-with-other-libraries)
  - [Benchmarking the runtime](#benchmarking-the-runtime)
  - [Benchmarking the runtime with performance improvements](#benchmarking-the-runtime-with-performance-improvements)
  - [Benchmarking the compilation time](#benchmarking-the-compilation-time)
  - [Benchmarking the compilation time with performance improvements](#benchmarking-the-compilation-time-with-performance-improvements)
  - [Executable size](#executable-size)
  - [Advantages](#advantages)
- [Todo](#todo)
  - [New features](#new-features)
  - [Improvements](#improvements)
- [Projects which use this library](#projects-which-use-this-library)
- [Credits](#credits)
  - [Main maintainers](#main-maintainers)
  - [Other contributors](#other-contributors)

## Introduction

`ptc::print` (*py-to-cpp print*) is a C++17 printing object (compiles also with C++20) inspired by the Python [`print`](https://realpython.com/python-print/) function, which provides you a most comfortable way to print messages and logs to the output stream.

It is constructed through the [`Print`](https://justwhit3.github.io/ptc-print/classptc_1_1Print.html) functor, which is a fully *type-* and *thread-safe* class with *automatic memory management*, implemented through an [header-only](https://github.com/JustWhit3/ptc-print/blob/main/ptc/print.hpp) library, with minimal and indispensable [dependencies](#install-and-use). It supports also the usage of [ANSI escape sequences](#printing-with-ansi-escape-sequences).

`ptc::print` supports the printing of all the standard types and some non-standard ones (list [here](#printing-non-standard-types)).

It is possible to choose to print using different char types (`char`, `wchar_t`...). List of supported `char` types can be found [here](#printing-non-standard-types).

If you want to contribute to the repository, please read [this](https://github.com/JustWhit3/ptc-print/blob/main/CONTRIBUTING.md) file before.

If you plan to use this tool in one of your projects please let me know so I can link you to the [Projects which use this library](#projects-which-use-this-library) section.

Code documentation is generated using [*Doxygen*](https://www.doxygen.nl/manual/starting.html) and can be accessed [here](https://justwhit3.github.io/ptc-print/). Updates and news will be published at [this](https://github.com/JustWhit3/ptc-print/discussions/categories/announcements) discussion page.

The software is and will stay **free**, but if you want to support me with a donation it would be really appreciated!

<a href="https://www.buymeacoffee.com/JustWhit33" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="41" width="174"></a>

Supported operating systems:

- **Linux**
  - *Ubuntu* (tested)
- **Windows** (release 10 or higher)
  - *Cygwin64* (tested)
  - *MSYS2* (tested)
  - *MinGW* (tested)
  - *WSL* (tested)
  - *Powershell* (tested)
- **MacOS**

Supported compilers:

- **gcc** (tested)
- **clang** (tested)
- **MSVC** (tested)

## Examples

### Standard cases

To normally **print** messages to stdout:

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

Print to a **different output stream**:

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

To **write into a file**:

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

To change the **end-line** character / instruction:

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

To change the **separator** character / instruction:

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

To allow output stream **flush** (false by default) use:

```C++
ptc::print.setFlush( true );
```

To **initialize a string**:

```C++
#include <ptc/print.hpp>
#include <string>

int main()
 {
  ptc::print.setEnd( "" ); // Avoid "\n" in the string initialization
  std::string msg = ptc::print( ptc::mode::str "I am a", "string." );
  ptc::print( msg );
 }
```

```txt
I am a string.
```

To change the **pattern** among each argument of `ptc::print`:

```C++
#include <ptc/print.hpp>

int main()
 {
  ptc::print.setPattern( "|" );
  ptc::print( "Changing", "the", "pattern" );
 }
```

```txt
|Changing| |the| |pattern|
```

### Printing with ANSI escape sequences

To color the output stream of a program:

```C++
#include <ptc/print.hpp>

int main()
 {
  ptc::print( "\033[31m", "This is a red string" );
 }
```

<img src="https://github.com/JustWhit3/ptc-print/blob/main/img/images/red_string.png" width="150">

this holds also for all the other [ANSI escape sequences](https://en.wikipedia.org/wiki/ANSI_escape_code). To better manage them you can use external libraries like [`osmanip`](https://github.com/JustWhit3/osmanip). The stream is automatically reset when the end of the `ptc::print` object is met, only if an ANSI escape sequence appears among its arguments.

With [`osmanip`](https://github.com/JustWhit3/osmanip):

```C++
#include <ptc/print.hpp>
#include <osmanip/manipulators/colsty>

int main()
 {
  ptc::print( osm::feat( osm::col, "red" ), "This is a red string" );
 }
```

### Printing non-standard types

List of not built-int types ready for custom printing:

- C containers: [C arrays](https://www.learncpp.com/cpp-tutorial/pointers-and-arrays/).
- C++ containers: [`std::vector`](https://en.cppreference.com/w/cpp/container/vector), [`std::map`](https://en.cppreference.com/w/cpp/container/map), [`std::unordered_map`](https://en.cppreference.com/w/cpp/container/unordered_map), [`std::deque`](https://en.cppreference.com/w/cpp/container/deque), [`std::forward_list`](https://en.cppreference.com/w/cpp/container/forward_list), [`std::list`](https://en.cppreference.com/w/cpp/container/list), [`std::set`](https://en.cppreference.com/w/cpp/container/set), [`std::unordered_set`](https://cplusplus.com/reference/unordered_set/unordered_set/#:~:text=Unordered%20sets%20are%20containers%20that,key%2C%20that%20identifies%20it%20uniquely.), [`std::multimap`](https://cplusplus.com/reference/map/multimap/), [`std::multiset`](https://cplusplus.com/reference/set/multiset/), [`std::unordered_multiset`](https://en.cppreference.com/w/cpp/container/unordered_multiset#:~:text=Unordered%20multiset%20is%20an%20associative,order%2C%20but%20organized%20into%20buckets.), [`std::unordered_multimap`](https://en.cppreference.com/w/cpp/container/unordered_multimap).
- Container adaptors: [`std::stack`](https://en.cppreference.com/w/cpp/container/stack), [`std::priority_queue`](https://en.cppreference.com/w/cpp/container/priority_queue).
- Other types: [`std::complex`](https://en.cppreference.com/w/cpp/numeric/complex), [`std::chrono::duration`](https://en.cppreference.com/w/cpp/chrono/duration).

These special types printing are characterized by specific `operator <<` overloads. These overloads are defined into the `ptc` namespace, therefore they will not work outside of the `ptc::print` objects unless you use the `using namespace ptc` directive (warmly discouraged).

If you need support to other particular types you can open an issue with a [feature request](https://github.com/JustWhit3/ptc-print/blob/main/.github/ISSUE_TEMPLATE/feature_request.md).

For example, to print an `std::vector`:

```C++
#include <ptc/print.hpp>
#include <vector>

int main()
 {
  std::vector<int> vec = { 1, 2, 3 };
  ptc::print( vec );
 }
```

```txt
[1, 2, 3]
```

Or an `std::map`:

```C++
#include <ptc/print.hpp>
#include <map>

int main()
 {
  std::map<int,int> map = { { 1, 1 }, { 2, 2 }, { 3, 3 } };
  ptc::print( map );
 }
```

```txt
[[1, 1], [2, 2], [3, 3]]
```

To print `std::chrono::duration` objects:

```C++
#include <ptc/print.hpp>
#include <chrono>
using namespace std::literals::chrono_literals;

int main()
 {
  ptc::print( "Time:", 5m, 30s );
 }
```

```txt
Time: 5m 30s
```

### Printing user-defined types

Within `ptc::print` it is possible to print any user-defined type. For example:

```C++
#include <ptc/print.hpp>

// Define a new type
struct foo
 {
  foo( int a_, int b_ ): a(a_), b(b_) {}
  int a, b;
 };

// Overload operator << for the new type in namespace ptc in order to be available only for ptc::print.
namespace ptc
 {
  template <class T_str>
  std::basic_ostream<T_str>& operator <<( std::basic_ostream<T_str>& os, const foo& object )
   {
    os << object.a << "+" << object.b;
    return os;
   }
 }

int main()
 {
  foo object( 2, 3 );
  ptc::print( object );
 }
```

### Printing using different char types

It is possible to choose a different char type with respect to the standard `char` used to define an `std::string`. A list of supported char types by the `ptc::print` object is the following:

- `char`
- `wchar_t`

To print using `wchar_t` you can use the `ptc::wprint` function:

```C++
#include <ptc/print.hpp>

int main()
 {
  ptc::wprint( "Printing to", "std::wcout!" );
 }
```

```txt
Printing to std::wcout!
```

## Install and use

### Install

Steps:

1) Download one of the repository releases.
2) Unzip the downloaded directory and `cd` into it.
3) Copy the **ptc** folder in one of your projects or in a specific path or install into the system with this command:

```txt
./install.sh
```

Prerequisites are minimal and are automatically installed with the `install.sh` script. They are:

- g++ (like *gcc* or *clang*) compiler.
- C++17 standard.

4) Include the header into your project:

```C++
#include <ptc/print.hpp>
```

### Performance improvements

#### Runtime

To consistently increase **performance improvements** you can use the following preprocessor directive:

```C++
#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
```

at the beginning of your program. In this way, as you can see from [benchmarking studies](#benchmarking), runtime will be strongly increased in case you are printing with the default `std::cout` stream. Read [here](https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull) for more information about the benefit of this choice.

> :warning: the usage of `PTC_ENABLE_PERFORMANCE_IMPROVEMENTS` macro will propagate not only to `ptc::print`, but also to `std::cout` in general, since it is directly used inside `ptc::print`.

If you plan to use this preprocessor directive pay attention to the **following points**:

- Use this in case you don't plan to use both C++ and C output stream objects together (like `std::cout` and `printf` in the same program).
- Make sure to flush `ptc::print` manually every time you want to display something before expecting input on `std::cin`, since `std::cout` and `std::cin` have been untied (see [here](https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull)).

These operations preserve the library quality, however some memory false-positive errors may occur when running Valgrind *memcheck* tool; they are due to the [`std::ios_base::sync_with_stdio`](https://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio) function usage inside a generic class. This false-positive has been hidden into a Valgrind [suppression file](https://github.com/JustWhit3/ptc-print/tree/main/tests/valgrind_suppressions.supp). A related discussion can be found [here](https://stackoverflow.com/questions/73267528/valgrind-complaining-for-possible-memory-problems-from-a-program-which-uses-std?noredirect=1#comment129394781_73267528).

#### Compilation

To decrease the **compilation time** you can use the following preprocessor directive:

```C++
#define PTC_DISABLE_STD_TYPES_PRINTING
```

This operation will reduce the compilation time by 30% more or less. You can use the previous directive if you plan to not use any of the standard C++ containers (or extra types), since it basically disable the [printing of non-standard types](#printing-non-standard-types).

## Tests

Tests are produced using `-Wall -Wextra -pedantic` flags. To check them you need some prerequisites:

- [Valgrind](https://valgrind.org/) for profiling.
- [doctest](https://github.com/onqtam/doctest) for testing.
- [cppcheck](https://cppcheck.sourceforge.io/) for testing.

They are installed in the second step of the installation through the `install.sh` script. Before running test codes you need to compile them:

```txt
cd tests
make
```

To launch all tests simultaneously:

```txt
./all_tests.sh
```

Or separately:

```txt
./bin/unit_tests
./bin/system_tests
./bin/threading_tests
./include_tests.sh
cppcheck include/ptc/print.hpp
```

To check the automatic memory management through *Memcheck*:

```txt
./profiling.sh memcheck ./bin/system_tests
```

To check thread safety through *Helgrind*:

```txt
./profiling.sh helgrind ./bin/system_tests
```

Tests using the `PTC_ENABLE_PERFORMANCE_IMPROVEMENTS` macro are automatically performed launching barely the `all_tests.sh` script, or alternatively specifying:

```txt
./all_tests.sh macro
```

## Comparison with other libraries

To install extra libraries used for comparison you can use the [`install_deps.sh`]((https://github.com/JustWhit3/ptc-print/blob/main/studies/install_deps.sh)) script.

List of functions / objects which `ptc::print` is compared with:

- [`std::cout`](https://en.cppreference.com/w/cpp/io/cout)
- [`printf`](https://m.cplusplus.com/reference/cstdio/printf/)
- [`fmt::print`](https://pkg.go.dev/fmt) version 9.0.0

> :warning: comparisons are performed **only** on the same features of each library. For example: I am not comparing the whole `fmtlib` formatting library to mine, but simply the `fmt::print` function.

Studies are performed with the `g++ (Ubuntu 11.2.0-19ubuntu1)` compiler.

Before each benchmarking study an environment set-up is performed in order to reduce the noise (i.e the standard-deviation of each data-point). In particular the following operations are performed:

- Set `scaling_governor` to *performance*.
- Disable Turboboost.
- Drop file system cache.
- Disable address space randomization.

Motivations for each choice can be found [here](https://easyperf.net/blog/2019/08/02/Perf-measurement-environment-on-Linux). At the end of the final benchmarking run, old system settings are restored.

Other suggestions are more than welcome.

### Benchmarking the runtime

Benchmarking is performed using the [Google Benchmark](https://github.com/google/benchmark) framework. The script [studies/benchmarking_execution/run.sh](https://github.com/JustWhit3/ptc-print/blob/main/studies/benchmarking_execution/run.sh) is used to generate and analyze benchmark data. It makes use of the [cpupower](https://linux.die.net/man/1/cpupower) tool and launches two other scripts during its run:

- [benchmark.cpp](https://github.com/JustWhit3/ptc-print/blob/main/studies/benchmarking_execution/benchmarking.cpp): is used for data generation and benchmarks measurement. The same procedure, which for `ptc::print` corresponds to printing:

```c++
ptc::print( "Testing", 123, "print", '!' );
```

is repeated for *300.000* times and the total runtime is registered. This latter step is repeated again for *100* times and results of each iteration are averaged each other. Final mean value with the corresponding standard deviation is considered. This script is compiled with `-O3 -O1 -falign-functions=32` flags.

- [analysis.py](https://github.com/JustWhit3/ptc-print/blob/main/studies/benchmarking_execution/analysis.py): is used for data analysis and plots production, with comparison among each library benchmark results.

**Real time** benchmark results:

<img src="https://github.com/JustWhit3/ptc-print/blob/main/img/benchmarks/real_time/stdout_stream.png">

**CPU time** benchmark results:

<img src="https://github.com/JustWhit3/ptc-print/blob/main/img/benchmarks/cpu_time/stdout_stream.png">

Without performance optimizations `ptc::print` is slightly slower than the others.

### Benchmarking the runtime with performance improvements

Extra studies are performed using consistent improvements in the runtime, thanks to the `PTC_ENABLE_PERFORMANCE_IMPROVEMENTS` macro usage (see [here](#install-and-use) for more information). Using this macro definition will consistently speed-up the `ptc::print` object, as you can see from the following plots.

To run these benchmarks you can do:

```txt
./run.sh macro
```

**Real time** benchmark results with macro usage:

<img src="https://github.com/JustWhit3/ptc-print/blob/main/img/benchmarks/real_time/stdout_stream_macro.png">

**CPU time** benchmark results with macro usage:

<img src="https://github.com/JustWhit3/ptc-print/blob/main/img/benchmarks/cpu_time/stdout_stream_macro.png">

`std::cout` is omitted since some of the performance improvements are directly applied also to it.

With performance optimizations `ptc::print` is much faster than the others.

### Benchmarking the compilation time

Compilation time studies are performed using the [studies/benchmarking_compilation/run.sh](https://github.com/JustWhit3/ptc-print/blob/main/studies/benchmarking_compilation/run.sh) script, which launches the [analysis.py](https://github.com/JustWhit3/ptc-print/blob/main/studies/benchmarking/analysis.py) script during its run, which generates and analyzes benchmark data.

During its procedure, program printing the same string, which for `ptc::print` corresponds to:

```c++
ptc::print( "Testing", 123, "print", '!' );
```

is created and compiled with `-O3 -O1 -falign-functions=32` flags, for *100* times. The total compilation time of each run is registered and averaged. Final mean value with the corresponding standard deviation is considered:

<img src="https://github.com/JustWhit3/ptc-print/blob/main/img/benchmarks/compilation_time/stdout_stream.png">

The hight compilation time of `ptc::print` with respect to the other libraries is probably due to the fact that it comes from an header-only library.

### Benchmarking the compilation time with performance improvements

To decrease the compilation time see the [Compilation](#compilation) subsection of the [Performance improvements](#performance-improvements) section. With performance improvements enabled these are the results:

<img src="https://github.com/JustWhit3/ptc-print/blob/main/img/benchmarks/compilation_time/stdout_stream_macro.png">

### Executable size

The same script used for [compilation time benchmark studies](#benchmarking-the-compilation-time) does also executable size comparison for each of the object / function previously cited. For each of them, a small program doing the same stuff is stored into the [studies/benchmarking_compilation/programs](https://github.com/JustWhit3/ptc-print/tree/main/studies/benchmarking_compilation/programs) folder and is compiled with optimized building flag `-O3`. The size of the executable is then computed and compared in the following plot:

<img src="https://github.com/JustWhit3/ptc-print/blob/main/img/benchmarks/executable_size/stdout_stream.png">

### Advantages

- Very simple signature and more similar to the `print` Python function than any other know implementation:

`ptc::print`:

```c++
ptc::print( "I am", "very similar to Python", 123 );
```

`fmt::print`:

```c++
fmt::print( "{} {} {}\n", "I am", "very similar to Python", 123 );
```

- Faster than all the other printing objects: in case of `PTC_ENABLE_PERFORMANCE_IMPROVEMENTS` macro usage the library increases its speed with respect to the other similar utils. See [Benchmarking](#benchmarking) section.

- Possibility to change *end* and *separator* characters, like in Python:

`ptc::print`:

```c++
ptc::print.setSep( "*" );
ptc::print.endSep( "" );
ptc::print( "I am", "very similar to Python", 123 );
```

Python `print`:

```Python
print( "I am", "Python", 123, sep = "*", end = "" );
```

- Much more...

## Todo

### New features

- Add a specific method to reorder the printing of a nidified containers. For example:

```C++
#include <ptc/print.hpp>
#include <map>
#include <string>

int main()
 {
  std::map<int, std::string> map = { {1, "one"}, {3, "three"}, {5, "five"} };

  ptc::print( ptc::reorder( map ) );
 }
```

```txt
KEY  VALUE
1    one
3    three
5    five
```

- Add a method to print time in strftime-like format. For example

```C++
#include <ptc/print.hpp>
#include <chrono>
using namespace std::literals::chrono_literals;

int main()
 {
  ptc::print( 1h + 30min + 5s );
 }
```

```txt
01:30:05
```

- Add standard C pointers printing. For example:

```C++
#include <ptc/print.hpp>

int main()
 {
  int *ptr = new int[2];
  ptr[0] = 1;
  ptr[1] = 2;
  ptc::print( ptr );
 }
```

```txt
Pointer name: "ptr"
Value: 0x55b776e15060
Direction: 0x7ffd370e32c8
Printing: [1, 2]
```

Or in case someone wants only the printing:

```C++
ptc::print( ptr_printing( ptr ) );
```

```txt
[1, 2]
```

- Enable printing of fixed-size heterogeneous tuples. For example:

```C++
#include <ptc/print.hpp>
#include <tuple>

int main()
 {
  auto get_info = []( int index )  
   {
    if ( index == 0 ) return std::make_tuple( 3.8, '32', "Bologna" );
    if ( index == 1 ) return std::make_tuple( 2.9, '12', "Milano" );
    throw std::invalid_argument( "index" );
   };

  ptc::print( { get_info(0), get_info(1) } );
 }
```

```txt
{ (2.9, '12', "Milano"), (3.8, '32', "Bologna") }
```

- Enable printing of `std::optional` values:

```C++
#include <ptc/print.hpp>
#include <optional>

int main()
 {
  std::optional<int> opt = 32;
  ptc::print( opt );
 }
```

```txt
32
```

### Improvements

- Improve the printing to an external file stream. Current implementation is too slow.
- Upload the package on some package managers (ex: [`Conan`](https://conan.io/) or `dpkg`).
- Create a [wiki](https://github.com/JustWhit3/ptc-print/wiki) with detailed examples for every feature.
- Extend the support to `char16_t` and `char32_t` types.
- Extend benchmarking studies with other libraries.
- Add support to C++20 features.

## Projects which use this library

Empty for the moment.

## Credits

### Main maintainers

<table>
  <tr>
    <td align="center"><a href="https://justwhit3.github.io/"><img src="https://avatars.githubusercontent.com/u/48323961?v=4" width="100px;" alt=""/><br /><sub><b>Gianluca Bianco</b></sub></a></td>
  </tr>
</table>

### Other contributors

<!-- ALL-CONTRIBUTORS-LIST:START - Do not remove or modify this section -->
<!-- prettier-ignore-start -->
<!-- markdownlint-disable -->
<table>
  <tr>
    <td align="center"><a href="https://github.com/TedLyngmo"><img src="https://avatars.githubusercontent.com/u/2361158?v=4" width="100px;" alt=""/><br /><sub><b>Ted Lyngmo</b></sub></a></td>
    <td align="center"><a href="https://github.com/MiiKaa3"><img src="https://avatars.githubusercontent.com/u/62884597?v=4" width="100px;" alt=""/><br /><sub><b>MiiKaa3</b></sub></a></td>
  </tr>
</table>

<!-- markdownlint-restore -->
<!-- prettier-ignore-end -->

<!-- ALL-CONTRIBUTORS-LIST:END -->
