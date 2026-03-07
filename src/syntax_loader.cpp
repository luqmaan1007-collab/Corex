#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include "function_registry.h"

using json = nlohmann::json;

void loadCorexSyntax(){

std::ifstream file("CorexSyntaxes/corexsyntax.json");

if(!file.is_open()){
std::cout<<"Could not load syntax file\n";
return;
}

json j;
file >> j;

for(auto& s : j["syntax"]){

std::string name = s;
registerSyntaxFunction(name);

}

}
