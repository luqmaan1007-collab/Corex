CXX = clang++
CXXFLAGS = -std=c++17 -O2 -Iinclude
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXE = corex

all: $(EXE)

$(EXE): $(OBJ)
$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
rm -f $(OBJ) $(EXE)
