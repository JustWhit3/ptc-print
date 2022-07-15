#====================================================
#     Variables
#====================================================
ifeq ($(OS),Windows_NT)
	EXEC := examples.exe
	TEST := tests.exe
else
	EXEC := examples
	TEST := tests
endif

#====================================================
#     FLAGS
#====================================================
WARNINGS := -Wall -Wextra -Wno-unused-but-set-variable
EXTRAFLAGS := -std=c++17 -g -MMD -MP
LDFLAGS := 
FLAGS := $(EXTRAFLAGS) $(WARNINGS) $(LDFLAGS)

#====================================================
#     Compilation
#====================================================
.PHONY: clean all

all: bin/$(EXEC) bin/$(TEST)

# Examples
bin/$(EXEC): examples.o
	g++ examples.o -o $(EXEC) $(LDFLAGS)
	@ mkdir -p obj bin
	@ mv *.o obj
	@ mv *.d obj
	@ mv examples bin

examples.o: examples.cpp
	g++ -c examples.cpp $(EXTRAFLAGS) $(WARNINGS) 

# Tests
bin/$(TEST): tests.o
	g++ tests.o -o $(TEST) $(LDFLAGS)
	@ mkdir -p obj bin
	@ mv *.o obj
	@ mv *.d obj
	@ mv tests bin

tests.o: test/tests.cpp
	g++ -c test/tests.cpp $(EXTRAFLAGS) $(WARNINGS) 

# Clean
clean:
	rm -rf obj bin