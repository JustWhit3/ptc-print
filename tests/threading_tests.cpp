//====================================================
//     Preprocessor directives
//====================================================
#define PTC_ENABLE_GETTERS_FOR_UNIT_TESTS

//====================================================
//     Headers
//====================================================

// My headers
#include <include/ptc/print.hpp>

// STD headers
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <chrono>
#include <optional>
#include <tuple>

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
    ptc::Print <char> first;
 
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

    ptc::print.setPattern( "|" );
    ptc::print( "Testing", "this", "pattern", 123 );
    ptc::print.setPattern( "" );

    // Other ostream objects
    ptc::wprint();
    ptc::wprint( std::wcout, "Testing std::wcout!" );

    #if ! defined( PTC_ENABLE_PERFORMANCE_IMPROVEMENTS ) && ! defined( __APPLE__ )

    std::basic_ostringstream<char16_t> oss16;
    ptc::print16( oss16, "Hello" );

    std::basic_ostringstream<char32_t> oss32;
    ptc::print32( oss32, "Hello" );

    #endif

    // Non built-in types
    std::complex<int> cmplx_no( 2, 3 );
    ptc::print( cmplx_no );
    std::vector <int> vec = { 1 ,2, 3 };
    ptc::print( vec );
    std::map <int,int> map = { { 1,2 }, { 2, 2 }, { 3, 3 } };
    ptc::print( map );
    int arr[3] = { 1, 2, 3 };
    ptc::print( arr );

    std::stack<int> my_stack;
    my_stack.push( 12 );
    my_stack.push( 8 );
    ptc::print( "Printing an std::stack:", my_stack );

    ptc::print( std::chrono::seconds( 5 ) );

    std::optional <int> opt = 3;
    ptc::print( "Printing an std::optional:", opt );

    #if defined( __GNUC__ ) && ( __GNUC___ == 12 )
    std::tuple<int, int, int> tuple = std::make_tuple( 3, 4, 5 );
    ptc::print( "Printing an std::tuple:", tuple );
    #endif

    int add = 2;
    int *pointer;
    pointer = &add;
    ptc::print( "Printing information of a pointer:" );
    ptc::print( ptc::ptr( pointer ) );
   };

  std::thread first_job( job1 );
  std::thread second_job( job1 );

  first_job.join();
  second_job.join();

  file_stream.close();
 }