//====================================================
//     Metadata
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
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <mutex>
#include <utility>
#include <complex>
#include <stack>
#include <queue>
#include <chrono>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>


namespace ptc
 {
  //====================================================
  //     Type aliases
  //====================================================
  namespace stype
   {
    template <class T> using string = std::basic_string<T>;
    template <class T> using string_view = std::basic_string_view<T>;
    template <class T> using ostringstream = std::basic_ostringstream<T>;
    template <class T> using ostream = std::basic_ostream<T>;
   }

  //====================================================
  //     Global constants
  //====================================================
  namespace sconstant
   {
    inline std::unordered_map<std::type_index, std::string> time_map
     {
      { typeid( std::nano ), "ns" },
      { typeid( std::micro ), "us" },
      { typeid( std::milli ), "ms" },
      { typeid( std::ratio<60> ), "min" },
      { typeid( std::ratio<3600> ), "h" }
     };
   }

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
    static auto test( const U& u ) -> decltype( std::declval <stype::ostream<T_str>&>() << u, std::true_type{} );
  
    static constexpr bool value = decltype( test( std::declval <T>() ) )::value;
   };
  
  template<class T, class T_str>
  inline constexpr bool is_streamable_v = is_streamable<T, T_str>::value;

  // TOSTRING
  /**
   * @brief Function used to convert a std::string into a std::wstring or vice-versa.
   * 
   * @tparam CharT The char type (char, wchar_t...).
   * @param str The char object.
   * @param wstr The wchar_t object.
   * @return const CharT* The char or wchar_t object.
   */
  template <class CharT>
  const CharT* ToString( const char* str, const wchar_t* wstr );
  
  template<>
  const char* ToString <char>( const char* str, const wchar_t* wstr )
   {
    ( void ) *wstr;
    return str;
   }
  
  template<>
  const wchar_t* ToString <wchar_t>( const char* str, const wchar_t* wstr )
   {
    ( void ) *str;
    return wstr;
   }
  
  #define TOSTRING( T, str ) ToString <T>( str, L##str )

  // select_cout
  /**
   * @brief Struct used to define a way to template the choice of the "std::cout" object in order to be "std::cout" for "char" type or "std::wcout" for "wchar_t" type.
   * 
   * @tparam T The template type of the "std::cout" object (char, wchar_t, ...).
   */
  template <class T> 
  struct select_cout;
  
  template<> struct select_cout <char> 
   {
    static std::ostream &cout;
   };

  std::ostream &select_cout <char>::cout = std::cout;
  
  template<> 
  struct select_cout <wchar_t>
   {
    static std::wostream &cout;
   };

  std::wostream &select_cout <wchar_t>::cout = std::wcout;
 
  // select_cin
  /**
   * @brief Struct used to define a way to template the choice of the "std::cin" object in order to be "std::cin" for "char" type or "std::wcin" for "wchar_t" type.
   * 
   * @tparam T The template type of the "std::cin" object (char, wchar_t, ...).
   */
  template <class T>
  struct select_cin;
  
  template<> 
  struct select_cin <char>
   {
    static std::istream &cin;
   };

  std::istream &select_cin <char>::cin = std::cin;
  
  template<>
  struct select_cin <wchar_t>
   {
    static std::wistream &cin;
   };

  std::wistream &select_cin <wchar_t>::cin = std::wcin;

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
  void print_adaptor( stype::ostream<T_str>& os, const Container& container )
   {
    typename Container::const_iterator beg = container.begin();
    const T_str* separator = TOSTRING( T_str, "" );
    
    while( beg != container.end() )
     {
      os << separator << *beg++;
      separator = TOSTRING( T_str, ", " );
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
  //     Operator << overloads
  //====================================================

  // Overload for std::complex
  /**
   * @brief Operator << overload for std::complex printing.
   * 
   * @tparam T_str The char type of the ostream object.
   * @tparam T_cmplx The type of the real and imaginary part complex number to be printed.
   * @param os The type of the output stream.
   * @param number The number to be printed.
   * @return stype::ostream<T_str>& The stream to which the number is printed to.
   */
  template <class T_str, class T_cmplx>
  inline stype::ostream<T_str>& operator << ( stype::ostream<T_str>& os, const std::complex<T_cmplx>& number )
   {
    os << number.real() << "+" << number.imag() << "j";
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
   * @return stype::ostream<T_str>& The stream to which the container is printed to.
   */
  template <class T_str, class T, class U>
  inline stype::ostream<T_str>& operator <<( stype::ostream<T_str>& os, const std::pair <T, U>& p ) 
   {
    os << "[" << p.first << ", " << p.second << "]";
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
   * @return stype::ostream<T_str>& The stream to which the container is printed to.
   */
  template <template <typename, typename...> class ContainerType, typename ValueType, typename... Args, class T_str>
  std::enable_if_t< ! is_streamable_v <ContainerType <ValueType, Args...>, T_str>, stype::ostream<T_str>&>
  operator <<( stype::ostream<T_str>& os, const ContainerType<ValueType, Args...>& container ) 
   {
    bool constexpr is_stack = std::is_same_v <ContainerType<ValueType, Args...>, std::stack<ValueType>>;
    bool constexpr is_pqueue = std::is_same_v <ContainerType<ValueType, Args...>, std::priority_queue<ValueType>>;
    
    os << "[";
    if constexpr ( ! is_stack && ! is_pqueue )
     {
      const T_str* separator = TOSTRING( T_str, "" );
      for ( const auto& elem: container )
       {
        os << separator;
        os << elem;
        separator = TOSTRING( T_str, ", " );
       }
     }
    else
     {
      print_adaptor( os, container_mod( container ) );
     }
    os << "]";

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
   * @return stype::ostream<T_str>& The stream to which the array is printed to.
   */
  template <class T_str, class T, size_t T_no>
  stype::ostream<T_str>& operator <<( stype::ostream<T_str>& os, const std::array<T, T_no>& container ) 
   {
    os << "[";
    const T_str* separator = TOSTRING( T_str, "" );
    for ( const auto& elem: container )
     {
      os << separator;
      os << elem;
      separator = TOSTRING( T_str, ", " );
     }
    os << "]";
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
   * @return stype::ostream<T_str>& The stream to which the array is printed to.
   */
  template <class T_str, class T1, size_t arrSize, 
  typename = std::enable_if_t< ! std::is_same <T1,char>::value>>
  stype::ostream<T_str>& operator <<( stype::ostream<T_str>& os, const T1( & arr )[ arrSize ] )
   {
    os << "[";
    if ( arrSize )
     {
      const T_str* separator = TOSTRING( T_str, "" );
      for ( const auto& elem: arr )
       {
        os << separator;
        os << elem;
        separator = TOSTRING( T_str, ", " );
       }
     }
    os << "]";
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
   * @return stype::ostream<T_str>& The stream to which the time object is printed to.
   */
  template <class T_str, class T_time, class int_type>
  stype::ostream<T_str>& operator <<( stype::ostream<T_str>& os, const std::chrono::duration<int_type, T_time>& val )
   {
    if constexpr( ! std::is_same_v<std::chrono::duration<int_type, T_time>, std::chrono::duration<int_type>> )
     {
      os << val.count() << sconstant::time_map[ typeid( T_time ) ];
     }
    else if constexpr( std::is_same_v<std::chrono::duration<int_type, T_time>, std::chrono::duration<int_type>> )
     {
      os << val.count() << "s";
     }
    return os;
   }

  //====================================================
  //     ptc_print class
  //====================================================
  /**
   * @brief Class used to construct the print function.
   * 
   * @tparam T _strThe type of the string objects defined inside the struct. This template is used in case you are dealing with std::string or std::wstring objects.
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
      end( TOSTRING( T_str, "\n" ) ),
      sep( TOSTRING( T_str, " " ) ),
      pattern( TOSTRING( T_str, "" ) ),
      flush( false )
      {       
       #ifdef PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
        performance_options();
       #endif
      }

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
       if constexpr ( std::is_base_of_v <stype::ostream<T_str>, std::remove_reference_t<T>> )
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
      * @return const stype::string<T_str> The whole print content in string format.
      */
     template <class... Args>
     const stype::string<T_str> operator()( mode&& first, Args&&... args ) const
      { 
       if constexpr( sizeof...( args ) > 0 )
        {
         switch( first )
          {
           case mode::str:
            {
             stype::ostringstream<T_str> oss;
             print_backend( oss, std::forward<Args>( args )... );
             return oss.str();
            }
          }
        }
       return null_str<stype::string<T_str>>;
      }

     // No arguments case
     /**
      * @brief Template operator redefinition used to print an empty line on the screen. This is the no argument case overload. Can be used with "ptc::print()" or "ptc::print( ostream_name )".
      * 
      * @param os The stream in which you want to print the output.
      */
     inline void operator () ( stype::ostream<T_str>& os = select_cout<T_str>::cout ) const
      {
       os << getEnd();
       if ( getFlush() ) os << std::flush;
      }
     
    private:

     //====================================================
     //     Private structs
     //====================================================

     // null_string
     /**
      * @brief Struct used to define the "null_str" constant. This workaround is needed for correct compilation in both gcc and clang.
      * 
      * @tparam T The template parameter of the future "null_string" constant.
      */
     template <class T> 
     struct null_string
      {
       inline static const stype::string<T_str> value = TOSTRING( T_str, "" );
      };

     //====================================================
     //     Private methods
     //====================================================

     // is_escape
     /**
      * @brief This method is used to check if an input variable is an ANSI escape sequency or not.
      * 
      * @tparam T Template type of the input variable.
      * @param str The input variable.
      * @param flag A flag which let to return different things with respect to its value. If flag = 0 the ANSI is searched as the first substring of the str argument, otherwise, if flag = 1 the ANSI is searched as a substring inside the str argument.
      * @return true If the input variable is an ANSI escape sequency.
      * @return false Otherwise.
      */
     template <typename T>
     static constexpr bool is_escape( const T& str, ANSI&& flag )
      {
       if constexpr( std::is_convertible_v <T, stype::string_view<T_str>> && ! std::is_same_v<T, std::nullptr_t> )
        {
         switch( flag )
          {
           case( ANSI::first ): 
            {
             return ( ! stype::string_view<T_str>( str ).rfind( TOSTRING( T_str, "\033" ), 0 ) ) && 
                    ( stype::string_view<T_str>( str ).length() < 7 );
            }
           case( ANSI::generic ):
            {
             return ( stype::string_view<T_str>( str ).find( TOSTRING( T_str, "\033" ) ) != stype::string_view<T_str>::npos );
            }
          }
        }
       return false;
      }

     // is_null_str
     /**
      * @brief This method is used to check if an input variable is a null string or not. Method used to ensure the required condition also in case of char, std::string, const char*... types.
      * 
      * @tparam T The templated type of the input variable.
      * @param str The input variable.
      * @return true If the variable is a null string.
      * @return false Otherwise.
      */
     template <typename T>
     static constexpr bool is_null_str( const T& str )
      {
       if constexpr( std::is_convertible_v <T, stype::string_view<T_str>> )
        {
         return str == null_str <T>;
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
       if( is_null_str( getPattern() ) || is_null_str( first ) || is_escape( first, ANSI::first ) ) os << first;
       else os << getPattern() << first << getPattern();

       // Printing all the other arguments
       if constexpr( sizeof...( args ) > 0 ) 
        {
         if ( is_null_str( first ) || is_escape( first, ANSI::first ) ) 
          {
           if( is_null_str( getPattern() ) ) ( ( os << args << getSep() ), ...);
           else ( ( os << getPattern() << args << getPattern() << getSep() ), ...);
          }
         else 
          {
           if( is_null_str( getPattern() ) ) ( ( os << getSep() << args ), ...);
           else ( ( os << getSep() << getPattern() << args << getPattern() ), ...);
          }
        }
       os << getEnd();

       // Resetting the stream from ANSI escape sequences
       if constexpr( sizeof...( args ) > 0 )
        {
         if ( is_escape( first, ANSI::generic ) || ( ( is_escape( args, ANSI::generic ) ) || ...) )
          {
           os << reset_ANSI;
          }
        }
       else 
        {
        if ( is_escape( first, ANSI::generic ) ) 
         {
          os << reset_ANSI;
         }
        }

       // Other operations
       if ( getFlush() && ! std::is_base_of_v <stype::ostringstream<T_str>, T_os> ) os << std::flush;
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
       select_cin<T_str>::cin.tie( NULL );
      }
     
     //====================================================
     //     Private attributes
     //====================================================
     stype::string<T_str> end, sep, pattern;
     static std::mutex mutex_;
     bool flush;

     //====================================================
     //     Private constants
     //====================================================
     inline static const stype::string<T_str> reset_ANSI = TOSTRING( T_str, "\033[0m" );
     template <class T> inline static const stype::string<T_str> null_str = Print::null_string<const T&>::value;
   };
   
  //====================================================
  //     Other steps
  //====================================================

  // Print::mutex_ definiton
  template <class T_str> inline std::mutex Print <T_str>::mutex_;

  // Print objects initialization
  inline Print <char> print;        // char
  inline Print <wchar_t> wprint;    // wchar_t
  //inline Print <char16_t> wprint_16;   // char16_t
  //inline Print <char32_t> wprint_32;   // char16_t
 }

#endif