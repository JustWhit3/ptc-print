//====================================================
//     headers
//====================================================

// My headers
#include "../ptc/print.hpp"

// STD headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

//====================================================
//     print_out
//====================================================
void print_out()
 {
  std::cout << "\n" << "======================================================" << "\n"
            << "     Print out                                           " << "\n"
            << "======================================================" << "\n";

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
  ptc::print( strout, "I am an", "std::ostringstream object!" );
  ptc::print( strout.str() );

  // Printing on a file
  std::ofstream file_stream( "test.txt", std::ios::trunc );
  ptc::print( file_stream, "You can also write in a file! ", 1, 2, 3, 4.5, 7 );
  file_stream.close();
  ptc::print( "Text has been wrote to", "test.txt", "file!" );

  // Printing with std::flush
  ptc::print.setFlush( true );
  ptc::print( "Printing", "with std::flush on." );
  ptc::print.setFlush( false );

  // Passing variables into print
  std::string var = "This var";
  ptc::print( var, "is printed." );
 }

//====================================================
//     threading
//====================================================
void threading()
 {
  std::cout << "\n" << "======================================================" << "\n"
            << "     Threading                                           " << "\n"
            << "======================================================" << "\n";

  // Variables
  std::ostringstream strout;
  std::ofstream file_stream;

  file_stream.open( "test.txt", std::ios::trunc );

  // First job
  auto job1 = [ &strout, &file_stream ]() 
   {
    //ptc::__print__ first;
    ptc::print( std::cerr, "Printing the", "1st", "message with std::cerr" ); 
    ptc::print.setEnd( "\n" );
    ptc::print.setSep( " " );
    ptc::print.setFlush( false );
    ptc::print( "Printing the", "1st", "message " ); 
    ptc::print();
    ptc::print.getEnd();
    ptc::print.getSep();
    ptc::print.getFlush();

    ptc::print( strout, "Printing the", "1st", "message with std::ostringstream" );
    ptc::print( strout.str() );

    ptc::print( file_stream, "Printing the", "1st", "message with std::ofstream" );
   };

  // Second job
  auto job2 = [ &strout, &file_stream ]()
   {
    //ptc::__print__ second;
    ptc::print( std::cerr, "Printing the", "2nd", "message with std::cerr" ); 
    ptc::print.setEnd( "\n" );
    ptc::print.setSep( " " );
    ptc::print.setFlush( false );
    ptc::print( "Printing the", "2nd", "message" );
    ptc::print();
    ptc::print.getEnd();
    ptc::print.getSep();
    ptc::print.getFlush();
    
    ptc::print( strout, "Printing the", "2nd", "message with std::ostringstream" );
    ptc::print( strout.str() );

    ptc::print( file_stream, "Printing the", "2nd", "message with std::ofstream" );
   };

  std::thread first_job(job1);
  std::thread second_job(job2);

  first_job.join();
  second_job.join();

  file_stream.close();
 }

//====================================================
//     main
//====================================================
int main()
 {
  print_out();
  threading();
 }