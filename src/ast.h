#pragma once
#include <string>

struct Node{
virtual ~Node(){}
};

struct FunctionCall : Node{
std::string name;
};
