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
bin/$(EXEC):
	g++ print/examples.cpp $(FLAGS) -o $(EXEC)
	@ mkdir -p bin obj
	@ mv examples bin
	@ mv *.d obj

# Tests
bin/$(TEST):
	g++ print/tests.cpp $(FLAGS) -o $(TEST)
	@ mkdir -p bin obj
	@ mv tests bin
	@ mv *.d obj

clean:
	rm -rf obj bin