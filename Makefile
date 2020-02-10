EXE = AP_BST.x
CXX = c++
CXXFLAGS = -I include -g -O3 -std=c++14 -Wall -Wextra -fPIC
SRC = main.cpp src/bst.cpp src/Node.cpp
OBJ = $(SRC:.cpp=.o)
INC = include/bst.hpp  include/Node.hpp
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
	rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ html latex

.PHONY: clean

%.o: %.cc ap_error.h
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

doc: Doxygen/doxy.in
	doxygen $^

.PHONY: doc

main.o: include/bst.hpp include/Node.hpp

src/bst.o: include/bst.hpp
src/Node.o: include/bst.hpp include/Node.hpp

format: $(SRC) $(INC)
	@clang-format -i $^ -verbose || echo "Please install clang-format to run this commands"

.PHONY: format
