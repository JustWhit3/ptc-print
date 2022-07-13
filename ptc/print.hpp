//====================================================
//     Preprocessor directives
//====================================================
#ifndef PRINT_HPP
#define PRINT_HPP

//====================================================
//     Headers
//====================================================

// Extra headers
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/null.hpp>

// STD headers
#include <iostream>
#include <string>
#include <type_traits>

namespace ptc
 {
  //====================================================
  //     ptc_print class
  //====================================================
  /**
   * @brief Class used to construct the print function.
   * 
   */
  class PtcPrint
   {
    public:

     //====================================================
     //     Constructors / Destructors declaration
     //====================================================
     PtcPrint();
     ~PtcPrint();

     //====================================================
     //     Operators declaration
     //====================================================
     template <typename... Args>
     const std::ostream& operator () ( std::ostream& os = null_stream, const Args&... args );
     // Another overload for the standard stream case and 0 arguments case

    private:

     //====================================================
     //     Variables declaration
     //====================================================
     std::string end;
     std::ostream* current_os;

     //====================================================
     //     Constants declaration
     //====================================================
     static const boost::iostreams::stream<boost::iostreams::null_sink> null_stream;
   };

  //====================================================
  //     Constants definition
  //====================================================
  const boost::iostreams::stream<boost::iostreams::null_sink> PtcPrint::null_stream = boost::iostreams::null_sink{} ;

  //====================================================
  //     Default constructor definition
  //====================================================
  /**
   * @brief Default constructor of the PtcPrint class.
   * 
   */
  PtcPrint::PtcPrint(): 
   end( "\n" ) 
   {}

  //====================================================
  //     Destructor definition
  //====================================================
  /**
   * @brief Destructor of the PtcPrint class.
   * 
   */
  PtcPrint::~PtcPrint()
   {
    // Destructor which resets all
    // std::is_same_v<std::ostream, decltype(obj)>
   }

  //====================================================
  //     Operator () first overload definition
  //====================================================
  /**
   * @brief Template operator redefinition used to print the content of the args argument on the screen.
   * 
   * @tparam Args Generic type of objects to be printed.
   * @param os The stream in which you want to print the output.
   * @param args The list of objects to be printed on the screen.
   * @return const std::ostream& The stream within the objects you choose to print.
   */
  template <typename... Args>
  inline const std::ostream& PtcPrint::operator () ( std::ostream& os, const Args&... args )
   {
    if( &os == &null_stream ) std::cout << end;
    ( os << ... << args ) << end;
    current_os = os;

    return os;
   }
  // TODO: mancano gli spazi tra ogni cosa printata

  //====================================================
  //     print function initialization
  //====================================================
  PtcPrint print;
 }

#endif