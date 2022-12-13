#include <pprint/pprint.hpp>

int main()
 {
  pprint::PrettyPrinter printer;
  printer.print( "Testing", 123, "print", '!' );
 }