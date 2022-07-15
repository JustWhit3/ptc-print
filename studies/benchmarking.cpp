//====================================================
//     Headers
//====================================================

// My headers
#include "../ptc/print.hpp"

// Headers for comparison

// Extra headers
#include <benchmark/benchmark.h>

// STD headers

//====================================================
//     Namespace directives
//====================================================
namespace bm = benchmark;

//====================================================
//     osmanip
//====================================================

// empty
/*static void osmanip_common_feat( bm::State& state ) 
 {
  for ( auto _ : state ) bm::DoNotOptimize( std::cout << osm::feat( osm::col, "red" ) );
 }

//====================================================
//     Benchmarking settings
//====================================================

// osmanip
BENCHMARK( osmanip_common_feat );*/

BENCHMARK_MAIN();