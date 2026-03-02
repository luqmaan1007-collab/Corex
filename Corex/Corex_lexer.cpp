// corex_lexer.cpp (with #include)
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

struct Token {
    std::string type;
    std::string value;
};

std::vector<std::string> keywords = {
    "class", "func", "if", "else", "for", "while", "return",
    "int", "float", "bool", "Destroy"
};

bool is_keyword(const std::string& s) {
    for (auto& k : keywords) if (k == s) return true;
    return false;
}

std::vector<Token> lex(const std::string& code) {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < code.size()) {
        char c = code[i];

        if (isspace(c)) { i++; continue; }

        // Handle #include
        if (c == '#' && code.substr(i, 8) == "#include") {
            i += 8;
            while (i < code.size() && isspace(code[i])) i++;
            std::string path;
            if (code[i] == '"') {  // "file"
                i++;
                while (i < code.size() && code[i] != '"') path += code[i++];
                i++; // skip closing "
            } else if (code[i] == '<') { // <file>
                i++;
                while (i < code.size() && code[i] != '>') path += code[i++];
                i++; // skip closing >
            }
            tokens.push_back({"INCLUDE", path});
            continue;
        }

        // Numbers
        if (isdigit(c)) {
            std::string num;
            while (i < code.size() && (isdigit(code[i]) || code[i]=='.')) num += code[i++];
            tokens.push_back({"NUMBER", num});
            continue;
        }

        // Identifiers / keywords
        if (isalpha(c) || c == '_') {
            std::string id;
            while (i < code.size() && (isalnum(code[i]) || code[i]=='_')) id += code[i++];
            if (is_keyword(id)) tokens.push_back({"KEYWORD", id});
            else tokens.push_back({"IDENT", id});
            continue;
        }

        // Strings
        if (c == '"') {
            std::string str = "\"";
            i++;
            while (i < code.size() && code[i] != '"') str += code[i++];
            str += "\""; i++;
            tokens.push_back({"STRING", str});
            continue;
        }

        // Operators & symbols
        std::string two = i+1 < code.size() ? std::string() + code[i] + code[i+1] : "";
        if (two == "==" || two == "!=" || two == "<=" || two == ">=") {
            tokens.push_back({"OPERATOR", two}); i += 2; continue;
        }

        std::string one = std::string(1, code[i]);
        if (one == "+" || one == "-" || one == "*" || one == "/" || one == "=" ||
            one == "<" || one == ">" || one == "{" || one == "}" || one == "(" ||
            one == ")" || one == ";" || one == "," || one == ".") {
            tokens.push_back({"SYMBOL", one}); i++; continue;
        }

        std::cerr << "Unexpected char: " << c << std::endl;
        i++;
    }
    return tokens;
}

// Example usage
int main() {
    std::string code = R"(
#include "Engine.corex"
#include <Physics.corex>

class Player {
    int health = 100;
    func Move(Vector3 direction, float deltaTime) { }
}
)";
    auto tokens = lex
