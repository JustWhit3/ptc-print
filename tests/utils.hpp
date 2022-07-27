//====================================================
//     Preprocessor directives
//====================================================
#ifndef TESTS_UTILS_HPP
#define TESTS_UTILS_HPP

//====================================================
//     Headers
//====================================================

// My headers
#include "../include/ptc/print.hpp"

// STD headers
#include <iostream>
#include <streambuf>
#include <string>

namespace ptc
 {
  //====================================================
  //     savebuf class declarations
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

  //====================================================
  //     savebuf class members definition
  //====================================================
  savebuf::savebuf( std::streambuf* sbuf ): sbuf( sbuf ) {}

  std::string savebuf::str() const { return save; }

  int savebuf::sync() { return sbuf -> pubsync(); }

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

  //====================================================
  //     osout
  //====================================================
  template <class... Args>
  inline const std::string osout( std::ostream& os = std::cout, const Args&... args )
   {
    std::streambuf* buf = os.rdbuf();
    std::ostringstream str;

    savebuf sbuf( buf );
    os.rdbuf( &sbuf );
    
    ( ( str << args << print.getSep() ), ... );

    ptc::print( os, str.str() );
    os.rdbuf( buf );
    return sbuf.str();
   }

  template <class... Args>
  inline const std::string osout( const Args&... args )
   {
    std::streambuf* buf = std::cout.rdbuf();
    std::ostringstream str;

    savebuf sbuf( buf );
    std::cout.rdbuf( &sbuf );

    ( ( str << args << print.getSep() ), ... );

    ptc::print( std::cout, str.str() );
    std::cout.rdbuf( buf );
    return sbuf.str();
   }
 }

#endif