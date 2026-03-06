#include <iostream>
#include <vector>
#include <string>
#include <cctype>

// ------------------- Token Definition -------------------
struct Token {
    std::string type;
    std::string value;
};

// ------------------- AST Nodes -------------------
struct ASTNode {
    std::string nodeType;
    std::string value;
    std::vector<ASTNode*> children;

    ASTNode(std::string t, std::string v) : nodeType(t), value(v) {}
};

// ------------------- Lexer (simplified) -------------------
std::vector<std::string> keywords = {
    "class", "func", "int", "float", "bool", "if", "else", "return"
};

bool is_keyword(const std::string& s) {
    for (auto& k : keywords) if (k == s) return true;
    return false;
}

// ------------------- Simple Lexer -------------------
std::vector<Token> lex(const std::string& code) {
    std::vector<Token> tokens;
    size_t i = 0;
    while (i < code.size()) {
        if (isspace(code[i])) { i++; continue; }

        // Identifiers / keywords
        if (isalpha(code[i]) || code[i] == '_') {
            std::string id;
            while (i < code.size() && (isalnum(code[i]) || code[i]=='_')) id += code[i++];
            if (is_keyword(id)) tokens.push_back({"KEYWORD", id});
            else tokens.push_back({"IDENT", id});
            continue;
        }

        // Numbers
        if (isdigit(code[i])) {
            std::string num;
            while (i < code.size() && (isdigit(code[i]) || code[i]=='.')) num += code[i++];
            tokens.push_back({"NUMBER", num});
            continue;
        }

        // Symbols
        std::string sym(1, code[i++]);
        if (sym == "{" || sym == "}" || sym == "(" || sym == ")" || sym == ";" || sym == "=" || sym == ",") {
            tokens.push_back({"SYMBOL", sym});
            continue;
        }

        std::cerr << "Unexpected char: " << sym << std::endl;
    }
    return tokens;
}

// ------------------- Parser -------------------
class Parser {
    std::vector<Token> tokens;
    size_t pos = 0;

public:
    Parser(const std::vector<Token>& t) : tokens(t) {}

    Token peek() {
        return pos < tokens.size() ? tokens[pos] : Token{"EOF",""};
    }

    Token consume() {
        return tokens[pos++];
    }

    ASTNode* parseClass() {
        // class IDENT { ... }
        consume(); // class
        Token name = consume(); // class name
        ASTNode* node = new ASTNode("Class", name.value);

        consume(); // {
        while (peek().value != "}") {
            node->children.push_back(parseStatement());
        }
        consume(); // }
        return node;
    }

    ASTNode* parseStatement() {
        Token t = peek();
        if (t.type == "KEYWORD" && t.value == "func") return parseFunc();
        if (t.type == "KEYWORD" && (t.value == "int" || t.value == "float" || t.value == "bool")) return parseVar();
        std::cerr << "Unknown statement: " << t.value << std::endl;
        return nullptr;
    }

    ASTNode* parseVar() {
        Token type = consume(); // int, float, bool
        Token name = consume(); // var name
        consume(); // =
        Token val = consume(); // number or literal
        consume(); // ;
        ASTNode* node = new ASTNode("VarDecl", name.value);
        node->children.push_back(new ASTNode("Type", type.value));
        node->children.push_back(new ASTNode("Value", val.value));
        return node;
    }

    ASTNode* parseFunc() {
        consume(); // func
        Token name = consume(); // func name
        consume(); // (
        // skip parameters for simplicity
        while (peek().value != ")") consume();
        consume(); // )
        consume(); // {
        ASTNode* node = new ASTNode("Func", name.value);
        // skip body for simplicity
        while (peek().value != "}") consume();
        consume(); // }
        return node;
    }

    ASTNode* parse() {
        return parseClass();
    }
};

// ------------------- Test -------------------
int main() {
    std::string code = R"(
class Player {
    int health = 100;
    func Move() { }
}
)";
    auto tokens = lex(code);
    Parser p(tokens);
    ASTNode* ast = p.parse();

    // Simple AST print
    std::cout << ast->nodeType << ": " << ast->value << std::endl;
    for (auto c : ast->children)
        std::cout << "  " << c->nodeType << ": " << c->value << std::endl;

    return 0;
}
