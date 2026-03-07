#include "../include/token.h"
#include <vector>
#include <sstream>
#include <unordered_set>

extern std::unordered_set<std::string> keywords;
extern std::unordered_set<std::string> functions;

std::vector<Token> lex(const std::string& code){

std::vector<Token> tokens;
std::stringstream ss(code);
std::string word;

while(ss >> word){

if(keywords.count(word))
tokens.push_back({KEYWORD,word});

else if(functions.count(word))
tokens.push_back({FUNCTION,word});

else
tokens.push_back({IDENTIFIER,word});

}

tokens.push_back({END,""});
return tokens;

}
