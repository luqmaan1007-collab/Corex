CXX = clang++
CXXFLAGS = -std=c++17 -O2 -Iinclude
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = corex

all: $(EXE)

$(EXE): $(OBJ)
<TAB>$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
<TAB>$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
<TAB>rm -f $(OBJ) $(EXE)
