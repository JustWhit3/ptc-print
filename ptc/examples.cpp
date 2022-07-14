//====================================================
//     headers
//====================================================

// My headers
#include "print.hpp"

// STD headers
#include <iostream>

//====================================================
//     main
//====================================================
int main()
 {
  // Print with stdout
  ptc::print( "Print", "with", "stdout." );
  ptc::print();

  // Print with stderr (or other streams)
  ptc::print( std::cerr, "Print", "with", "stderr." );
  ptc::print( std::cerr );

  // Print changing the "end" variable value (and/or type)
  ptc::print.setEnd( "." );
  ptc::print( "Test" );
  ptc::print();
 }