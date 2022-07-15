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
#include <fstream>

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
     //     Public setters declaration
     //====================================================
     template <class T> void setEnd( const T& end_val );
     template <class T> void setSep( const T& sep_val );

     //====================================================
     //     Public getters declaration
     //====================================================
     auto getEnd() const;
     auto getSep() const;

     //====================================================
     //     Public operators overload declaration
     //====================================================
     template <class T, class... Args> std::ostream& operator () ( std::ostream& os, const T& first, const Args&... args );
     template <class T, class... Args> std::ostream& operator () ( const T& first, const Args&... args );
     std::ostream& operator () ( std::ostream& os = std::cout );
     template <class T, class... Args> std::ostringstream& operator () ( std::ostringstream& os, const T& first, const Args&... args );
     template <class T, class... Args> std::ofstream& operator () ( std::ofstream& os, const T& first, const Args&... args );

    private:

     //====================================================
     //     Private variables declaration
     //====================================================
     std::string end, sep;
   };

  //====================================================
  //     Default constructor definition
  //====================================================
  /**
   * @brief Default constructor of the __print__ class.
   * 
   */
  __print__::__print__():
   end( "\n" ),
   sep( " " )
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
    std::cout << "\033[0m";
    std::cerr << "\033[0m";
    std::clog << "\033[0m";
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
  template <class T>
  inline void __print__::setEnd( const T& end_val )
   {
    end = end_val;
   }

  //====================================================
  //     setSep initialization
  //====================================================
  /**
   * @brief Setter used to set the value of the "sep" variable.
   * 
   * @tparam T The type of the expression inserted to set the value of "sep" variable.
   * @param end_val The inserted expression used to set the value of "sep" variable.
   */
  template <class T>
  inline void __print__::setSep( const T& sep_val )
   {
    sep = sep_val;
   }

  //====================================================
  //     getEnd initialization
  //====================================================
  /**
   * @brief Getter used to get the value of the "end" variable.
   * 
   * @return auto The value of the "end" variable.
   */
  inline auto __print__::getEnd() const
   {
    return end;
   }

  //====================================================
  //     getSep initialization
  //====================================================
  /**
   * @brief Getter used to get the value of the "sep" variable.
   * 
   * @return auto The value of the "sep" variable.
   */
  inline auto __print__::getSep() const
   {
    return sep;
   }

  //====================================================
  //     Operator ()
  //====================================================
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen, using the os ostream.
   * 
   * @tparam T Generic type of first object to be printed.
   * @tparam Args Generic type of objects to be printed.
   * @param os The stream in which you want to print the output.
   * @param args The list of objects to be printed on the screen.
   * @return const std::ostream& The stream within the objects you choose to print.
   */
  template <class T, class... Args>
  inline std::ostream& __print__::operator () ( std::ostream& os, const T& first, const Args&... args )
   {    
    // Output
    os << first;
    if constexpr( sizeof...( args ) > 0 ) ( ( os << getSep() << args ), ...);
    os << getEnd();

    // Return
    return os;
   }

  //====================================================
  //     Operator () (standard stdout case)
  //====================================================
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen, using the stdout stream.
   * 
   * @tparam T Generic type of first object to be printed.
   * @tparam Args Generic type of objects to be printed.
   * @param args The list of objects to be printed on the screen.
   * @return const std::ostream& The stream within the objects you choose to print.
   */
  template <class T, class... Args>
  inline std::ostream& __print__::operator () ( const T& first, const Args&... args )
   {
    // Output
    std::cout << first;
    if constexpr( sizeof...( args ) > 0 ) ( ( std::cout << getSep() << args ), ...);
    std::cout << getEnd();

    // Return
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
  inline std::ostream& __print__::operator () ( std::ostream& os )
   {
    os << end;
    return os;
   }

  //====================================================
  //     Operator () (std::ostringstream case)
  //====================================================
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen, using the os ostringstream.
   * 
   * @tparam T Generic type of first object to be printed.
   * @tparam Args Generic type of objects to be printed.
   * @param os The stream in which you want to print the output.
   * @param args The list of objects to be printed on the screen.
   * @return const std::ostringstream& The stream within the objects you choose to print.
   */
  template <class T, class... Args> 
  inline std::ostringstream& __print__::operator () ( std::ostringstream& os, const T& first, const Args&... args )
   {
    // Output
    os << first;
    if constexpr( sizeof...( args ) > 0 ) ( ( os << getSep() << args ), ...);
    os << getEnd();

    // Return
    return os;
   }

  //====================================================
  //     Operator () (std::ofstream case)
  //====================================================
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen, using the os ofstream.
   * 
   * @tparam T Generic type of first object to be printed.
   * @tparam Args Generic type of objects to be printed.
   * @param os The stream in which you want to print the output.
   * @param args The list of objects to be printed on the screen.
   * @return const std::ofstream& The stream within the objects you choose to print.
   */
  template <class T, class... Args> 
  inline std::ofstream& __print__::operator () ( std::ofstream& os, const T& first, const Args&... args )
   {
    // Output
    os << first;
    if constexpr( sizeof...( args ) > 0 ) ( ( os << getSep() << args ), ...);
    os << getEnd();

    // Return
    return os;
   }

  //====================================================
  //     print function initialization
  //====================================================
  __print__ print;
 }

#endif