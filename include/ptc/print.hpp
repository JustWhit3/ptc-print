//====================================================
//     File data
//====================================================
/**
 * @file print.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-07-14
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef PRINT_HPP
#define PRINT_HPP

//====================================================
//     Headers
//====================================================

// Standard headers
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <mutex>
#include <utility>
#include <locale>
#include <codecvt>

// Extra types headers
#ifndef PTC_DISABLE_STD_TYPES_PRINTING
#include <complex>
#include <stack>
#include <queue>
#include <chrono>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <optional>
#endif

//====================================================
//     Namespaces
//====================================================
using namespace std::literals::string_literals;

namespace ptc
 {
  //====================================================
  //     Enum classes
  //====================================================

  // mode
  /**
   * @brief Enum class used to set up the "str" mode to pass a string with the content of the print function.
   * 
   */
   enum class mode { str };

  // ANSI_pos
  /**
   * @brief Enum class used to switch among ANSI escape configurations in the "is_escape" function.
   * 
   */
   enum class ANSI { first, generic };

  //====================================================
  //     Helper tools
  //====================================================

  // StringConverter
  /**
   * @brief Function used to convert an std::string into other string types (std::wstring etc...). If the argument is an std::string it will be returned without any modification.
   * 
   * @tparam CharT The char type (char, wchar_t...) to which the string is converted..
   * @param input_str The input std::string object.
   * @return std::conditional_t<std::is_same_v<CharT, char>, const std::basic_string<CharT>&, std::basic_string<CharT>> The converted string object.
   */
  template <class CharT>
  std::conditional_t<std::is_same_v<CharT, char>, const std::basic_string<CharT>&, std::basic_string<CharT>>
  StringConverter( const std::string& input_str )
   {
    if constexpr( std::is_same_v <CharT, char> ) 
     {
      return input_str;
     }
    else if constexpr( std::is_same_v <CharT, wchar_t> )
     {
      static std::wstring_convert <std::codecvt_utf8_utf16 <wchar_t>> converter_wchar_t;
      return converter_wchar_t.from_bytes( input_str );
     }
    #ifndef __APPLE__
    #if ( __cplusplus >= 202002L )
    else if constexpr( std::is_same_v <CharT, char8_t> )
     {
      return reinterpret_cast <const char8_t*>( input_str.c_str() );
     }
    #endif
    else if constexpr( std::is_same_v <CharT, char16_t> )
     {
      static std::wstring_convert <std::codecvt_utf8_utf16 <char16_t>, char16_t> converter_16_t;
      return converter_16_t.from_bytes( input_str );
     } 
    else if constexpr( std::is_same_v <CharT, char32_t> )
     {
      static std::wstring_convert <std::codecvt_utf8_utf16 <char32_t>, char32_t> converter_32_t;
      return converter_32_t.from_bytes( input_str );
     }
    #endif
    else 
     {
      return StringConverter<CharT>( "" );
     }
   }

  #ifndef PTC_DISABLE_STD_TYPES_PRINTING

  // is_streamable
  /**
   * @brief Struct used to define a specific type trait for operator << overload for container printing.
   * 
   * @tparam T Template type of the type trait.
   */
  template <class T, class T_str>
  struct is_streamable 
   {
    static std::false_type test( ... );
      
    template<class U>
    static auto test( const U& u ) -> decltype( std::declval <std::basic_ostream<T_str>&>() << u, std::true_type{} );
  
    static constexpr bool value = decltype( test( std::declval <T>() ) )::value;
   };
  
  template<class T, class T_str>
  inline constexpr bool is_streamable_v = is_streamable<T, T_str>::value;

  // Helper function for container adaptors printing
  /**
   * @brief Helper function for container adaptors printing.
   * 
   * @tparam Container The modified type of the container to be printed.
   * @tparam T_str The char type of the stream.
   * @param os The stream to which the container is printed to.
   * @param container The container to be printed.
   */
  template <class Container, class T_str>
  inline void print_adaptor( std::basic_ostream<T_str>& os, const Container& container )
   {
    typename Container::const_iterator beg = container.begin();
    std::basic_string<T_str> separator = StringConverter<T_str>( ""s );
    
    while( beg != container.end() )
     {
      os << separator << *beg++;
      separator = StringConverter<T_str>( ", "s );
     }
   }
  
  // container_mod overload for std::stack hacked printing
  /**
   * @brief Overload used to create a modified stack object in order to be successfully printed.
   * 
   * @tparam Type The type of the stack elements..
   * @tparam Container The type of the container.
   * @param stack The stack to be modified.
   * @return const Container& The modified stack.
   */
  template <class Type, class Container>
  const Container& container_mod( const std::stack<Type, Container>& stack )
   {
    struct HackedStack : private std::stack<Type, Container>
     {
      static const Container& container( const std::stack<Type, Container>& stack )
       {
        return stack.*&HackedStack::c;
       }
     };
  
    return HackedStack::container( stack );
   }

  // container_mod overload for std::priority_queue hacked printing
  /**
   * @brief Overload used to create a modified priority_queue object in order to be successfully printed.
   * 
   * @tparam Type The type of the priority_queue elements..
   * @tparam Container The type of the container.
   * @param priority_queue The priority_queue to be modified.
   * @return const Container& The modified priority_queue.
   */
  template < class Type, class Container >
  const Container& container_mod( const std::priority_queue<Type, Container>& priority_queue )
   {
    struct HackedQueue : private std::priority_queue<Type, Container>
     {
      static const Container& container( const std::priority_queue<Type, Container>& priority_queue )
       {
        return priority_queue.*&HackedQueue::c;
       }
     };

    return HackedQueue::container( priority_queue );
   }

  //====================================================
  //     Operator << overloads for stdlib types
  //====================================================

  #if defined( __GNUC__ ) && ( __GNUC___ <= 9 )

  // Overload for std::nullptr_t
  /**
   * @brief Operator << overload for std::nullptr_t printing.
   * 
   * @tparam T_str The char type of the ostream object.
   * @param os The type of the output stream.
   * @return std::basic_ostream<T_str>& The stream to which the object is printed to.
   */
  template <class T_str>
  inline std::basic_ostream<T_str>& operator << ( std::basic_ostream<T_str>& os, std::nullptr_t )
   {
    os << "nullptr";
    return os; 
   }

  #endif

  // Overload for std::complex
  /**
   * @brief Operator << overload for std::complex printing.
   * 
   * @tparam T_str The char type of the ostream object.
   * @tparam T_cmplx The type of the real and imaginary part complex number to be printed.
   * @param os The type of the output stream.
   * @param number The number to be printed.
   * @return std::basic_ostream<T_str>& The stream to which the number is printed to.
   */
  template <class T_str, class T_cmplx>
  inline std::basic_ostream<T_str>& operator << ( std::basic_ostream<T_str>& os, const std::complex<T_cmplx>& number )
   {
    os << number.real() << '+' << number.imag() << 'j';

    return os; 
   }

  // Helper overload for std::vector and std::map
  /**
   * @brief Helper overload to print test containers (std::vector and std::map).
   * 
   * @tparam T_str The char type of the ostream object.
   * @tparam T First template type of the std::pair variable.
   * @tparam U Second template type of the std::pair variable.
   * @param os The stream to which the overload prints.
   * @param p The std::pair object.
   * @return std::basic_ostream<T_str>& The stream to which the container is printed to.
   */
  template <class T_str, class T, class U>
  inline std::basic_ostream<T_str>& operator <<( std::basic_ostream<T_str>& os, const std::pair <T, U>& p ) 
   {
    os << '[' << p.first << ", " << p.second << ']';

    return os;
   } 

  // Overload for all containers printing
  /**
   * @brief Overload for all containers printing. Containers which already has an operator << overload will be ignored.
   * 
   * @tparam T_str The char type of the ostream object.
   * @tparam ContainerType The container type (ex std::vector, std::map etc...)
   * @tparam ValueType The value type of the container.
   * @tparam Args The arguments of the container.
   * @param os The stream to which the output is printed.
   * @param container The container to be printed.
   * @return std::basic_ostream<T_str>& The stream to which the container is printed to.
   */
  template <template <typename, typename...> class ContainerType, typename ValueType, typename... Args, class T_str>
  std::enable_if_t< ! is_streamable_v <ContainerType <ValueType, Args...>, T_str>, std::basic_ostream<T_str>&>
  operator <<( std::basic_ostream<T_str>& os, const ContainerType<ValueType, Args...>& container ) 
   {
    static bool constexpr is_stack = std::is_same_v <ContainerType<ValueType, Args...>, std::stack<ValueType>>;
    static bool constexpr is_pqueue = std::is_same_v <ContainerType<ValueType, Args...>, std::priority_queue<ValueType>>;
    
    os << '[';
    if constexpr ( ! is_stack && ! is_pqueue )
     {
      std::basic_string<T_str> separator = StringConverter<T_str>( ""s );
      for ( const auto& elem: container )
       {
        os << separator;
        os << elem;
        separator = StringConverter<T_str>( ", "s );
       }
     }
    else
     {
      print_adaptor( os, container_mod( container ) );
     }
    os << ']';

    return os;
   }

  // Overload for std::array printing
  /**
   * @brief Overload for std::array printing.
   * 
   * @tparam T_str The char type of the ostream object.
   * @tparam T The type of the array.
   * @tparam T_no The number of elements of the array.
   * @param os The stream to which the output is printed.
   * @param container The array to be printed.
   * @return std::basic_ostream<T_str>& The stream to which the array is printed to.
   */
  template <class T_str, class T, size_t T_no>
  std::basic_ostream<T_str>& operator <<( std::basic_ostream<T_str>& os, const std::array<T, T_no>& container ) 
   {
    std::basic_string<T_str> separator = StringConverter<T_str>( ""s );

    os << '[';
    for ( const auto& elem: container )
     {
      os << separator;
      os << elem;
      separator = StringConverter<T_str>( ", "s );
     }
    os << ']';

    return os;
   }

  // Overload for C arrays
  /**
   * @brief Overload for C arrays printing.
   * 
   * @tparam T_str The char type of the ostream object.
   * @tparam T1 The type of the array.
   * @tparam arrSize The size of the array.
   * @tparam std::enable_if_t< ! std::is_same <T1,char>::value> Enable if it is not const char*.
   * @param os The stream to which the array is printed to.
   * @return std::basic_ostream<T_str>& The stream to which the array is printed to.
   */
  template <class T_str, class T1, size_t arrSize, 
  typename = std::enable_if_t< ! std::is_same <T1,char>::value>>
  std::basic_ostream<T_str>& operator <<( std::basic_ostream<T_str>& os, const T1( & arr )[ arrSize ] )
   {
    os << '[';
    if ( arrSize )
     {
      std::basic_string<T_str> separator = StringConverter<T_str>( ""s );
      for ( const auto& elem: arr )
       {
        os << separator;
        os << elem;
        separator = StringConverter<T_str>( ", "s );
       }
     }
    os << ']';

    return os;
   }

  // Overload for std::chrono::duration objects
  /**
   * @brief Operator << overload for std::chrono::duration objects printing.
   * 
   * @tparam T_str The char type of the ostream object.
   * @tparam T_time The order of magnitude of the time object.
   * @tparam int_type The int type of the time object.
   * @param os The stream to which the time object is printed to.
   * @param val The time object.
   * @return std::basic_ostream<T_str>& The stream to which the time object is printed to.
   */
  template <class T_str, class T_time, class int_type>
  std::basic_ostream<T_str>& operator <<( std::basic_ostream<T_str>& os, const std::chrono::duration<int_type, T_time>& val )
   {
    if constexpr( ! std::is_same_v<std::chrono::duration<int_type, T_time>, std::chrono::duration<int_type>> )
     {
      static std::unordered_map<std::type_index, const std::basic_string<T_str>> time_map
       {
        { typeid( std::nano ), StringConverter<T_str>( "ns" ) },
        { typeid( std::micro ), StringConverter<T_str>( "us" ) },
        { typeid( std::milli ), StringConverter<T_str>( "ms" ) },
        { typeid( std::ratio<60> ), StringConverter<T_str>( "min" ) },
        { typeid( std::ratio<3600> ), StringConverter<T_str>( "h" ) }
       };

      #if ( __cplusplus >= 202002L )
      time_map.insert( { typeid( std::ratio<86400> ), StringConverter<T_str>( "d" ) } );
      time_map.insert( { typeid( std::ratio<604800> ), StringConverter<T_str>( "w" ) } );
      time_map.insert( { typeid( std::ratio<2629746> ), StringConverter<T_str>( "mos" ) } );
      time_map.insert( { typeid( std::ratio<31556952> ), StringConverter<T_str>( "y" ) } );
      #endif
       
      os << val.count() << time_map[ typeid( T_time ) ];
     }
    else if constexpr( std::is_same_v<std::chrono::duration<int_type, T_time>, std::chrono::duration<int_type>> )
     {
      os << val.count() << 's';
     }

    return os;
   }

  // Overload for std::optional
  template <class T_str, class T>
  std::basic_ostream<T_str>& operator <<( std::basic_ostream<T_str>& os, std::optional<T> const& opt )
   {
    if ( opt ) os << opt.value();
    else os << "nullopt"; 
    
    return os;
   }

  #endif

  //====================================================
  //     ptc_print class
  //====================================================
  /**
   * @brief Class used to construct the print function.
   * 
   * @tparam T_str The type of the string objects defined inside the struct. This template is used in case you are dealing with std::string or std::wstring objects.
   */
  template <class T_str>
  struct Print
   {
    //====================================================
    //     Public constructors and destructor
    //====================================================

    // Default constructor
    /**
     * @brief Default constructor of the Print class. It initializes the basic class members and enable (if required) performance improvements..
     * 
     */
    Print(): 
     end( StringConverter<T_str>( "\n"s ) ),
     sep( StringConverter<T_str>( " "s ) ),
     flush( false )
     {       
      #ifdef PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
      performance_options();
      #endif
     }

    //====================================================
    //     Public structs
    //====================================================

    // select_cout
    /**
     * @brief Struct used to define a way to template the choice of the "std::cout" object in order to be "std::cout" for "char" type or "std::wcout" for "wchar_t" type.
     * 
     * @tparam T The template type of the "std::cout" object (char, wchar_t, ...).
     */  
    template <class T> 
    struct select_cout
     {
      static std::basic_ostream<T> &cout;
     };

    #ifdef PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
   
    // select_cin
    /**
     * @brief Struct used to define a way to template the choice of the "std::cin" object in order to be "std::cin" for "char" type or "std::wcin" for "wchar_t" type.
     * 
     * @tparam T The template type of the "std::cin" object (char, wchar_t, ...).
     */  
    template <class T> 
    struct select_cin
     {
      static std::basic_istream<T> &cin;
     };
  
    #endif

    //====================================================
    //     Public setters
    //====================================================

    // setEnd
    /**
     * @brief Setter used to set the value of the "end" variable. Templated type is required in order to allow also char variables.
     * 
     * @tparam T The type of the expression inserted to set the value of "end" variable.
     * @param end_val The inserted expression used to set the value of "end" variable.
     */
    template <class T> 
    inline void setEnd( const T& end_val )
     {
      end = end_val;
     }

    // setSep
    /**
     * @brief Setter used to set the value of the "sep" variable. Templated type is required in order to allow also char variables.
     * 
     * @tparam T The type of the expression inserted to set the value of "sep" variable.
     * @param end_val The inserted expression used to set the value of "sep" variable.
     */
    template <class T>
    inline void setSep( const T& sep_val )
     {
      sep = sep_val;
     }

    // setFlush
    /**
     * @brief Setter used to set the value of the "flush" variable. Templated type is required in order to allow also char variables.
     * 
     * @param flush_val The inserted expression used to set the value of the "flush" variable.
     */
    inline void setFlush( const bool& flush_val )
     {
      flush = flush_val;
     }
    
    // setPattern
    /**
     * @brief Setter used to set the value of the "pattern" variable. Templated type is required in order to allow also char variables.
     * 
     * @tparam T The type of the expression inserted to set the value of "pattern" variable.
     * @param pattern_val The inserted expression used to set the value of "pattern" variable.
     */
    template <class T>
    inline void setPattern( const T& pattern_val )
     {
      pattern = pattern_val;
     }

    //====================================================
    //     Public getters
    //====================================================

    #ifdef PTC_ENABLE_GETTERS_FOR_UNIT_TESTS

    // getEnd
    /**
     * @brief Getter used to get the value of the "end" variable. Mainly used for debugging.
     * 
     * @return auto The value of the "end" variable.
     */
    inline const auto& getEnd() const 
     {
      return end;
     }

    // getSep
    /**
     * @brief Getter used to get the value of the "sep" variable. Mainly used for debugging.
     * 
     * @return auto The value of the "sep" variable.
     */
    inline const auto& getSep() const
     {
      return sep;
     }

    // getFlush
    /**
     * @brief Getter used to get the value of the "flush" variable. Mainly used for debugging.
     * 
     * @return bool The value of the "flush" variable.
     */
    inline const bool& getFlush() const
     {
      return flush;
     }

    // getPattern
    /**
     * @brief Getter used to get the value of the "pattern" variable. Mainly used for debugging.
     * 
     * @return auto The value of the "pattern" variable.
     */
    inline const auto& getPattern() const
     {
      return pattern;
     }

    #endif

    //====================================================
    //     Public operator () overloads
    //====================================================

    // General case
    /**
     * @brief Frontend implementation of the () operator overload to print to the output stream. The backend implementation is called in the required variation.
     * 
     * @tparam T Generic type of first object to be passed as argument to the backend implementation.
     * @tparam Args Generic type of all the other objects to be passed to the backend implementation.
     * @param first First object to be passed to the backend implementation.
     * @param args The list of all the other objects to be passed to the backend implementation.
     */
    template <class T, class... Args>
    void operator()( T&& first, Args&&... args ) const
     {
      if constexpr ( std::is_base_of_v <std::basic_ostream<T_str>, std::remove_reference_t<T>> )
       {
        print_backend( std::forward<T>( first ), std::forward<Args>( args )... );
       }
      else
       {
        print_backend( select_cout<T_str>::cout, std::forward<T>( first ), std::forward<Args>( args )... );
       }
     }

    // String initialization case
    /**
     * @brief Frontend implementation of the () operator overload to initialize its content with an std::string object. The backend implementation is called in the required variation. This overload is required in order to hide the output of the "print_backend" function during the initialization.
     * 
     * @tparam Args Generic type of all the other objects to be passed to the backend implementation.
     * @param first First object to be passed to the backend implementation.
     * @param args The list of all the other objects to be passed to the backend implementation.
     * @return const std::basic_string<T_str> The whole print content in string format.
     */
    template <class... Args>
    const std::basic_string<T_str> operator()( mode&& first, Args&&... args ) const
     { 
      if constexpr( sizeof...( args ) > 0 )
       {
        switch( first )
         {
          case mode::str:
           {
            static std::basic_ostringstream<T_str> oss;
            oss.str( StringConverter<T_str>( ""s ) );
            oss.clear();
            print_backend( oss, std::forward<Args>( args )... );

            return oss.str();
           }
         }
       }
       
      return StringConverter<T_str>( "" );
     }

    // No arguments case
    /**
     * @brief Template operator redefinition used to print an empty line on the screen. This is the no argument case overload. Can be used with "ptc::print()" or "ptc::print( ostream_name )".
     * 
     * @param os The stream in which you want to print the output.
     */
    inline void operator () ( std::basic_ostream<T_str>& os = select_cout<T_str>::cout ) const
     {
      os << end;
      if ( flush ) os << std::flush;
     }
     
   private:

    //====================================================
    //     Private methods
    //====================================================

    // is_escape
    /**
     * @brief This method is used to check if an input variable is an ANSI escape sequency or not.
     * 
     * @tparam T Template type of the input variable.
     * @param str The input variable.
     * @param flag A flag which let to return different things with respect to its value. If flag = ANSI::first the ANSI is searched as the first substring of the str argument, otherwise, if flag = ANSI::generic the ANSI is searched as a substring inside the str argument.
     * @return true If the input variable is an ANSI escape sequency.
     * @return false Otherwise.
     */
    template <typename T>
    static constexpr bool is_escape( const T& str, const ANSI& flag )
     {
      if constexpr( std::is_convertible_v <T, std::basic_string_view<T_str>> && ! std::is_same_v<T, std::nullptr_t> )
       {
        switch( flag )
         {
          case( ANSI::first ): 
           {
            return ( std::basic_string_view<T_str>( str ).length() < 7 ) && ( str[0] == '\033' );
           }
          case( ANSI::generic ):
           {
            return ( std::basic_string_view<T_str>( str ).find( '\033' ) != std::basic_string_view<T_str>::npos );
           }
         }
       }
      return false;
     }
      
    // print_backend
    /**
     * @brief Backend implementation of the () operator overloads to print to the output stream. The stream is automatically reset in case of an ANSI escape sequence is sent to output.
     * 
     * @tparam T_os The type of the output stream object.
     * @tparam T Generic type of first object to be printed.
     * @tparam Args Generic type of all the other objects to be printed.
     * @param os The stream in which you want to print the output.
     * @param first First printed object.
     * @param args The list of objects to be printed on the screen.
     */
    template <class T_os, class T, class... Args>
    void print_backend( T_os&& os, T&& first, Args&&... args ) const
     {
      std::lock_guard <std::mutex> lock{ mutex_ };

      // Printing the first argument
      if( is_escape( first, ANSI::first ) || pattern.empty() ) os << first;
      else os << pattern << first << pattern;
      
      // Printing all the other arguments
      if constexpr( sizeof...( args ) > 0 ) 
       {
        if ( is_escape( first, ANSI::first ) ) 
         {
          if( pattern.empty() ) ( ( os << args << sep ), ...);
          else ( ( os << pattern << args << pattern << sep ), ...);
         }
        else 
         {
          if( pattern.empty() ) ( ( os << sep << args ), ...);
          else ( ( os << sep << pattern << args << pattern ), ...);
         }
       }
      os << end;
      
      // Resetting the stream from ANSI escape sequences
      if constexpr( sizeof...( args ) > 0 )
       {
        if ( is_escape( first, ANSI::generic ) || ( ( is_escape( args, ANSI::generic ) ) || ...) )
         {
          os << "\033[0m";
         }
       }
      else 
       {
       if ( is_escape( first, ANSI::generic ) ) 
        {
         os << "\033[0m";
        }
       }

      // Other operations
      if ( flush ) os << std::flush;
     }

    // performance_options
    /**
     * @brief Function used to set on the performance improvements to the operator () overload.
     *
     */
    inline void performance_options() const
     {
      std::lock_guard <std::mutex> lock{ mutex_ };
      
      std::ios_base::sync_with_stdio( false );
      select_cout<T_str>::cout.tie( NULL );

      #ifdef PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
      select_cin<T_str>::cin.tie( NULL );
      #endif
     }
     
    //====================================================
    //     Private attributes
    //====================================================
    std::basic_string<T_str> end, sep, pattern;
    static std::mutex mutex_;
    bool flush;
   };
   
  //====================================================
  //     Other steps
  //====================================================

  // Print structs specializations
  template <> template <> std::ostream &Print<char>::select_cout <char>::cout = std::cout;
  template <> template <> std::wostream &Print<wchar_t>::select_cout <wchar_t>::cout = std::wcout;

  #ifdef PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
  template <> template <> std::istream &Print<char>::select_cin <char>::cin = std::cin;
  template <> template <> std::wistream &Print<wchar_t>::select_cin <wchar_t>::cin = std::wcin;
  #endif

  // Print::mutex_ definiton
  template <class T_str> inline std::mutex Print <T_str>::mutex_;

  // Print objects initialization
  inline Print <char> print;        // char
  inline Print <wchar_t> wprint;    // wchar_t

  #if ! defined( PTC_ENABLE_PERFORMANCE_IMPROVEMENTS ) && ! defined( __APPLE__ )
  #if ( __cplusplus >= 202002L )
  inline Print <char8_t> print8;  // char8_t
  #endif
  inline Print <char16_t> print16;  // char16_t
  inline Print <char32_t> print32;  // char32_t
  #endif
 }

#endif