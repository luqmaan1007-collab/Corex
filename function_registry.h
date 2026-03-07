#pragma once
#include <string>
#include <unordered_map>
#include <functional>

extern std::unordered_map<std::string,std::function<void()>> corexFunctions;

void registerSyntaxFunction(const std::string& name);
void runFunction(const std::string& name);
