//====================================================
//     headers
//====================================================

// My headers
#include "../include/ptc/print.hpp"

// STD headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

//====================================================
//     main
//====================================================
int main()
 {
  // Variables
  std::ostringstream strout;
  std::ofstream file_stream;

  file_stream.open( "test.txt", std::ios::trunc );

  // First job
  auto job1 = [ &strout, &file_stream ]() 
   {
    // Testing constructor
    ptc::__print__ first;
 
    // Testing methods
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

    std::string str_out = ptc::print( ptc::mode::str, "This", "is the 1st string!" );
   };

  // Second job
  auto job2 = [ &strout, &file_stream ]()
   {
    // Testing constructor
    ptc::__print__ second;

    // Testing methods
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

    std::string str_out = ptc::print( ptc::mode::str, "This", "is the 2nd string!" );
   };

  std::thread first_job(job1);
  std::thread second_job(job2);

  first_job.join();
  second_job.join();

  file_stream.close();
 }