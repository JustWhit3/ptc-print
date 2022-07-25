//====================================================
//     Headers
//====================================================

// My headers
#include "../../include/ptc/print.hpp"

// Headers for comparison
#include <fmt/core.h>
#include <fmt/os.h>

// Extra headers
#include <benchmark/benchmark.h>

// STD headers
#include <iostream>
#include <sstream>
#include <fstream>
#include <string_view>

//====================================================
//     Namespace directives
//====================================================
namespace bm = benchmark;

//====================================================
//     ptc::print setters
//====================================================

// ptc_print_setSep
static void ptc_print_setSep( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print.setSep( "*" );
 }

// ptc_print_setEnd
static void ptc_print_setEnd( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print.setEnd( "." );
 }

// ptc_print_setFlush
static void ptc_print_setFlush( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print.setFlush( true );
 }

//====================================================
//     ptc::print getters
//====================================================

// ptc_print_getEnd
static void ptc_print_getEnd( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print.getEnd() );
 }

// ptc_print_getSep
static void ptc_print_getSep( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print.getSep() );
 }

// ptc_print_getFlush
static void ptc_print_getFlush( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print.getFlush() );
 }

//====================================================
//     ptc::print
//====================================================

// ptc_print_newline
static void ptc_print_newline( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print();
 }

// ptc_print
static void ptc_print( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print( std::cout, "Testing", "print", "function" );
 }

// ptc_print_stdout
static void ptc_print_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print( "Testing", "print", "function" );
 }

// ptc_print_file
static void ptc_print_file( bm::State& state ) 
 {
  std::ofstream file_stream;
  file_stream.open( "test.txt", std::ios::trunc );
  for ( auto _ : state ) ptc::print( file_stream, "Testing", "print", "function" );
  file_stream.close();
 }

//====================================================
//     std::cout
//====================================================

// std_cout
static void std_cout( bm::State& state ) 
 {
  for ( auto _ : state ) std::cout << "Testing" << " " << "print" << " " << "function" << "\n";
 }

// std_cout_newline
static void std_cout_newline( bm::State& state ) 
 {
  for ( auto _ : state ) std::cout << "\n";
 }

// std_ostringstream
static void std_ostringstream( bm::State& state ) 
 {
  std::ostringstream ostr;
  for ( auto _ : state ) ostr << "Testing" << " " << "print" << " " << "function" << "\n";
 }

// std_file
static void std_file( bm::State& state ) 
 {
  std::ofstream file_stream;
  file_stream.open( "test.txt", std::ios::trunc );
  for ( auto _ : state ) file_stream << "Testing" << " " << "print" << " " << "function" << "\n";
  file_stream.close();
 }

//====================================================
//     printf
//====================================================

// printf
static void printf( bm::State& state ) 
 {
  for ( auto _ : state ) printf( "Testing print function\n" );
 }

// printf_newline
static void printf_newline( bm::State& state ) 
 {
  for ( auto _ : state ) printf( "\n" );
 }

//====================================================
//     fmt::print
//====================================================

// fmt_print
static void fmt_print( bm::State& state ) 
 {
  for ( auto _ : state ) fmt::print( stdout, "Testing {} {}{}", "print", "function", "\n" );
 }

// fmt_print_newline
static void fmt_print_newline( bm::State& state ) 
 {
  for ( auto _ : state ) fmt::print( "\n" );
 }

// fmt_print_stdout
static void fmt_print_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) fmt::print( "Testing {} {}{}", "print", "function", "\n" );
 }

// fmt_print_file
static void fmt_print_file( bm::State& state ) 
 {
  auto out = fmt::output_file( "test.txt", std::ios::trunc );
  for ( auto _ : state ) out.print( "Testing {} {}{}", "print", "function", "\n" );
 }

//====================================================
//     Benchmarking settings
//====================================================

// ptc::print setters
//BENCHMARK( ptc_print_setEnd );
//BENCHMARK( ptc_print_setSep );
//BENCHMARK( ptc_print_setFlush );

// ptc::print getters
//BENCHMARK( ptc_print_getEnd );
//BENCHMARK( ptc_print_getSep );
//BENCHMARK( ptc_print_getFlush );

// ptc::print
BENCHMARK( ptc_print );
//BENCHMARK( ptc_print_newline );
//BENCHMARK( ptc_print_stdout );
//BENCHMARK( ptc_print_file );

// fmt::print
//BENCHMARK( fmt_print );
//BENCHMARK( fmt_print_newline );
//BENCHMARK( fmt_print_stdout );
//BENCHMARK( fmt_print_file );

// std::cout
//BENCHMARK( std_cout );
//BENCHMARK( std_cout_newline );
//BENCHMARK( std_ostringstream );
//BENCHMARK( std_file );

// printf
//BENCHMARK( printf );
//BENCHMARK( printf_newline );

BENCHMARK_MAIN();