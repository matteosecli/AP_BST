EXE  = AP_BST
CXX  = c++
CXXFLAGS = -g -O3 -std=c++14 -Wall -Wextra -fPIC
SRC  = main.cpp
OBJ  = $(SRC:.cpp=.o)
INC  = src
DIST = README.md \
       Makefile \
       LICENSE

TESTSRC = test/000-CatchMain.cpp test/010-NodeTest.cpp test/020-IteratorTest.cpp test/030-TreeTest.cpp
TESTOBJ  = $(TESTSRC:.cpp=.o)
TESTEXE = test/test

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cpp .o

all: $(EXE)

.PHONY: all

$(EXE): $(SRC)
	$(CXX) $^ -o $@ -I $(INC) $(FLAGS)

test: $(TESTEXE)

.PHONY: test

$(TESTEXE): $(TESTSRC)
	$(CXX) $^ -o $@ -I ./$(INC) $(FLAGS)

clean:
	rm -rf $(OBJ) $(EXE) $(TESTOBJ) $(TESTEXE) *~ doc/_build

.PHONY: clean

doc: Doxyfile
	doxygen $^

.PHONY: doc

main.o: main.cpp

format: $(SRC) $(INC)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this commands"

.PHONY: format
