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
#include <complex>
#include <vector>
#include <stack>
#include <chrono>

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
//      ptc::print other 
//====================================================

// ptc_print_standard
static void ptc_print_standard( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print( std::cout, "Testing", 123, "print", '!' );
 }

// ptc_print_str
static void ptc_print_str( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::print( ptc::mode::str, "Testing", 123, "print", '!' ) );
 }

// ptc_print_TOSTRING
static void ptc_print_TOSTRING( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( ptc::TOSTRING( char, "Hey" ) );
 }

//====================================================
//      ptc::print non built-in types 
//====================================================

// ptc_print_complex
static void ptc_print_complex( bm::State& state ) 
 {
  std::complex <int> cmplx_no( 1, 4 );
  for ( auto _ : state ) ptc::print( cmplx_no );
 }

// ptc_print_vector
static void ptc_print_vector( bm::State& state ) 
 {
  std::vector <int> vec = { 1, 2, 3 };
  for ( auto _ : state ) ptc::print( vec );
 }

// ptc_print_stack
static void ptc_print_stack( bm::State& state ) 
 {
  std::stack <int> stack;
  stack.push( 2 );
  stack.push( 4 );
  for ( auto _ : state ) ptc::print( stack );
 }

// ptc_print_duration
static void ptc_print_duration( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print( std::chrono::seconds( 5 ) );
 }

//====================================================
//      stdout
//====================================================

// ptc_print_stdout
static void ptc_print_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) ptc::print( "Testing", 123, "print", '!' );
 }

// fmt_print_stdout
static void fmt_print_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) fmt::print( "Testing {} {} {}\n", 123, "print", '!' );
 }

// std_cout_stdout
static void std_cout_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) std::cout << "Testing " << 123 << " print " << '!' << "\n";
 }

// printf_stdout
static void printf_stdout( bm::State& state ) 
 {
  for ( auto _ : state ) printf( "Testing %d %s %c\n", 123, "print", '!' );
 }

//====================================================
//      file writing
//====================================================

// ptc_print_file
static void ptc_print_file( bm::State& state ) 
 {
  std::ofstream file_stream;
  file_stream.open( "test.txt", std::ios::trunc );
  for ( auto _ : state ) ptc::print( file_stream, "Testing", 123, "print", '!' );
  file_stream.close();
 }

// std_file
static void std_file( bm::State& state ) 
 {
  std::ofstream file_stream;
  file_stream.open( "test.txt", std::ios::trunc );
  for ( auto _ : state ) file_stream << "Testing " << 123 << " print " << '!' << "\n";
  file_stream.close();
 }

// fmt_print_file
static void fmt_print_file( bm::State& state ) 
 {
  auto out = fmt::output_file( "test.txt", std::ios::trunc );
  for ( auto _ : state ) out.print( "Testing {} {} {}\n", 123, "print", '!' );
 }

//====================================================
//     ptc::print methods
//====================================================

// ptc::print setters
//BENCHMARK( ptc_print_setEnd );
//BENCHMARK( ptc_print_setSep );
//BENCHMARK( ptc_print_setFlush );

// ptc::print getters
//BENCHMARK( ptc_print_getEnd );
//BENCHMARK( ptc_print_getSep );
//BENCHMARK( ptc_print_getFlush );

// ptc::print other 
//BENCHMARK( ptc_print_standard );
//BENCHMARK( ptc_print_str );
//BENCHMARK( ptc_print_TOSTRING );

// non built-in types
//BENCHMARK( ptc_print_complex );
//BENCHMARK( ptc_print_vector );
//BENCHMARK( ptc_print_stack );
BENCHMARK( ptc_print_duration );

//====================================================
//     Comparison with other libraries
//====================================================

// stdout
//BENCHMARK( ptc_print_stdout );
//BENCHMARK( fmt_print_stdout ) ;
//BENCHMARK( std_cout_stdout ) ;
//BENCHMARK( printf_stdout );

// file writing
//BENCHMARK( ptc_print_file );
//BENCHMARK( fmt_print_file );
//BENCHMARK( std_file );

BENCHMARK_MAIN();