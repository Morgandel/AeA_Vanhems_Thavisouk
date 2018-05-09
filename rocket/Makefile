OBJ=obj
SRC=src
INC=include
CXXFLAGS= -Wall -g -Wextra -std=c++14

#================================================
#                  Targets
#================================================

all: pareto

pareto : $(SRC)/main.cpp $(OBJ)/experience.o $(OBJ)/pareto_front.o $(OBJ)/options_parser.o $(OBJ)/solution.o
	g++ $^ $(CXXFLAGS) -o $@ -I $(INC)/

#=================== Objects ====================

$(OBJ)/pareto_front.o: $(INC)/pareto_front.hpp $(INC)/solution.hpp $(INC)/experience.hpp
$(OBJ)/solution.o : $(INC)/solution.hpp $(INC)/experience.hpp
$(OBJ)/experience.o : $(INC)/experience.hpp
$(OBJ)/options_parser.o : $(INC)/options_parser.hpp

#================================================
#                  Dummy rule
#================================================

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(@D)
	g++ $< $(CXXFLAGS) -c -o $@ -I $(INC)/

#================================================
#                Miscellaneous
#================================================

clean:
	rm -rf $(OBJ)/
	rm -f pareto

.PHONY: clean
