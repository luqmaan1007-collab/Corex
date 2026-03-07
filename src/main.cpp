#include <iostream>
#include <vector>
#include "../include/token.h"

extern void loadSyntax();
extern std::vector<Token> lex(const std::string&);

int main(){

loadSyntax();

std::string code = "print hello";

auto tokens = lex(code);

for(auto& t : tokens)
std::cout<<t.value<<"\n";

}
