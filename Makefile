# Corex Makefile - foolproof version

CXX = clang++
CXXFLAGS = -std=c++17 -O2 -Iinclude
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp,build/%.o,$(SRC))
EXE = corex

# Ensure build directory exists
BUILD_DIR = build
$(shell mkdir -p $(BUILD_DIR))

# Default target
all: $(EXE)

# Link executable
$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to build/*.o
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf build/*.o $(EXE)
