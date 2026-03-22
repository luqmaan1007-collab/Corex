#include "interpreter.cpp"
#include "ast.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Minimal AST parser stub
std::vector<Node*> parseCode(const std::string& code) {
    std::vector<Node*> nodes;
    FunctionCall* fn = new FunctionCall();
    fn->name = "test";  // Match a syntax in JSON
    nodes.push_back(fn);
    return nodes;
}

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if(!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return "";
    }
    return std::string((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
}

int main(int argc, char* argv[]) {
    if(argc < 3) {
        std::cout << "Usage: corex <corex_file> <syntax_json>\n";
        return 1;
    }

    std::string corexFile = argv[1];
    std::string syntaxFile = argv[2];

    loadCorexSyntaxes(syntaxFile);

    std::string code = readFile(corexFile);
    if(code.empty()) return 1;

    std::vector<Node*> nodes = parseCode(code);

    for(auto node : nodes) {
        run(node);
    }

    return 0;
}
