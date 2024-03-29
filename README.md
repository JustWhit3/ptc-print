<p align="center"><img src="https://github.com/JustWhit3/ptc-print/blob/main/img/images/logo.svg" height=220></p>

<h3 align="center">A single-header library for custom printing to the output stream. </h3>
<p align="center">
  <img title="v1.4" alt="v1.4" src="https://img.shields.io/badge/version-v1.4-informational?style=flat-square">
  <img title="MIT License" alt="license" src="https://img.shields.io/badge/license-MIT-informational?style=flat-square">
	<img title="C++17/20" alt="C++17/20" src="https://img.shields.io/badge/c++-17/20-informational?style=flat-square"><br/>
	<img title="Code size" alt="code size" src="https://img.shields.io/github/languages/code-size/JustWhit3/ptc-print?color=red">
	<img title="Repo size" alt="repo size" src="https://img.shields.io/github/repo-size/JustWhit3/ptc-print?color=red">
	<img title="Lines of code" alt="total lines" src="https://img.shields.io/tokei/lines/github/JustWhit3/ptc-print?color=red"></br>
  <img title="codeq" alt="codeq" src="https://github.com/JustWhit3/ptc-print/actions/workflows/codeql-analysis.yml/badge.svg">
  <img title="doc" alt="doc" src="https://github.com/JustWhit3/ptc-print/actions/workflows/DocGenerator.yml/badge.svg">
</p>

***

## Table of contents

- [Introduction](#introduction)
- [Architectures support](#architectures-support)
  - [Operating systems](#operating-systems)
  - [Compilers](#compilers)
- [Examples](#examples)
  - [Standard cases](#standard-cases)
  - [Printing with ANSI escape sequences](#printing-with-ansi-escape-sequences)
  - [Printing non-standard types](#printing-non-standard-types)
  - [Printing user-defined types](#printing-user-defined-types)
  - [Printing using different char types](#printing-using-different-char-types)
- [Install and use](#install-and-use)
  - [Install](#install)
  - [Use with CMake](#use-with-cmake)
  - [Package managers](#package-managers)
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
- [Projects which use this library](#projects-which-use-this-library)
- [Credits](#credits)
  - [Main maintainers](#main-maintainers)
  - [Other contributors](#other-contributors)
- [Stargazers over time](#stargazers-over-time)

## Introduction

`ptc::print` (*py-to-cpp print*) is a C++17/20 printing object inspired by the Python [`print`](https://realpython.com/python-print/) function, which provides you a most comfortable way to print messages and logs to the output stream. This library is available also with `vcpkg` package manager.

It is constructed through the [`Print`](https://justwhit3.github.io/ptc-print/structptc_1_1Print.html) functor, which is a fully *type-* and *thread-safe* class with *automatic memory management*, implemented through an [single-header](https://github.com/JustWhit3/ptc-print/blob/main/ptc/print.hpp) library, with minimal and indispensable [dependencies](#install-and-use). It supports also the usage of [ANSI escape sequences](#printing-with-ansi-escape-sequences) and is cross-platform.

`ptc::print` supports the printing of all the standard types and some non-standard ones (list [here](#printing-non-standard-types)).

It is possible to choose to print using different char types (`char`, `wchar_t`...). List of supported `char` types can be found [here](#printing-non-standard-types).

If you want to contribute to the repository, please read [this](https://github.com/JustWhit3/ptc-print/blob/main/CONTRIBUTING.md) file before. If you want to propose ideas you can open a [discussion](https://github.com/JustWhit3/ptc-print/discussions).

If you plan to use this tool in one of your projects please let me know so I can link you to the [Projects which use this library](#projects-which-use-this-library) section.

Code documentation is generated using [*Doxygen*](https://www.doxygen.nl/manual/starting.html) and can be accessed [here](https://justwhit3.github.io/ptc-print/). Updates and news will be published at [this](https://github.com/JustWhit3/ptc-print/discussions/categories/announcements) discussion page.

The software is and will stay **free**, but if you want to support me with a donation it would be really appreciated!

<a href="https://www.buymeacoffee.com/JustWhit33" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Buy Me A Coffee" height="41" width="174"></a>

## Architectures support

### Operating systems

- **Linux**
  - *Ubuntu* (tested)
- **Windows** (release 10 or higher)
  - *Cygwin64* (tested)
  - *MSYS2* (tested)
  - *MinGW* (tested)
  - *WSL* (tested)
  - *Powershell* (tested)
- **MacOS**

### Compilers

- **gcc**:
  - *C++17*: 7/8/9/10/11/12
  - *C++20*: 10/11/12
- **clang**:
  - *C++17*: 5/6/7/8/9/10/11/12/13/14/15
  - *C++20*: 9/10/11/12/13/14/15
- **MSVC**:
  - *C++17*: 19 (only this one tested)
  - *C++20*: //

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

- C containers: [C arrays](https://www.learncpp.com/cpp-tutorial/pointers-and-arrays/), [C pointers](https://cplusplus.com/doc/tutorial/pointers/).
- C++ containers: [`std::vector`](https://en.cppreference.com/w/cpp/container/vector), [`std::map`](https://en.cppreference.com/w/cpp/container/map), [`std::unordered_map`](https://en.cppreference.com/w/cpp/container/unordered_map), [`std::deque`](https://en.cppreference.com/w/cpp/container/deque), [`std::forward_list`](https://en.cppreference.com/w/cpp/container/forward_list), [`std::list`](https://en.cppreference.com/w/cpp/container/list), [`std::set`](https://en.cppreference.com/w/cpp/container/set), [`std::unordered_set`](https://cplusplus.com/reference/unordered_set/unordered_set/#:~:text=Unordered%20sets%20are%20containers%20that,key%2C%20that%20identifies%20it%20uniquely.), [`std::multimap`](https://cplusplus.com/reference/map/multimap/), [`std::multiset`](https://cplusplus.com/reference/set/multiset/), [`std::unordered_multiset`](https://en.cppreference.com/w/cpp/container/unordered_multiset#:~:text=Unordered%20multiset%20is%20an%20associative,order%2C%20but%20organized%20into%20buckets.), [`std::unordered_multimap`](https://en.cppreference.com/w/cpp/container/unordered_multimap).
- Container adaptors: [`std::stack`](https://en.cppreference.com/w/cpp/container/stack), [`std::priority_queue`](https://en.cppreference.com/w/cpp/container/priority_queue).
- Other types: [`std::complex`](https://en.cppreference.com/w/cpp/numeric/complex), [`std::chrono::duration`](https://en.cppreference.com/w/cpp/chrono/duration), [`std::tuple`](https://en.cppreference.com/w/cpp/utility/tuple).

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

To print pointer information use the [ptc::ptr](https://justwhit3.github.io/ptc-print/namespaceptc.html#ace943d075c91bba7265425760ede4cb4) function:

```C++
#include <ptc/print.hpp>

int main()
 {
  int add = 2;
  int *pointer;
  pointer = &add;
  ptc::print( ptc::ptr( pointer ) );
 }
```

```txt
Value: 0x7fffc43b1d24
Address: 0x7fffc43b1cc0
```

It works also for higher-order pointers (ex: pointer of a pointer).

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

- `char` (`ptc::print`)
- `wchar_t` (`ptc::wprint`)
- `char16_t` (`ptc::print16`)
- `char32_t` (`ptc::print32`)

> :warning: MacOS operating systems don't support `char16_t` neither `char32_t`, since these types are defined in the [`cuchar`](https://cplusplus.com/reference/cuchar/) header which is not present in XCode.

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
3.a) Copy the **ptc** folder in one of your projects or in a specific path.
3.b) Or install into the system with these command:

Set the building directory:

```bash
cmake -B build
```

Install:

```bash
sudo cmake --build build --target install
```

> :warning: `sudo` is not required on Windows.

Prerequisites are minimal:

- g++ (like *gcc*, *clang* or *MSVC*) compiler.
- C++17 standard at least.
- CMake (v 3.15 at least).

4) Include the header into your project:

```C++
#include <ptc/print.hpp>
```

### Use with CMake

To get an installed version of the library:

```cmake
find_package( ptcprint )
```

then, to link it to a target:

```cmake
target_link_libraries( ${TARGET} ptcprint::ptcprint )
```

To avoid tests compilation:

```cmake
set( PTCPRINT_TESTS OFF )
```

### Package managers

To install with `vcpkg` package manager run:

```shell
vcpkg install ptc-print
```

### Performance improvements

#### Runtime

To consistently increase **performance improvements** you can use the following preprocessor directive:

```C++
#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
```

at the beginning of your program. In this way, as you can see from [benchmarking studies](#benchmarking), runtime will be strongly increased in case you are printing with the default `std::cout` stream. Read [here](https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull) for more information about the benefit of this choice.

> :warning: the usage of `PTC_ENABLE_PERFORMANCE_IMPROVEMENTS` macro will propagate not only to `ptc::print`, but also to `std::cout` in general, since it is directly used inside `ptc::print`.

> :warning: do not use in case of `ptc::print16` or `ptc::print32` usage, since for `char16_t` and `char32_t` there is any `std::cout` counterpart and optimization will raise an error.

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

Tests are produced using `-Wall -Wextra -pedantic` flags. To run them you need some prerequisites:

- [CMake](https://cmake.org/) (at least v3.15 is required).
- [Valgrind](https://valgrind.org/) for profiling.
- [doctest](https://github.com/onqtam/doctest) for testing.
- [cppcheck](https://cppcheck.sourceforge.io/) for testing.

To compile unit tests code:

Set the building directory:

```bash
cmake -B build 
```

Compile:

```txt
cmake --build build
```

To launch all tests simultaneously:

```txt
./tests/all_tests.sh
```

Or separately:

```txt
./build/tests/unit_tests
./build/tests/system_tests
./build/tests/threading_tests
./tests/include_tests.sh
cppcheck include/ptc/print.hpp
```

To check the automatic memory management through *Memcheck*:

```txt
./tests/profiling.sh memcheck ./build/tests/system_tests
```

To check thread safety through *Helgrind*:

```txt
./tests/profiling.sh helgrind ./build/tests/system_tests
```

Tests using the `PTC_ENABLE_PERFORMANCE_IMPROVEMENTS` macro are automatically performed launching barely the `all_tests.sh` script, or alternatively specifying:

```txt
./tests/all_tests.sh macro
```

**EXTRA**: to check that only the needed headers are include use this script:

```txt
./tests/IWYU.sh
```

which is based on [include-what-you-use](https://github.com/include-what-you-use/include-what-you-use).

## Comparison with other libraries

To install extra libraries used for comparison you can use the [`install_deps.sh`]((https://github.com/JustWhit3/ptc-print/blob/main/studies/install_deps.sh)) script.

List of functions / objects which `ptc::print` is compared with:

- [`std::cout`](https://en.cppreference.com/w/cpp/io/cout)
- [`printf`](https://m.cplusplus.com/reference/cstdio/printf/)
- [`fmt::print`](https://pkg.go.dev/fmt) version 9.0.0
- [`pprint`](https://github.com/p-ranav/pprint).

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

To run these benchmarks you can do:

```txt
cd studies/benchmarking_execution
cmake -S. -B build
cmake --build build
./run.sh
```

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

- Improve the printing to an external file stream. Current implementation is too slow.
- Add support to SFML types printing.

## Projects which use this library

- [snake-game](https://github.com/JustWhit3/snake-game)

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


## Stargazers over time

[![Stargazers over time](https://starchart.cc/JustWhit3/ptc-print.svg)](https://starchart.cc/JustWhit3/ptc-print)
