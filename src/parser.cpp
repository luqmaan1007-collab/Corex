#include "../include/token.h"
#include "ast.h"
#include <vector>

class Parser{

public:

std::vector<Token> tokens;
int pos = 0;

Parser(std::vector<Token> t){
tokens = t;
}

Node* parse(){

if(tokens[pos].type == FUNCTION){

FunctionCall* fn = new FunctionCall();
fn->name = tokens[pos].value;
return fn;

}

return nullptr;

}

};
