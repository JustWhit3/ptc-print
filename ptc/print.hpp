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
     //     Setters declaration
     //====================================================
     template <typename T> void setEnd( const T& end_val );

     //====================================================
     //     Getters declaration
     //====================================================
     auto getEnd() const;

     //====================================================
     //     Operators declaration
     //====================================================
     template <typename T, typename... Args> 
     const std::ostream& operator () ( std::ostream& os, const T& first, const Args&... args );
     template <typename T, typename... Args> 
     const std::ostream& operator () ( const T& first, const Args&... args );
     const std::ostream& operator () ( std::ostream& os = std::cout );

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
  template <typename T, typename... Args>
  inline const std::ostream& __print__::operator () ( std::ostream& os, const T& first, const Args&... args )
   {    
    os << first;
    if constexpr( sizeof...( args ) > 0 ) ( ( os << " " << args ), ...);
    current_os = &os;
    os << getEnd();
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
  template <typename T, typename... Args>
  inline const std::ostream& __print__::operator () ( const T& first, const Args&... args )
   {
    std::cout << first;
    if constexpr( sizeof...( args ) > 0 ) ( ( std::cout << " " << args ), ...);
    current_os = &std::cout;
    std::cout << getEnd();
    return std::cout;
   }

  //====================================================
  //     Operator () (no arguments case)
  //====================================================
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen. This is the no argument case overload. Can be used with "ptc::print()" or "ptc::print( ostream_name )".
   * 
   * @param os The stream in which you want to print the output.
   * @return const std::ostream& The stream within the objects you choose to print.
   */
  inline const std::ostream& __print__::operator () ( std::ostream& os )
   {
    os << end;
    return os;
   }

  //====================================================
  //     setEnd initialization
  //====================================================
  /**
   * @brief Setter used to set the value of the "end" variable.
   * 
   * @tparam T The type of the expression inserted to set the value of "end" variable.
   * @param end_val The inserted expression used to set the value of "end" variable.
   */
  template <typename T>
  inline void __print__::setEnd( const T& end_val )
   {
    end = end_val;
   }

  //====================================================
  //     getEnd initialization
  //====================================================
  /**
   * @brief Getter used to get the value of the "end" variable.
   * 
   * @return auto The value of the end variable.
   */
  inline auto __print__::getEnd() const
   {
    return end;
   }

  //====================================================
  //     print function initialization
  //====================================================
  __print__ print;
 }

#endif