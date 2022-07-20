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

namespace ptc
 {
  //====================================================
  //     ptc_print class
  //====================================================
  /**
   * @brief Class used to construct the print function.
   * 
   */
  class __print__
   {
     //====================================================
     //     Private structs
     //====================================================

     // is_any
     /**
      * @brief Template struct used to check if a type is in a certain list.
      * 
      * @tparam T The type which check is needed.
      * @tparam Ts The list of types to compare with T.
      */
     template <class T, class... Ts>
     struct is_any: std::disjunction <std::is_same <T, Ts>... >{};

     //====================================================
     //     Private methods
     //====================================================


     //====================================================
     //     Private attributes declaration
     //====================================================
     std::string end, sep;
     static std::mutex mutex_;
     bool flush;

    public:

     //====================================================
     //     Constructors / destructor declaration
     //====================================================
     __print__();
     ~__print__();

     //====================================================
     //     Public setters declaration
     //====================================================
     template <class T> const __print__& setEnd( const T& end_val );
     template <class T> const __print__& setSep( const T& sep_val );
     const __print__& setFlush( const bool& flush_val );

     //====================================================
     //     Public getters declaration
     //====================================================
     const auto& getEnd() const;
     const auto& getSep() const;
     const bool& getFlush() const;

     //====================================================
     //     Operator () overloads declaration
     //====================================================

     // General case
     template <class T_os, class T, class... Args, typename = std::enable_if_t<is_any
     <T_os, std::ostream, std::ofstream, std::fstream, std::ostringstream>::value>>
     const __print__& operator () ( T_os& os, const T& first, const Args&... args ) const;

     // Default stdout case
     template <class T, class... Args> 
     const __print__& operator () ( const T& first, const Args&... args ) const;

     // No arguments case
     const __print__& operator () ( std::ostream& os = std::cout ) const;
   };
   
  //====================================================
  //     Attributes definition
  //====================================================
  std::mutex __print__::mutex_;

  //====================================================
  //     Constructors / destructor definition
  //====================================================

  // Default constructor
  /**
   * @brief Default constructor of the __print__ class.
   * 
   */
  __print__::__print__():
   end( "\n" ),
   sep( " " ),
   flush( false )
   {}

  // Destructor
  /**
   * @brief Destructor of the __print__ class. It resets the output stream from ANSI escape sequences (such as color and styles) manipulations.
   * 
   */
  __print__::~__print__()
   { 
    std::lock_guard <std::mutex> lock{ mutex_ };
    
    std::cout << "\033[0m";
    std::cout << "\033[0m";
    std::cout << "\033[0m";
   }

  //====================================================
  //     Setters definition
  //====================================================

  // setEnd
  /**
   * @brief Setter used to set the value of the "end" variable.
   * 
   * @tparam T The type of the expression inserted to set the value of "end" variable.
   * @param end_val The inserted expression used to set the value of "end" variable.
   * @return const __print__& The this pointer to the class.
   */
  template <class T>
  inline const __print__& __print__::setEnd( const T& end_val )
   {
    end = end_val;
    return *this;
   }

  // setSep
  /**
   * @brief Setter used to set the value of the "sep" variable.
   * 
   * @tparam T The type of the expression inserted to set the value of "sep" variable.
   * @param end_val The inserted expression used to set the value of "sep" variable.
   * @return const __print__& The this pointer to the class.
   */
  template <class T>
  inline const __print__& __print__::setSep( const T& sep_val )
   {
    sep = sep_val;
    return *this;
   }

  // setFlush
  /**
   * @brief Setter used to set the value of the "flush" variable.
   * 
   * @param flush_val The inserted expression used to set the value of the "flush" variable.
   * @return const __print__& The this pointer to the class.
   */
  inline const __print__& __print__::setFlush( const bool& flush_val )
   {
    flush = flush_val;
    return *this;
   }

  //====================================================
  //     Getters definition
  //====================================================

  // getEnd
  /**
   * @brief Getter used to get the value of the "end" variable.
   * 
   * @return auto The value of the "end" variable.
   */
  inline const auto& __print__::getEnd() const
   {
    return end;
   }

  // getSep
  /**
   * @brief Getter used to get the value of the "sep" variable.
   * 
   * @return auto The value of the "sep" variable.
   */
  inline const auto& __print__::getSep() const
   {
    return sep;
   }

  // getFlush
  /**
   * @brief Getter used to get the value of the "flush" variable.
   * 
   * @return bool The value of the "flush" variable.
   */
  inline const bool& __print__::getFlush() const
   {
    return flush;
   }

  //====================================================
  //     Operator () overloads definition
  //====================================================

  // General case
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen, using the os ostream.
   * 
   * @tparam T_os The type of the output stream object. Can be std::ofstream, std::fstream, std::ostringstream or std::ostream.
   * @tparam T Generic type of first object to be printed.
   * @tparam Args Generic type of objects to be printed.
   * @param os The stream in which you want to print the output.
   * @param first First printed object.
   * @param args The list of objects to be printed on the screen.
   * @return const __print__& The this pointer to the class.
   */
  template <class T_os, class T, class... Args, typename>
  inline const __print__& __print__::operator () ( T_os& os, const T& first, const Args&... args ) const
   {    
    std::lock_guard <std::mutex> lock{ mutex_ };
    
    os << first;
    if constexpr( sizeof...( args ) > 0 ) ( ( os << getSep() << args ), ...);
    os << getEnd();

    if ( getFlush() == true && !std::is_same <T_os, std::ostringstream>::value ) os << std::flush;

    return *this;
   }

  // Standard stdout case
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen, using the stdout stream.
   * 
   * @tparam T Generic type of first object to be printed.
   * @tparam Args Generic type of objects to be printed.
   * @param first First printed object.
   * @param args The list of objects to be printed on the screen.
   * @return const __print__& The this pointer to the class.
   */
  template <class T, class... Args>
  inline const __print__& __print__::operator () ( const T& first, const Args&... args ) const
   {
    std::lock_guard <std::mutex> lock{ mutex_ };

    std::cout << first;
    if constexpr( sizeof...( args ) > 0 ) ( ( std::cout << getSep() << args ), ...);
    std::cout << getEnd();
    if ( getFlush() == true ) std::cout << std::flush;

    return *this;
   }

  // No arguments case
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen. This is the no argument case overload. Can be used with "ptc::print()" or "ptc::print( ostream_name )".
   * 
   * @param os The stream in which you want to print the output.
   * @return const __print__& The this pointer to the class.
   */
  inline const __print__& __print__::operator () ( std::ostream& os ) const
   {
    std::lock_guard <std::mutex> lock{ mutex_ };

    os << getEnd();
    if ( getFlush() == true ) os << std::flush;

    return *this;
   }

  //====================================================
  //     print function initialization
  //====================================================
  __print__ print;
 } // namespace ptc

#endif