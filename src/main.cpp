#include "interpreter.cpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Usage: corex <file.corex>\n";
        return 1;
    }

    std::string filename = argv[1];

    // FIX: replace "test" with a valid syntax
    std::string fn_name = "kernel_main"; // must match your JSON

    std::cout << "Running Corex function: " << fn_name << "\n";

    // Call your Corex interpreter
    if(!runCorexFile(filename)) {
        std::cerr << "Error running " << filename << "\n";
        return 1;
    }

    return 0;
}
