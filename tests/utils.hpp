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
  template <class T>
  class savebuf: public std::basic_streambuf<T>
   {
    public:
     savebuf( std::basic_streambuf<T>* sbuf ): sbuf( sbuf ) {};
     stype::string<T> str() const { return save; };

    private:
     int overflow( int c )
      {
       if ( ! std::char_traits<T>::eq_int_type( c, std::char_traits<T>::eof() ) ) 
        {
         save.push_back( std::char_traits<T>::to_char_type( c ) );
         return sbuf -> sputc( c );
        }
       else 
        {
         return std::char_traits<T>::not_eof( c );
        }
      } 
     int sync() { return sbuf -> pubsync(); };
     std::basic_streambuf<T>* sbuf;
     stype::string<T> save;
   };

  //====================================================
  //     osout
  //====================================================
  template <class T, class... Args>
  inline const stype::string<T> osout( stype::ostream<T>& os = select_cout<T>::cout, const Args&... args )
   {
    Print<T> printer;
    std::basic_streambuf<T>* buf = os.rdbuf();
    stype::ostringstream<T> str;

    savebuf<T> sbuf( buf );
    os.rdbuf( &sbuf );

    ( ( str << args << printer.getSep() ), ... );
    printer( os, str.str() );
    os.rdbuf( buf );
    return sbuf.str();
   }

  template <class T, class... Args>
  inline const stype::string<T> osout( const Args&... args )
   {
    Print<T> printer;
    std::basic_streambuf<T>* buf = select_cout<T>::cout.rdbuf();
    stype::ostringstream<T> str;

    savebuf<T> sbuf( buf );
    select_cout<T>::cout.rdbuf( &sbuf );

    ( ( str << args << printer.getSep() ), ... );
    printer( select_cout<T>::cout, str.str() );
    select_cout<T>::cout.rdbuf( buf );
    return sbuf.str();
   }
 }

#endif