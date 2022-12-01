//====================================================
//     Preprocessor directives
//====================================================
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#define PTC_ENABLE_GETTERS_FOR_UNIT_TESTS

//====================================================
//     Headers
//====================================================

// My headers
#include <include/ptc/print.hpp>
#include "utils.hpp"

// Extra headers
#include <doctest/doctest.h>

// STD headers
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <complex>
#include <chrono>

// Containers for testing
#include <vector>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <optional>

//====================================================
//     Namespaces
//====================================================
using namespace std::literals::chrono_literals;

//====================================================
//     Utils
//====================================================
TEST_CASE( "Testing utils." )
 {
  // StringConverter
  SUBCASE( "Testing StringConverter function." )
   {
    // char
    CHECK_EQ( ptc::StringConverter<char>( "Hello" ), "Hello" );
    CHECK_EQ( ptc::StringConverter<char>( "Test a long string" ), "Test a long string" );
    CHECK_EQ( ptc::StringConverter<char>( "" ), "" );

    // wchar_t
    CHECK_EQ( ptc::StringConverter<wchar_t>( "Hello" ), L"Hello" );
    CHECK_EQ( ptc::StringConverter<wchar_t>( "Test a long string" ), L"Test a long string" );
    CHECK_EQ( ptc::StringConverter<wchar_t>( "" ), L"" );

    // char16_t
    CHECK_EQ( ptc::StringConverter<char16_t>( "Hello" ), u"Hello" );
    CHECK_EQ( ptc::StringConverter<char16_t>( "Test a long string" ), u"Test a long string" );
    CHECK_EQ( ptc::StringConverter<char16_t>( "" ), u"" );

    // char32_t
    CHECK_EQ( ptc::StringConverter<char32_t>( "Hello" ), U"Hello" );
    CHECK_EQ( ptc::StringConverter<char32_t>( "Test a long string" ), U"Test a long string" );
    CHECK_EQ( ptc::StringConverter<char32_t>( "" ), U"" );

    // char8_t
    #if ( __cplusplus >= 202002L )
    CHECK_EQ( ptc::StringConverter<char8_t>( "Hello" ), u8"Hello" );
    CHECK_EQ( ptc::StringConverter<char8_t>( "Test a long string" ), u8"Test a long string" );
    CHECK_EQ( ptc::StringConverter<char8_t>( "" ), u8"" );
    #endif
   }

  // select_cout
  SUBCASE( "Testing select_cout." )
   {
    CHECK_EQ( &ptc::select_cout<char>::cout, &std::cout );
    CHECK_EQ( &ptc::select_cout<wchar_t>::cout, &std::wcout );
   }

  #ifdef PTC_ENABLE_PERFORMANCE_IMPROVEMENTS

  // select_cin
  SUBCASE( "Testing select_cin." )
   {
    CHECK_EQ( &ptc::select_cin<char>::cin, &std::cin );
    CHECK_EQ( &ptc::select_cin<wchar_t>::cin, &std::wcin );
   }

  #endif
 }

//====================================================
//     Print default constructor
//====================================================
TEST_CASE( "Testing the Print default constructor." )
 {
  CHECK_EQ( ptc::print.getEnd(), "\n" );
  CHECK_EQ( ptc::print.getSep(), " " );
 }

//====================================================
//     Print operator () overload
//====================================================
TEST_CASE( "Testing the operator () overload." )
 {  
  // General case
  SUBCASE( "General case." )
   {
    const std::string test = ptc::osout( std::cerr, "Test passes", "(ignore this)." );
    CHECK_EQ( test, "Test passes (ignore this). \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // General case with different types
  SUBCASE( "General case." )
   {
    const std::string test = ptc::osout( std::cerr, "Test passes", 123, "(ignore this)", '.' );
    CHECK_EQ( test, "Test passes 123 (ignore this) . \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // General case with no args
  SUBCASE( "General case with no args." )
   {
    const std::string test = ptc::osout( std::clog );
    CHECK_EQ( test, "\n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // stdout case
  SUBCASE( "Stdout case." )
   {
    const std::string test = ptc::osout<char>( "Test passes", "(ignore this)." );
    CHECK_EQ( test, "Test passes (ignore this). \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // No arguments case
  SUBCASE( "No arguments case." )
   {
    std::streambuf* coutbuf = std::cout.rdbuf();
    ptc::savebuf sbuf( coutbuf );
    std::cout.rdbuf( &sbuf );
    ptc::print();
    std::cout.rdbuf( coutbuf );
    CHECK_EQ( sbuf.str(), "\n" );
    CHECK( sbuf.str() != "Test thisssa.\n" );
   }

  // std::ostringstream case
  SUBCASE( "std::ostringstream case." )
   {
    std::ostringstream ostr;
    ptc::print( ostr, "Test", "this." );
    CHECK_EQ( ostr.str(), "Test this.\n" );
    CHECK( ostr.str() != "Test thisssa.\n" );
   }
   
  // std::ofstream case
  SUBCASE( "std::ofstream case." )
   {
    std::ofstream file_stream_o;
    file_stream_o.open( "test.txt", std::ios::trunc );
    ptc::print( file_stream_o, "Test", "passes (ignore this)." );
    file_stream_o.close();

    char str[26];
    std::ifstream file_stream_i;
    file_stream_i.open( "test.txt" );
    file_stream_i.read( str, 26 );
    file_stream_i.close();

    CHECK_EQ( static_cast<std::string> ( str ), "Test passes (ignore this)." );
   }

  // std::fstream case
  SUBCASE( "std::fstream case." )
   {
    std::ofstream file_stream_f;
    file_stream_f.open( "test.txt", std::ios::out | std::ios::trunc );
    ptc::print( file_stream_f, "Test", "passes (ignore this)." );
    file_stream_f.close();

    char str[26];
    std::ifstream file_stream_i;
    file_stream_i.open( "test.txt" );
    file_stream_i.read( str, 26 );
    file_stream_i.close();

    CHECK_EQ( static_cast<std::string> ( str ), "Test passes (ignore this)." );
   }

  // Passing variables inside ptc::print
  SUBCASE( "Passing variables inside ptc::print." )
   {
    std::string str = "Test passes";
    const std::string test = ptc::osout<char>( str, "(ignore this)." );
    CHECK_EQ( test, "Test passes (ignore this). \n" );
    CHECK( test != "Test thisssa.\n" );
   }

  // Testing the string return overload
  SUBCASE( "String return overload" )
   {
    ptc::print.setEnd( "" );

    CHECK_EQ( ptc::print( ptc::mode::str, "Test", "this!" ), "Test this!" );
    const std::string test_string = ptc::print( ptc::mode::str, "Test", "this!" );
    CHECK_EQ( test_string, "Test this!" );
    CHECK_EQ( ptc::print( ptc::mode::str ), "" );
    CHECK_EQ( ptc::print( ptc::mode::str, "" ), "" );

    ptc::print.setEnd( "\n" );
   }

  // Testing usage of ANSI escape sequence and final reset
  SUBCASE( "Testing usage of ANSI escape sequence and final reset." )
   {
    const std::string test_a = ptc::osout<char>( "\033[31mTesting colors", "(ignore this)." );
    CHECK_EQ( test_a, "\033[31mTesting colors (ignore this). \n\033[0m" );

    ptc::print.setEnd( "" );
    const std::string test_b = ptc::print( ptc::mode::str, "Testing", "\033[31mcolors", "(ignore this)." );
    CHECK_EQ( test_b, "Testing \033[31mcolors (ignore this).\033[0m" );
    const std::string test_c = ptc::print( ptc::mode::str, "Testing", "the \033[31mcolors", "(ignore this)." );
    CHECK_EQ( test_c, "Testing the \033[31mcolors (ignore this).\033[0m" );
    CHECK_EQ( ptc::print( ptc::mode::str, 1, "Number" ), "1 Number" );
    const std::string test_nullptr = ptc::print( ptc::mode::str, "Hey", nullptr, nullptr );
    CHECK_EQ( test_nullptr, "Hey nullptr nullptr" );
    ptc::print.setEnd( "\n" );
   }

  // Testing usage of ANSI or empty character as first argument
  SUBCASE( "Testing ANSI escape sequence or empty character as first argument." )
   {
    ptc::print.setEnd( "" );
    const std::string test_b = ptc::print( ptc::mode::str, "\033[31m", "Testing empty char (ignore this)." );
    CHECK_EQ( test_b, "\033[31mTesting empty char (ignore this). \033[0m" ); 
    ptc::print.setEnd( "\n" );
   }
 }

//====================================================
//     Other char types
//====================================================
TEST_CASE( "Testing case of other char types." )
 {  
  // wchar_t
  SUBCASE( "Testing wchar_t" )
   {
    std::wstring wstr_in = ptc::wprint( ptc::mode::str, "Testing", "this" );
    std::wstring wstr_out = L"Testing this\n";
    CHECK_EQ( wstr_in, wstr_out );
  
    std::wstring wstr_in_2 = ptc::wprint( ptc::mode::str );
    std::wstring wstr_out_2 = L"";
    CHECK_EQ( wstr_in_2, wstr_out_2 );
   }

  #if ! defined( PTC_ENABLE_PERFORMANCE_IMPROVEMENTS ) && ! defined( __APPLE__ )

  // char16_t
  SUBCASE( "Testing char16_t" )
   {
    std::basic_string<char16_t> wstr_in = ptc::print16( ptc::mode::str, "Testing", "this" );
    std::basic_string<char16_t> wstr_out = u"";
    CHECK_EQ( wstr_in, wstr_out );
  
    std::basic_string<char16_t> wstr_in_2 = ptc::print16( ptc::mode::str );
    std::basic_string<char16_t> wstr_out_2 = u"";
    CHECK_EQ( wstr_in_2, wstr_out_2 );
   }

  // char32_t
  SUBCASE( "Testing char16_t" )
   {
    std::basic_string<char32_t> wstr_in = ptc::print32( ptc::mode::str, "Testing", "this" );
    std::basic_string<char32_t> wstr_out = U"";
    CHECK_EQ( wstr_in, wstr_out );
  
    std::basic_string<char32_t> wstr_in_2 = ptc::print32( ptc::mode::str );
    std::basic_string<char32_t> wstr_out_2 = U"";
    CHECK_EQ( wstr_in_2, wstr_out_2 );
   }

  // char8_t
  #if ( __cplusplus >= 202002L )
  SUBCASE( "Testing char8_t" )
   {
    std::basic_string<char8_t> wstr_in = ptc::print8( ptc::mode::str, "Testing", "this" );
    std::basic_string<char8_t> wstr_out = u8"";
    CHECK_EQ( wstr_in, wstr_out );
  
    std::basic_string<char8_t> wstr_in_2 = ptc::print8( ptc::mode::str );
    std::basic_string<char8_t> wstr_out_2 = u8"";
    CHECK_EQ( wstr_in_2, wstr_out_2 );
   }
  #endif

  #endif
 }

//====================================================
//     Print operator << overload
//====================================================
TEST_CASE( "Testing the Print operator << overloads." )
 {
  // Testing std::complex printing
  SUBCASE( "Testing std::complex printing." )
   {
    ptc::print.setEnd( "" );
    std::complex <int> no( 1, 6 );
    const std::string test_a = ptc::print( ptc::mode::str, no );
    CHECK_EQ( test_a, "1+6j" );
    std::complex <double> no_d( 1, 2.1 );
    const std::string test_b = ptc::print( ptc::mode::str, no_d );
    CHECK_EQ( test_b, "1+2.1j" );

    std::ostringstream ostr;
    ptc::print( ostr, no );
    CHECK_EQ( ostr.str(), "1+6j" );
    ptc::print.setEnd( "\n" );
   }

  // Testing all std containers printing
  SUBCASE( "Testing all std containers printing." )
   {
    ptc::print.setEnd( "" );

    // std::array
    std::array <int, 3> array = { 1, 2, 3 };
    CHECK_EQ( ptc::print( ptc::mode::str, array ), "[1, 2, 3]" );

    // std::vector
    std::vector <int> vec = { 1, 2, 3 };
    CHECK_EQ( ptc::print( ptc::mode::str, vec ), "[1, 2, 3]" );
    std::vector <int> null_v = {};
    CHECK_EQ( ptc::print( ptc::mode::str, null_v ), "[]" );

    std::wstring vec_in = ptc::wprint( ptc::mode::str, vec );
    std::wstring vec_out = L"[1, 2, 3]\n";
    CHECK_EQ( vec_in, vec_out );

    // std::deque
    std::deque <int> deque = { 7, 5, 16 };
    CHECK_EQ( ptc::print( ptc::mode::str, deque ), "[7, 5, 16]" );

    // std::forward_list
    std::forward_list <std::pair <int, int> > forwardListOfPairs;
    std::pair<int, int> pair1 = std::make_pair( 11, 22 );
    forwardListOfPairs.push_front( pair1 );
    std::pair<int, int> pair2 = std::make_pair( 33, 44 );
    forwardListOfPairs.push_front( pair2 );
    CHECK_EQ( ptc::print( ptc::mode::str, forwardListOfPairs ), "[[33, 44], [11, 22]]" );

    // std::list
    std::list<int> list = { 7, 5, 16 };
    CHECK_EQ( ptc::print( ptc::mode::str, list ), "[7, 5, 16]" );

    // std::set
    std::set<int> set = { 7, 5, 16 };
    CHECK_EQ( ptc::print( ptc::mode::str, set ), "[5, 7, 16]" );

    // std::map
    std::map <int,int> map = { { 1, 1 }, { 2, 2 }, { 3, 3 } };
    CHECK_EQ( ptc::print( ptc::mode::str, map ), "[[1, 1], [2, 2], [3, 3]]" );

    // std::multiset
    std::multiset <int, std::greater<int>> multiset;
    multiset.insert( 40 );
    multiset.insert( 23 );
    multiset.insert( 1 );
    CHECK_EQ( ptc::print( ptc::mode::str, multiset ), "[40, 23, 1]" );

    // std::multimap
    std::multimap <int, int> multimap;
    multimap.insert( std::pair <int, int> ( 1, 40 ) );
    multimap.insert( std::pair <int, int> ( 2, 30 ) );
    CHECK_EQ( ptc::print( ptc::mode::str, multimap ), "[[1, 40], [2, 30]]" );

    // std::unordered_set
    std::unordered_set<int> u_set = { 7, 5, 16 };
    CHECK_EQ( ptc::print( ptc::mode::str, u_set ), "[16, 5, 7]" );

    // std::unordered_map
    std::unordered_map <int,int> u_map = { { 1, 1 }, { 2, 2 }, { 3, 3 } };
    CHECK_EQ( ptc::print( ptc::mode::str, u_map ), "[[3, 3], [2, 2], [1, 1]]" );

    // std::unordered_multiset
    std::unordered_multiset <int> u_multiset = { 40, 23, 1 };
    CHECK_EQ( ptc::print( ptc::mode::str, u_multiset ), "[23, 1, 40]" );

    // std::unordered_multimap
    std::unordered_multimap <int, int> u_multimap;
    u_multimap.insert( std::pair <int, int> ( 1, 40 ) );
    u_multimap.insert( std::pair <int, int> ( 2, 30 ) );
    CHECK_EQ( ptc::print( ptc::mode::str, u_multimap ), "[[2, 30], [1, 40]]" );

    // std::stack
    std::stack <int> stack;
    stack.push( 21 );
    stack.push( 22 );
    stack.push( 24 );
    CHECK_EQ( ptc::print( ptc::mode::str, stack ), "[21, 22, 24]" );
    CHECK_EQ( ptc::print( ptc::mode::str, stack ), "[21, 22, 24]" );

    std::stack <int> empty_stack;
    CHECK_EQ( ptc::print( ptc::mode::str, empty_stack ), "[]" );

    // std::priority_queue
    std::priority_queue<int> p_queue;
    p_queue.push( 2 );
    p_queue.push( 5 );
    p_queue.push( 6 );
    CHECK_EQ( ptc::print( ptc::mode::str, p_queue ), "[6, 2, 5]" );

    // std::chrono::duration
    CHECK_EQ( ptc::print( ptc::mode::str, 5ns ), "5ns" );
    CHECK_EQ( ptc::print( ptc::mode::str, 5us ), "5us" );
    CHECK_EQ( ptc::print( ptc::mode::str, 5ms ), "5ms" );
    CHECK_EQ( ptc::print( ptc::mode::str, 5s ), "5s" );
    CHECK_EQ( ptc::print( ptc::mode::str, 5min ), "5min" );
    CHECK_EQ( ptc::print( ptc::mode::str, 5h ), "5h" );

    #if ( __cplusplus >= 202002L )
    CHECK_EQ( ptc::print( ptc::mode::str, std::chrono::days( 2 ) ), "2d" );
    CHECK_EQ( ptc::print( ptc::mode::str, std::chrono::weeks( 5 ) ), "5w" );
    CHECK_EQ( ptc::print( ptc::mode::str, std::chrono::months( 1 ) ), "1mos" );
    CHECK_EQ( ptc::print( ptc::mode::str, std::chrono::years( 23 ) ), "23y" );
    #endif

    ptc::print.setEnd( "\n" );
   }

  // Testing C arrays printing
  SUBCASE( "Testing C arrays printing." )
   {
    int arr[3] = { 1, 2, 3 };
    CHECK_EQ( ptc::print( ptc::mode::str, arr ), "[1, 2, 3]\n" );
   }

  // Testing nested std containers printing
  SUBCASE( "Testing nested std containers printing." )
   {
    std::vector <std::vector <int>> vec = { { 1, 3 }, { 2, 1 } };
    CHECK_EQ( ptc::print( ptc::mode::str, vec ), "[[1, 3], [2, 1]]\n" );
   }

  // Testing std::optional printing
  SUBCASE( "Testing std::optional printing." )
   {
    std::optional<int> opt = 43;
    CHECK_EQ( ptc::print( ptc::mode::str, opt ), "43\n" );

    std::optional<int> opt_n;
    CHECK_EQ( ptc::print( ptc::mode::str, opt_n ), "nullopt\n" );
   }
 }

//====================================================
//     Print setEnd and getEnd
//====================================================
TEST_CASE( "Testing the Print setEnd and getEnd methods." )
 {
  ptc::print.setEnd( '.' );
  CHECK_EQ( ptc::print.getEnd(), "." );
  
  std::streambuf* cerrbuf = std::cerr.rdbuf();
  ptc::savebuf sbuf( cerrbuf );
  std::cerr.rdbuf( &sbuf );
  ptc::print( std::cerr, "Test passes (ignore this)." );
  std::cerr.rdbuf( cerrbuf );
  CHECK_EQ( sbuf.str(), "Test passes (ignore this).." );
  CHECK( sbuf.str() != "Test thisssa.\n" );

  ptc::print.setEnd( "\n" );
  ptc::print( "\n" );
 }

//====================================================
//     Print setSep and getSep
//====================================================
TEST_CASE( "Testing the Print setSep and getSep methods." )
 {
  ptc::print.setSep( "*" );
  CHECK_EQ( ptc::print.getSep(), "*" );

  std::streambuf* coutbuf = std::cout.rdbuf();
  ptc::savebuf sbuf( coutbuf );
  std::cout.rdbuf( &sbuf );
  ptc::print( "Test", "passes", "(ignore this)." );
  std::cout.rdbuf( coutbuf );
  CHECK_EQ( sbuf.str(), "Test*passes*(ignore this).\n" );
  CHECK( sbuf.str() != "Test thisssa.\n" );

  ptc::print.setSep( " " );
 }

//====================================================
//     Print setFlush and getFlush
//====================================================
TEST_CASE( "Testing the Print setFlush and getFlush methods." )
 {
  ptc::print.setFlush( true );
  CHECK_EQ( ptc::print.getFlush(), true );

  std::streambuf* coutbuf = std::cout.rdbuf();
  ptc::savebuf sbuf( coutbuf );
  std::cout.rdbuf( &sbuf );
  ptc::print( "Test", "passes", "(ignore this)." );
  std::cout.rdbuf( coutbuf );
  CHECK_EQ( sbuf.str(), "Test passes (ignore this).\n" );
  CHECK( sbuf.str() != "Test thisssa.\n" );

  ptc::print.setFlush( false );
 }

//====================================================
//     Print setPattern and getPattern
//====================================================
TEST_CASE( "Testing the Print setPattern and getPattern methods." )
 {
  ptc::print.setEnd( "" );

  ptc::print.setPattern( "|" );
  CHECK_EQ( ptc::print( ptc::mode::str, "Testing", "this", "pattern" ), "|Testing| |this| |pattern|" );
  CHECK_EQ( ptc::print( ptc::mode::str, "\033[31m", "this", "pattern" ), "\033[31m|this| |pattern| \033[0m" );
  CHECK_EQ( ptc::print( ptc::mode::str, "Testing", 1.2, "pattern" ), "|Testing| |1.2| |pattern|" );
  CHECK_EQ( ptc::print( ptc::mode::str, 1, "this", "pattern" ), "|1| |this| |pattern|" );
  ptc::print.setPattern( "" );

  ptc::print.setPattern( '|' );
  CHECK_EQ( ptc::print( ptc::mode::str, "Testing", "this", "pattern" ), "|Testing| |this| |pattern|" );
  ptc::print.setPattern( "" );
  CHECK_EQ( ptc::print( ptc::mode::str, "Testing", "this", "pattern" ), "Testing this pattern" );

  ptc::print.setEnd( "\n" );
 }