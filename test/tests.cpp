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

// Extra headers
#include <doctest/doctest.h>

// STD headers
#include <iostream>
#include <streambuf>

//====================================================
//     savebuf (helper class)
//====================================================
  class savebuf: public std::streambuf 
   {
    public:
     savebuf( std::streambuf* sbuf );
     std::string str() const;

    private:

     int overflow( int c );
     int sync();
     
     std::streambuf* sbuf;
     std::string     save;
   };

  savebuf::savebuf( std::streambuf* sbuf ): 
   sbuf( sbuf ) 
   {}

  std::string savebuf::str() const 
   { 
    return save; 
   }

  int savebuf::overflow( int c ) 
   {
    if ( ! traits_type::eq_int_type( c, traits_type::eof() ) ) 
     {
      save.push_back( traits_type::to_char_type( c ) );
      return sbuf -> sputc( c );
     }
    else 
     {
      return traits_type::not_eof( c );
     }
   } 

  int savebuf::sync() 
   { 
    return sbuf -> pubsync(); 
   }

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
  SUBCASE( "General case." )
   {
    std::streambuf* cerrbuf = std::cerr.rdbuf();
    savebuf sbuf( cerrbuf );
    std::cerr.rdbuf( &sbuf );
    ptc::print( std::cerr << "Test this." );
    std::cerr.rdbuf( cerrbuf );
    CHECK_EQ( sbuf.str(), "Test this.\n" );
    CHECK( sbuf.str() != "Test thisssa.\n" );
   }

  SUBCASE( "Stdout case." )
   {
    
   }

  SUBCASE( "No arguments case." )
   {
    
   }
 }

//====================================================
//     __print__ setEnd and getEnd
//====================================================
TEST_CASE( "Testing the __print__ setEnd and getEnd methods." )
 {
  ptc::print.setEnd( '.' );
  CHECK_EQ( ptc::print.getEnd(), "." );
  ptc::print.setEnd( "\n" );
 }

//====================================================
//     __print__ setSep and getSep
//====================================================
TEST_CASE( "Testing the __print__ setSep and getSep methods." )
 {
  ptc::print.setSep( "\"" );
  CHECK_EQ( ptc::print.getSep(), "\"" );
  ptc::print.setSep( " " );
 }