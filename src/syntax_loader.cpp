#include <fstream>
#include <iostream>
#include <unordered_set>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::unordered_set<std::string> keywords;
std::unordered_set<std::string> functions;

void loadSyntax() {

    std::ifstream file("CorexSyntaxes/corexsyntax.json");

    if(!file.is_open()){
        std::cout<<"Failed to load syntax file\n";
        return;
    }

    json j;
    file >> j;

    for(auto& k : j["keywords"])
        keywords.insert(k);

    for(auto& f : j["functions"])
        functions.insert(f);
}
