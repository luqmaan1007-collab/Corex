#include <iostream>
#include <fstream>
#include <unordered_map>
#include <regex>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// ANSI färger
const std::string RED    = "\033[31m";
const std::string GREEN  = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE   = "\033[34m";
const std::string MAGENTA= "\033[35m";
const std::string CYAN   = "\033[36m";
const std::string RESET  = "\033[0m";

// Syntax patterns
std::unordered_map<std::string,std::regex> patterns;

// Ladda syntaxer från JSON
void loadCorexSyntaxes(const std::string& jsonPath){
    std::ifstream file(jsonPath);
    if(!file.is_open()){
        std::cerr << "Failed to open syntax file: " << jsonPath << std::endl;
        return;
    }

    json j;
    file >> j;

    for(auto& pattern : j["patterns"]){
        if(pattern.contains("name") && pattern.contains("match")){
            std::string name = pattern["name"];
            std::string match = pattern["match"];
            patterns[name] = std::regex(match);
        }
    }
}

// Highlight en rad av Corex-kod
void highlightLine(const std::string& line){
    std::string highlighted = line;

    for(auto& kv : patterns){
        std::regex re = kv.second;
        highlighted = std::regex_replace(highlighted, re, BLUE + "$&" + RESET);
    }

    std::cout << highlighted << std::endl;
}

// Highlight en fil
void highlightFile(const std::string& filepath){
    std::ifstream file(filepath);
    if(!file.is_open()){
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return;
    }

    std::string line;
    while(std::getline(file, line)){
        highlightLine(line);
    }
}

// Test main
int main(){
    loadCorexSyntaxes("CorexSyntaxes/corexsyntax.json");

    std::cout << "=== Corex Syntax Highlight ===\n";

    // Exempel: highlight en Corex-fil
    highlightFile("example.corex"); // Skriv din Corex-fil här

    return 0;
}
