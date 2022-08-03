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

namespace ptc
 {
  //====================================================
  //     ptc_print class
  //====================================================
  /**
   * @brief Enum class used to set up the "str" mode to pass a string with the content of the print function.
   * 
   */
   enum class mode { str };

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
      * @brief Destructor of the __print__ class.
      * 
      */
     ~__print__(){}

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
     inline void setEnd( const T& end_val )
      {
       end = end_val;
      }

     // setSep
     /**
      * @brief Setter used to set the value of the "sep" variable.
      * 
      * @tparam T The type of the expression inserted to set the value of "sep" variable.
      * @param end_val The inserted expression used to set the value of "sep" variable.
      */
     template <class T>
     inline void setSep( const T& sep_val )
      {
       sep = sep_val;
      }

     // setFlush
     /**
      * @brief Setter used to set the value of the "flush" variable.
      * 
      * @param flush_val The inserted expression used to set the value of the "flush" variable.
      */
     inline void setFlush( const bool& flush_val )
      {
       flush = flush_val;
      }

     //====================================================
     //     Public getters
     //====================================================

     // getEnd
     /**
      * @brief Getter used to get the value of the "end" variable.
      * 
      * @return auto The value of the "end" variable.
      */
     inline const auto& getEnd() const 
      {
       return end;
      }

     // getSep
     /**
      * @brief Getter used to get the value of the "sep" variable.
      * 
      * @return auto The value of the "sep" variable.
      */
     inline const auto& getSep() const
      {
       return sep;
      }

     // getFlush
     /**
      * @brief Getter used to get the value of the "flush" variable.
      * 
      * @return bool The value of the "flush" variable.
      */
     inline const bool& getFlush() const
      {
       return flush;
      }

     //====================================================
     //     Public operator () overloads
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
     const __print__& operator()( T&& first, Args&&... args ) const
      {
       if constexpr ( std::is_base_of_v <std::ostream, std::remove_reference_t<T>> )
        {
         print_backend( std::forward<T>( first ), std::forward<Args>( args )... );
        }
       else
        {
         print_backend( std::cout, std::forward<T>( first ), std::forward<Args>( args )... );
        }
       return *this;
      }

     // String initialization case
     /**
      * @brief Frontend implementation of the () operator overload to initialize its content with an std::string object. The backend implementation is called in the required variation. This overload is required in order to hide the output of the "print_backend" function during the initialization.
      * 
      * @tparam Args Generic type of all the other objects to be passed to the backend implementation.
      * @param first First object to be passed to the backend implementation.
      * @param args The list of all the other objects to be passed to the backend implementation.
      * @return const std::string The whole print content in std::string format.
      */
     template <class... Args>
     const std::string operator()( mode&& first, Args&&... args ) const
      {    
       if constexpr( sizeof...( args ) > 0 )
        {
         switch( first )
          {
           case mode::str:
            {
             std::ostringstream oss;
             print_backend( oss, std::forward<Args>( args )... );
             return oss.str();
            }
          }
        }
       return "";
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
     struct null_string
      {
       inline static const std::string value = "";
      };

     //====================================================
     //     Private methods
     //====================================================

     // is_escape
     /**
      * @brief This method is used to check if an input variable is an ANSI escape sequency or not.
      * 
      * @tparam T Template type of the input variable.
      * @param str The input variable.
      * @param flag A flag which let to return different things with respect to its value. If flag = 0 the ANSI is searched as the first substring of the str argument, otherwise, if flag = 1 the ANSI is searched as a substring inside the str argument.
      * @return true If the input variable is an ANSI escape sequency.
      * @return false Otherwise.
      */
     template <typename T>
     static constexpr bool is_escape( const T& str, const unsigned short& flag = 1 )
      {
       if constexpr( std::is_convertible_v <T, std::string_view> )
        {
         switch( flag )
          {
           case( 0 ): 
            {
             return ( ! std::string_view( str ).rfind( "\033", 0 ) ) && ( std::string_view( str ).length() < 7 );
            }
           case( 1 ):
            {
             return ( std::string_view( str ).find( "\033" ) != std::string_view::npos );
            }
          }
        }
       return false;
      }

     // is_null_str
     /**
      * @brief This method is used to check if an input variable is a null string or not.
      * 
      * @tparam T The templated type of the input variable.
      * @param str The input variable.
      * @return true If the variable is a null string.
      * @return false Otherwise.
      */
     template <typename T>
     static constexpr bool is_null_str( const T& str )
      {
       if constexpr( std::is_convertible_v <T, std::string_view> )
        {
         return str == null_str <T>;
        }
       return false;
      }
      
     // print_backend
     /**
      * @brief Backend implementation of the () operator overloads to print to the output stream. The stream is automatically reset in case of an ANSI escape sequence is sent to output.
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
 
       // Printing all the arguments
       os << first;
       if constexpr( sizeof...( args ) > 0 ) 
        {
         if ( is_null_str( first ) || is_escape( first, 0 ) ) ( ( os << args << getSep() ), ...); 
         else ( ( os << getSep() << args ), ...);
        }
       os << getEnd();

       // Resetting the stream from ANSI escape sequences
       if constexpr( sizeof...( args ) > 0 )
        {
         if ( is_escape( first ) || ( ( is_escape( args ) ) || ...) ) os << "\033[0m";
        }
       else 
        {
        if ( is_escape( first ) ) os << "\033[0m";
        }
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
  inline std::mutex __print__::mutex_;

  // print function initialization
  inline __print__ print;
 } // end of namespace ptc

#endif