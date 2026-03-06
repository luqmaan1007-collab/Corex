#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void loadSyntaxes(const std::string& path) {
    std::ifstream f(path);
    if(!f) { std::cout << "Could not open " << path << "\n"; return; }
    json j; f >> j;
    std::cout << "Loaded " << j["patterns"].size() << " syntaxes\n";
}

int CorexMain() {
    std::cout << "Corex runtime initialized\n";
    loadSyntaxes("../CorexSyntaxes/corexsyntax.json");
    return 0;
}
