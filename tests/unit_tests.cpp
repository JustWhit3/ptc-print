//====================================================
//     Preprocessor directives
//====================================================
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS

//====================================================
//     Headers
//====================================================

// My headers
#include "../include/ptc/print.hpp"
#include "utils.hpp"

// Extra headers
#include <doctest/doctest.h>

// STD headers
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

//====================================================
//     __print__ default constructor
//====================================================
TEST_CASE( "Testing the __print__ default constructor." )
 {
  CHECK_EQ( ptc::print.getEnd(), "\n" );
  CHECK_EQ( ptc::print.getSep(), " " );
 }

//====================================================
//     __print__ operator () overload
//====================================================
TEST_CASE( "Testing the operator () overload." )
 {  
  // General case
  SUBCASE( "General case." )
   {
    const std::string test = ptc::osout( std::cerr, "Test passes", "(ignore this)." );
    CHECK_EQ( test, "Test passes (ignore this). \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // General case with different types
  SUBCASE( "General case." )
   {
    const std::string test = ptc::osout( std::cerr, "Test passes", 123, "(ignore this)", '.' );
    CHECK_EQ( test, "Test passes 123 (ignore this) . \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // General case with no args
  SUBCASE( "General case with no args." )
   {
    const std::string test = ptc::osout( std::clog );
    CHECK_EQ( test, "\n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // stdout case
  SUBCASE( "Stdout case." )
   {
    const std::string test = ptc::osout( "Test passes", "(ignore this)." );
    CHECK_EQ( test, "Test passes (ignore this). \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // No arguments case
  SUBCASE( "No arguments case." )
   {
    std::streambuf* coutbuf = std::cout.rdbuf();
    ptc::savebuf sbuf( coutbuf );
    std::cout.rdbuf( &sbuf );
    ptc::print();
    std::cout.rdbuf( coutbuf );
    CHECK_EQ( sbuf.str(), "\n" );
    CHECK( sbuf.str() != "Test thisssa.\n" );
   }

  // std::ostringstream case
  SUBCASE( "std::ostringstream case." )
   {
    std::ostringstream ostr;
    ptc::print( ostr, "Test", "this." );
    CHECK_EQ( ostr.str(), "Test this.\n" );
    CHECK( ostr.str() != "Test thisssa.\n" );
   }
   
  // std::ofstream case
  SUBCASE( "std::ofstream case." )
   {
    std::ofstream file_stream_o;
    file_stream_o.open( "test.txt", std::ios::trunc );
    ptc::print( file_stream_o, "Test", "passes (ignore this)." );
    file_stream_o.close();

    char str[26];
    std::ifstream file_stream_i;
    file_stream_i.open( "test.txt" );
    file_stream_i.read( str, 26 );
    file_stream_i.close();

    CHECK_EQ( static_cast<std::string> ( str ), "Test passes (ignore this)." );
   }

  // std::fstream case
  SUBCASE( "std::fstream case." )
   {
    std::ofstream file_stream_f;
    file_stream_f.open( "test.txt", std::ios::out | std::ios::trunc );
    ptc::print( file_stream_f, "Test", "passes (ignore this)." );
    file_stream_f.close();

    char str[26];
    std::ifstream file_stream_i;
    file_stream_i.open( "test.txt" );
    file_stream_i.read( str, 26 );
    file_stream_i.close();

    CHECK_EQ( static_cast<std::string> ( str ), "Test passes (ignore this)." );
   }

  // Passing variables inside ptc::print
  SUBCASE( "Passing variables inside ptc::print." )
   {
    std::string str = "Test passes";
    const std::string test = ptc::osout( str, "(ignore this)." );
    CHECK_EQ( test, "Test passes (ignore this). \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // Testing the string return overload
  SUBCASE( "String return overload" )
   {
    ptc::print.setEnd( "" );

    CHECK_EQ( ptc::print( ptc::mode::str, "Test", "this!" ), "Test this!" );
    const std::string test_string = ptc::print( ptc::mode::str, "Test", "this!" );
    CHECK_EQ( test_string, "Test this!" );
    CHECK_EQ( ptc::print( ptc::mode::str ), "" );
    CHECK_EQ( ptc::print( ptc::mode::str, "" ), "" );

    ptc::print.setEnd( "\n" );
   }

  // Testing usage of ANSI escape sequence and final reset
  SUBCASE( "Testing usage of ANSI escape sequence and final reset." )
   {
    const std::string test_a = ptc::osout( "\033[31mTesting colors", "(ignore this)." );
    CHECK_EQ( test_a, "\033[31mTesting colors (ignore this). \n\033[0m" );

    ptc::print.setEnd( "" );
    const std::string test_b = ptc::print( ptc::mode::str, "Testing", "\033[31mcolors", "(ignore this)." );
    CHECK_EQ( test_b, "Testing \033[31mcolors (ignore this).\033[0m" );
    const std::string test_c = ptc::print( ptc::mode::str, "Testing", "the \033[31mcolors", "(ignore this)." );
    CHECK_EQ( test_c, "Testing the \033[31mcolors (ignore this).\033[0m" );
    CHECK_EQ( ptc::print( ptc::mode::str, 1, "Number" ), "1 Number" );
    ptc::print.setEnd( "\n" );
   }

  // Testing usage of ANSI or empty character as first argument
  SUBCASE( "Testing ANSI escape sequence inside ptc::print." ) // TODO: This should be improved (delete last empty space)
   {
    ptc::print.setEnd( "" );
    const std::string test_a = ptc::print( ptc::mode::str, "", "Testing empty char (ignore this)." );
    CHECK_EQ( test_a, "Testing empty char (ignore this). " ); 
    const std::string test_b = ptc::print( ptc::mode::str, "\033[31m", "Testing empty char (ignore this)." );
    CHECK_EQ( test_b, "\033[31mTesting empty char (ignore this). \033[0m" ); 
    ptc::print.setEnd( "\n" );
   }
 }

//====================================================
//     __print__ setEnd and getEnd
//====================================================
TEST_CASE( "Testing the __print__ setEnd and getEnd methods." )
 {
  ptc::print.setEnd( '.' );
  CHECK_EQ( ptc::print.getEnd(), "." );
  
  std::streambuf* cerrbuf = std::cerr.rdbuf();
  ptc::savebuf sbuf( cerrbuf );
  std::cerr.rdbuf( &sbuf );
  ptc::print( std::cerr, "Test passes (ignore this)." );
  std::cerr.rdbuf( cerrbuf );
  CHECK_EQ( sbuf.str(), "Test passes (ignore this).." );
  CHECK( sbuf.str() != "Test thisssa.\n" );

  ptc::print.setEnd( "\n" );
  ptc::print( "\n" );
 }

//====================================================
//     __print__ setSep and getSep
//====================================================
TEST_CASE( "Testing the __print__ setSep and getSep methods." )
 {
  ptc::print.setSep( "*" );
  CHECK_EQ( ptc::print.getSep(), "*" );

  std::streambuf* coutbuf = std::cout.rdbuf();
  ptc::savebuf sbuf( coutbuf );
  std::cout.rdbuf( &sbuf );
  ptc::print( "Test", "passes", "(ignore this)." );
  std::cout.rdbuf( coutbuf );
  CHECK_EQ( sbuf.str(), "Test*passes*(ignore this).\n" );
  CHECK( sbuf.str() != "Test thisssa.\n" );

  ptc::print.setSep( " " );
 }

//====================================================
//     __print__ setFlush and getFlush
//====================================================
TEST_CASE( "Testing the __print__ setFlush and getFlush methods." )
 {
  ptc::print.setFlush( true );
  CHECK_EQ( ptc::print.getFlush(), true );

  std::streambuf* coutbuf = std::cout.rdbuf();
  ptc::savebuf sbuf( coutbuf );
  std::cout.rdbuf( &sbuf );
  ptc::print( "Test", "passes", "(ignore this)." );
  std::cout.rdbuf( coutbuf );
  CHECK_EQ( sbuf.str(), "Test passes (ignore this).\n" );
  CHECK( sbuf.str() != "Test thisssa.\n" );

  ptc::print.setFlush( false );
 }