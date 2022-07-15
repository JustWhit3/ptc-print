//====================================================
//     Headers
//====================================================

// My headers
#include "../ptc/print.hpp"

// Headers for comparison
#include "deps/fmt/include/fmt/core.h"
#include "deps/fmt/include/fmt/os.h"

// Extra headers
#include <benchmark/benchmark.h>

// STD headers
#include <iostream>
#include <sstream>
#include <fstream>

//====================================================
//     Namespace directives
//====================================================
namespace bm = benchmark;

//====================================================
//     ptc::print proper methods
//====================================================

// ptc_print_setSep
static void ptc_print_setSep( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print.setSep( "*" ) );
 }

// ptc_print_getSep
static void ptc_print_getSep( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print.getSep() );
 }

// ptc_print_setEnd
static void ptc_print_setEnd( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print.setEnd( "." ) );
 }

// ptc_print_getEnd
static void ptc_print_getEnd( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print.getEnd() );
 }

//====================================================
//     ptc::print
//====================================================

// ptc_print_newline
static void ptc_print_newline( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print( std::cout ) );
 }

// ptc_print
static void ptc_print( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print( std::cout, "Testing", "print", "\u001b[1A" ) );
 }

// ptc_print_stdout
static void ptc_print_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print( "Testing", "print", "\u001b[1A" ) );
 }

// ptc_print_ostringstream
static void ptc_print_ostringstream( bm::State& state ) 
 {
  std::ostringstream ostr;
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print( ostr, "Testing", "print", "\u001b[1A" ) );
 }

// ptc_print_file
static void ptc_print_file( bm::State& state ) 
 {
  std::ofstream file_stream;
  file_stream.open( "test.txt", std::ios::trunc );
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print( file_stream, "Testing", "print", "\u001b[1A" ) );
  file_stream.close();
 }

//====================================================
//     std::cout
//====================================================

// std_cout
static void std_cout( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( std::cout << "Testing" << " " << "print" << " " << "\u001b[1A" << "\n" );
 }

// std_cout_newline
static void std_cout_newline( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( std::cout << "\n" );
 }

// std_ostringstream
static void std_ostringstream( bm::State& state ) 
 {
  std::ostringstream ostr;
  for ( auto _ : state ) bm::DoNotOptimize( ostr << "Testing" << " " << "print" << " " << "\u001b[1A" << "\n" );
 }

// std_file
static void std_file( bm::State& state ) 
 {
  std::ofstream file_stream;
  file_stream.open( "test.txt", std::ios::trunc );
  for ( auto _ : state ) bm::DoNotOptimize( file_stream << "Testing" << "print" << "\u001b[1A" << "\n" );
  file_stream.close();
 }

//====================================================
//     printf
//====================================================

// printf
static void printf( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( printf( "Testing print \u001b[1A\n" ) );
 }

// printf_newline
static void printf_newline( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( printf( "\n" ) );
 }

//====================================================
//     fmt::print
//====================================================

// fmt_print
static void fmt_print( bm::State& state ) 
 {
  for ( auto _ : state ) fmt::print( "Testing print \u001b[1A\n" );
 }

// fmt_print_newline
static void fmt_print_newline( bm::State& state ) 
 {
  for ( auto _ : state ) fmt::print( "\n" );
 }

// fmt_print_file
static void fmt_print_file( bm::State& state ) 
 {
  auto out = fmt::output_file( "test.txt" );
  for ( auto _ : state ) out.print( "Testing print \u001b[1A\n" );
 }

//====================================================
//     Benchmarking settings
//====================================================

// ptc::print proper methods
BENCHMARK( ptc_print_setEnd );
BENCHMARK( ptc_print_setSep );
BENCHMARK( ptc_print_getEnd );
BENCHMARK( ptc_print_getSep );

// ptc::print
BENCHMARK( ptc_print );
BENCHMARK( ptc_print_newline );
BENCHMARK( ptc_print_stdout );
BENCHMARK( ptc_print_ostringstream );
BENCHMARK( ptc_print_file );

// std::cout
BENCHMARK( std_cout );
BENCHMARK( std_cout_newline );
BENCHMARK( std_ostringstream );
BENCHMARK( std_file );

// printf
BENCHMARK( printf );
BENCHMARK( printf_newline );

// fmt::print
BENCHMARK( fmt_print );
BENCHMARK( fmt_print_newline );
BENCHMARK( fmt_print_file );

BENCHMARK_MAIN();