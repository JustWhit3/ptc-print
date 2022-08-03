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
inline const std::string test = "hey";

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

// ptc_print_standard
static void ptc_print_standard( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print( std::cout, "Testing", 123, "print", test );
 }

// ptc_print_stdout
static void ptc_print_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print( "Testing", 123, "print", test );
 }

// ptc_print_newline
static void ptc_print_newline( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print();
 }

// ptc_print_file
static void ptc_print_file( bm::State& state ) 
 {
  std::ofstream file_stream;
  file_stream.open( "test.txt", std::ios::trunc );
  for ( auto _ : state ) ptc::print( file_stream, "Testing", 123, "print", test );
  file_stream.close();
 }

// ptc_print_str
static void ptc_print_str( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print( ptc::mode::str, "Testing", 123, "print", test ) );
 }

//====================================================
//     std::cout
//====================================================

// std_cout_stdout
static void std_cout_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) std::cout << "Testing " << 123 << " print " << test << "\n";
 }

// std_cout_newline
static void std_cout_newline( bm::State& state ) 
 {
  for ( auto _ : state ) std::cout << "\n";
 }

// std_file
static void std_file( bm::State& state ) 
 {
  std::ofstream file_stream;
  file_stream.open( "test.txt", std::ios::trunc );
  for ( auto _ : state ) file_stream << "Testing " << 123 << " print " << test << "\n";
  file_stream.close();
 }

//====================================================
//     printf
//====================================================

// printf_stdout
static void printf_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) printf( "Testing 123 print hey\n" );
 }

// printf_newline
static void printf_newline( bm::State& state ) 
 {
  for ( auto _ : state ) printf( "\n" );
 }

//====================================================
//     fmt::print
//====================================================

// fmt_print_standard
static void fmt_print_standard( bm::State& state ) 
 {
  for ( auto _ : state ) fmt::print( stdout, "Testing {} {} {}\n", 123, "print", test );
 }

// fmt_print_newline
static void fmt_print_newline( bm::State& state ) 
 {
  for ( auto _ : state ) fmt::print( "\n" );
 }

// fmt_print_stdout
static void fmt_print_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) fmt::print( "Testing {} {} {}\n", 123, "print", test );
 }

// fmt_print_file
static void fmt_print_file( bm::State& state ) 
 {
  auto out = fmt::output_file( "test.txt", std::ios::trunc );
  for ( auto _ : state ) out.print( "Testing {} {} {}\n", 123, "print", test );
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
//BENCHMARK( ptc_print_standard );
//BENCHMARK( ptc_print_newline );
BENCHMARK( ptc_print_stdout );
//BENCHMARK( ptc_print_file );
//BENCHMARK( ptc_print_str );

// fmt::print
//BENCHMARK( fmt_print_standard );
//BENCHMARK( fmt_print_newline );
BENCHMARK( fmt_print_stdout );
//BENCHMARK( fmt_print_file );
// fmt str

// std::cout
BENCHMARK( std_cout_stdout );
//BENCHMARK( std_cout_newline );
//BENCHMARK( std_file );
// std str

// printf
BENCHMARK( printf_stdout );
//BENCHMARK( printf_newline );

BENCHMARK_MAIN();