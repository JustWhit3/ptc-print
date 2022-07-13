#====================================================
#     Variables
#====================================================
ifeq ($(OS),Windows_NT)
	EXEC := print.exe
else
	EXEC := print
endif

#====================================================
#     FLAGS
#====================================================
WARNINGS := -Wall -Wextra -Wno-unused-but-set-variable
EXTRAFLAGS := -std=c++17 -g -O3 -O1 -falign-functions=32 
LDFLAGS := -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -L../../lib -o $(EXEC)

#====================================================
#     Compilation
#====================================================
bin/$(EXEC): print.o
	g++ print.o -o $(EXEC) $(LDFLAGS)
	@ mkdir -p obj bin
	@ mv *.o obj
	@ mv print bin

print.o: print.cpp
	g++ -c print.cpp $(EXTRAFLAGS) $(WARNINGS) 

clean:
	rm -rf obj bin