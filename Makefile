EXE = AP_BST.x
CXX = c++
CXXFLAGS = -g -O3 -std=c++14 -Wall -Wextra -fPIC
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)
INC = BST.hpp Iterator.hpp Node.hpp
DIST = README.md \
       Makefile \
       LICENSE

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cpp .o

all: $(EXE)

.PHONY: all

clean:
	rm -rf $(OBJ) $(EXE) *~ doc/_build

.PHONY: clean

%.o: %.cc ap_error.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

doc: Doxyfile
	doxygen $^

.PHONY: doc

main.o: main.cpp

format: $(SRC) $(INC)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this commands"

.PHONY: format
