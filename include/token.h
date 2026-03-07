#pragma once
#include <string>

enum TokenType {

IDENTIFIER,
NUMBER,
KEYWORD,
FUNCTION,
SYMBOL,
END
};

struct Token{
TokenType type;
std::string value;
};
