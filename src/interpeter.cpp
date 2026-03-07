#include "ast.h"
#include <iostream>

void run(Node* node){

if(auto fn = dynamic_cast<FunctionCall*>(node)){

if(fn->name == "print")
std::cout<<"Print function\n";

if(fn->name == "spawnThread")
std::cout<<"Thread started\n";

}

}
