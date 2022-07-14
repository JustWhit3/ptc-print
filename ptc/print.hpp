//====================================================
//     Preprocessor directives
//====================================================
#ifndef PRINT_HPP
#define PRINT_HPP

//====================================================
//     Headers
//====================================================

// STD headers
#include <iostream>
#include <string>
#include <type_traits>
#include <sstream>

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
    public:

     //====================================================
     //     Constructors / Destructors declaration
     //====================================================
     __print__();
     ~__print__();

     //====================================================
     //     Operators declaration
     //====================================================
     template <typename... Args> const std::ostream& operator () ( std::ostream& os, const Args&... args );
     template <typename... Args> const std::ostream& operator () ( const Args&... args );

    private:

     //====================================================
     //     Variables declaration
     //====================================================
     std::string end;
     std::ostream* current_os;
   };

  //====================================================
  //     Default constructor definition
  //====================================================
  /**
   * @brief Default constructor of the __print__ class.
   * 
   */
  __print__::__print__(): 
   end( "\n" ) 
   {}

  //====================================================
  //     Destructor definition
  //====================================================
  /**
   * @brief Destructor of the __print__ class.
   * 
   */
  __print__::~__print__()
   {
    bool is_ostream = std::is_same_v <std::ostream, decltype( current_os ) >;
    bool is_ostringstream = std::is_same_v <std::ostringstream, decltype( current_os ) >;
    
    if ( is_ostream || is_ostringstream ) *current_os << "\033[0m";
   }

  //====================================================
  //     Operator ()
  //====================================================
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen, using the os ostream.
   * 
   * @tparam Args Generic type of objects to be printed.
   * @param os The stream in which you want to print the output.
   * @param args The list of objects to be printed on the screen.
   * @return const std::ostream& The stream within the objects you choose to print.
   */
  template <typename... Args>
  inline const std::ostream& __print__::operator () ( std::ostream& os, const Args&... args )
   {
    ( os << ... << args ) << end;
    current_os = &os;
    return os;
   }

  //====================================================
  //     Operator () (standard stdout case)
  //====================================================
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen, using the stdout stream.
   * 
   * @tparam Args Generic type of objects to be printed.
   * @param args The list of objects to be printed on the screen.
   * @return const std::ostream& The stream within the objects you choose to print.
   */
  template <typename... Args>
  inline const std::ostream& __print__::operator () ( const Args&... args )
   {
    ( std::cout << ... << args ) << end;
    current_os = &std::cout;
    return std::cout;
   }

  //====================================================
  //     print function initialization
  //====================================================
  __print__ print;
 }

#endif