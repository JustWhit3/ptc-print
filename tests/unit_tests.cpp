//====================================================
//     Preprocessor directives
//====================================================
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS

//====================================================
//     Headers
//====================================================

// My headers
#include "../ptc/print.hpp"
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

  // Passing variables inside ptc::print
  SUBCASE( "Passing variables inside ptc::print." )
   {
    std::string str = "Test passes";
    const std::string test = ptc::osout( str, "(ignore this)." );
    CHECK_EQ( test, "Test passes (ignore this). \n" );
    CHECK( test != "Test thisssa.\n" );
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