#include "ast.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <functional>
#include <nlohmann/json.hpp> // nlohmann/json måste finnas i projektet

using json = nlohmann::json;

// Function registry
std::unordered_map<std::string,std::function<void()>> corexFunctions;

// Registrera en syntax med en enkel logic stub
void registerSyntax(const std::string& name){
    corexFunctions[name] = [name](){
        std::cout << "Corex syntax executed: " << name << std::endl;
        // Här kan du lägga riktig logic per syntax
    };
}

// Ladda alla syntaxer från JSON och registrera dem
void loadCorexSyntaxes(const std::string& jsonPath){
    std::ifstream file(jsonPath);
    if(!file.is_open()){
        std::cerr << "Failed to open syntax file: " << jsonPath << std::endl;
        return;
    }

    json j;
    file >> j;

    // Exempel: JSON med "patterns" array
    for(auto& pattern : j["patterns"]){
        if(pattern.contains("name")){
            std::string name = pattern["name"];
            registerSyntax(name);
        }
    }
}

// Kör AST node
void run(Node* node){
    if(auto fn = dynamic_cast<FunctionCall*>(node)){
        auto it = corexFunctions.find(fn->name);
        if(it != corexFunctions.end()){
            it->second(); // Kör function
        } else {
            std::cout << "Unknown Corex syntax: " << fn->name << std::endl;
        }
    }
}
