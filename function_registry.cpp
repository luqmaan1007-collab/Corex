#include "function_registry.h"
#include <iostream>

std::unordered_map<std::string,std::function<void()>> corexFunctions;

void registerSyntaxFunction(const std::string& name){

corexFunctions[name] = [name](){
std::cout << "Corex syntax executed: " << name << std::endl;
};

}

void runFunction(const std::string& name){

if(corexFunctions.count(name))
corexFunctions[name]();
else
std::cout << "Unknown syntax: " << name << std::endl;

}
