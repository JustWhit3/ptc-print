//====================================================
//     Metadata
//====================================================
/**
 * @file print.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-07-14
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#ifndef PRINT_HPP
#define PRINT_HPP
#pragma once

//====================================================
//     Headers
//====================================================
#include <iostream>
#include <string>
#include <type_traits>
#include <sstream>
#include <fstream>
#include <mutex>
#include <string_view>
#include <utility>
#include <vector>

namespace ptc
 {
  //====================================================
  //     ptc_print class
  //====================================================
  /**
   * @brief Class used to construct the print function.
   * 
   */
  struct __print__
   {
     //====================================================
     //     Public constructors and destructor
     //====================================================

     // Default constructor
     /**
      * @brief Default constructor of the __print__ class. It initializes the basic class members.
      * 
      */
     __print__(): end( "\n" ), sep( " " ), flush( false ) {}

     // Destructor
     /**
      * @brief Destructor of the __print__ class. It resets the output stream from ANSI escape sequences, in case of std::ostream usage within the () operator.
      * 
      */
     ~__print__()
      { 
       std::lock_guard <std::mutex> lock{ mutex_ };
       
       std::cout << "\033[0m";
       std::cerr << "\033[0m";
       std::clog << "\033[0m";
      }

     //====================================================
     //     Public setters
     //====================================================

     // setEnd
     /**
      * @brief Setter used to set the value of the "end" variable.
      * 
      * @tparam T The type of the expression inserted to set the value of "end" variable.
      * @param end_val The inserted expression used to set the value of "end" variable.
      */
     template <class T> 
     inline void setEnd( const T& end_val ) { end = end_val; }

     // setSep
     /**
      * @brief Setter used to set the value of the "sep" variable.
      * 
      * @tparam T The type of the expression inserted to set the value of "sep" variable.
      * @param end_val The inserted expression used to set the value of "sep" variable.
      */
     template <class T>
     inline void setSep( const T& sep_val ) { sep = sep_val; }

     // setFlush
     /**
      * @brief Setter used to set the value of the "flush" variable.
      * 
      * @param flush_val The inserted expression used to set the value of the "flush" variable.
      */
     inline void setFlush( const bool& flush_val ) { flush = flush_val; }

     //====================================================
     //     Public getters
     //====================================================

     // getEnd
     /**
      * @brief Getter used to get the value of the "end" variable.
      * 
      * @return auto The value of the "end" variable.
      */
     inline const auto& getEnd() const { return end; }

     // getSep
     /**
      * @brief Getter used to get the value of the "sep" variable.
      * 
      * @return auto The value of the "sep" variable.
      */
     inline const auto& getSep() const { return sep; }

     // getFlush
     /**
      * @brief Getter used to get the value of the "flush" variable.
      * 
      * @return bool The value of the "flush" variable.
      */
     inline const bool& getFlush() const { return flush; }

     //====================================================
     //     Operator () overloads
     //====================================================

     // General case
     /**
      * @brief Frontend implementation of the () operator overload to print to the output stream. The backend implementation is called in the required variation.
      * 
      * @tparam T Generic type of first object to be passed as argument to the backend implementation.
      * @tparam Args Generic type of all the other objects to be passed to the backend implementation.
      * @param first First object to be passed to the backend implementation.
      * @param args The list of all the other objects to be passed to the backend implementation.
      */
     template <class T, class... Args>
     void operator()( T&& first, Args&&... args ) const 
      {
       if constexpr ( std::is_base_of_v <std::ostream, std::remove_reference_t<T>> ) 
         print_backend( std::forward<T>( first ), std::forward<Args>( args )... );
       else 
         print_backend( std::cout, std::forward<T>( first ), std::forward<Args>( args )... );
      }

     // No arguments case
     /**
      * @brief Template operator redefinition used to print an empty line on the screen. This is the no argument case overload. Can be used with "ptc::print()" or "ptc::print( ostream_name )".
      * 
      * @param os The stream in which you want to print the output.
      */
     void operator () ( std::ostream& os = std::cout ) const
      {
       os << getEnd();
       if ( getFlush() ) os << std::flush;
      }
     
    private:

     //====================================================
     //     Private structs
     //====================================================

     // null_string
     /**
      * @brief Struct used to define the "null_str" constant. This workaround is needed for correct compilation in both gcc and clang.
      * 
      * @tparam T The template parameter of the future "null_string" constant.
      */
     template <class T> 
     struct null_string { inline static const std::string value = ""; };

     //====================================================
     //     Private methods
     //====================================================

     // is_escape
     /**
      * @brief This method is used to check if an input variable is an ANSI escape sequency or not.
      * 
      * @param str The input variable.
      * @return true If the input variable is an ANSI escape sequency.
      * @return false Otherwise.
      */
     inline bool is_escape( const std::string_view& str ) const { return ! str.rfind( "\033", 0 ); }

     // print_backend
     /**
      * @brief Backend implementation of the () operator overloads to print to the output stream.
      * 
      * @tparam T_os The type of the output stream object.
      * @tparam T Generic type of first object to be printed.
      * @tparam Args Generic type of all the other objects to be printed.
      * @param os The stream in which you want to print the output.
      * @param first First printed object.
      * @param args The list of objects to be printed on the screen.
      */
     template <class T_os, class T, class... Args>
     void print_backend( T_os&& os, T&& first, Args&&... args ) const 
      {
       std::lock_guard <std::mutex> lock{ mutex_ };
 
       os << first;
       if constexpr( sizeof...( args ) > 0 ) 
        {
         if ( first == null_str <decltype( first )> || is_escape( first ) ) ( ( os << args << getSep() ), ...); 
         else ( ( os << getSep() << args ), ...);
        }
       os << getEnd();
       if ( getFlush() && ! std::is_base_of_v <std::ostringstream, T_os> ) os << std::flush;
      }

     //====================================================
     //     Private attributes
     //====================================================
     std::string end, sep;
     static std::mutex mutex_;
     bool flush;

     //====================================================
     //     Private constants
     //====================================================
     template <class T> inline static const std::string null_str = __print__::null_string<const T&>::value;
   }; // end of __print__ class
   
  //====================================================
  //     Other steps
  //====================================================

  // __print__::mutex_ definiton
  std::mutex __print__::mutex_;

  // print function initialization
  __print__ print;
 } // end of namespace ptc

#endif