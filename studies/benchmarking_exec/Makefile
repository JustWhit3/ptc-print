#====================================================
#     Variables
#====================================================
ifeq ($(OS),Windows_NT)
	EXEC := benchmarking.exe
else
	EXEC := benchmarking
endif

#====================================================
#     FLAGS
#====================================================
WARNINGS := -Wall -Wextra -Wno-unused-function
EXTRAFLAGS := -std=c++17 -O3 -O1 -falign-functions=32 
LDFLAGS := -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lfmt -lpthread -o $(EXEC)

#====================================================
#     Compilation
#====================================================
bin/$(EXEC): benchmarking.o
	g++ benchmarking.o -o $(EXEC) $(LDFLAGS)
	@ mkdir -p obj bin
	@ mv *.o obj
	@ mv benchmarking bin

benchmarking.o: benchmarking.cpp
	g++ -c benchmarking.cpp $(EXTRAFLAGS) $(WARNINGS) 

clean:
	rm -rf obj bin