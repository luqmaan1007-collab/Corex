CXX = clang++
CXXFLAGS = -std=c++17 -O2 -Iinclude
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = corex

all: $(EXE)

$(EXE): $(OBJ)
<TAB here>$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
<TAB here>$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
<TAB here>rm -f $(OBJ) $(EXE)
