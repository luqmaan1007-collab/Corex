CXX = clang++
CXXFLAGS = -std=c++17 -O2 -Iinclude
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o)
EXE = corex

# Ensure build directory exists
BUILD_DIR = build
$(shell mkdir -p $(BUILD_DIR))

all: $(EXE)

# Link the executable
$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files to object files
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf build/*.o $(EXE)
