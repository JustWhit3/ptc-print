//====================================================
//     headers
//====================================================

// My headers
#include "ptc/print.hpp"

// STD headers
#include <iostream>
#include <fstream>
#include <sstream>

//====================================================
//     main
//====================================================
int main()
 {
  // Print with stdout
  ptc::print( "Print", "with", "stdout." );

  // Print a new line
  ptc::print();

  // Print with stderr (or other ostream objects)
  ptc::print( std::cerr, "Print", "with", "stderr." );
  ptc::print( std::cerr );

  // Print by changing the "end" variable value (and/or type)
  ptc::print.setEnd( '.' );
  ptc::print( "Test" );
  ptc::print();
  ptc::print.setEnd( "\n" );
  ptc::print( "\n" );

  // Print by changing the "sep" variable value (and/or type)
  ptc::print.setSep( '*' );
  ptc::print( "Test", "the", "new", "sep." );
  ptc::print();
  ptc::print.setSep( " " );

  // Print ostringstream
  std::ostringstream strout;
  ptc::print( strout, "Printing", "with an std::ostringstream object." );
  std::cout << strout.str();

  // Printing on a file
  std::ofstream file_stream;
  file_stream.open( "file.txt", std::ios::trunc );
  ptc::print( file_stream, "You can also write in a file! ", 1, 2, 3, 4.5, 7 );
  file_stream.close();
  ptc::print( "Text has been wrote to ", "file.txt ", "file!" );
 }