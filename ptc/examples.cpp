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
  ptc::print( "Print", "with", "std::cout." );

  ptc::print();

  ptc::print( std::cerr, "Print", "with", "std::cerr." );

  ptc::print( std::cerr );
 }