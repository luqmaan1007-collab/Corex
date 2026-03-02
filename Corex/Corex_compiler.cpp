#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>

// ------------------- Token -------------------
struct Token {
    std::string type;
    std::string value;
};

// ------------------- AST Node -------------------
struct ASTNode {
    std::string nodeType;
    std::string value;
    std::vector<ASTNode*> children;

    ASTNode(std::string t, std::string v) : nodeType(t), value(v) {}
    void addChild(ASTNode* c) { children.push_back(c); }

    void print(int indent = 0) {
        for (int i = 0; i < indent; i++) std::cout << "  ";
        std::cout << nodeType << ": " << value << std::endl;
        for (auto c : children) c->print(indent + 1);
    }
};

// ------------------- Lexer -------------------
std::vector<std::string> keywords = {
    "class","func","int","float","bool","if","else","for","while","return","include"
};

bool is_keyword(const std::string& s) {
    for (auto &k : keywords) if (k == s) return true;
    return false;
}

std::vector<Token> lex(const std::string& code) {
    std::vector<Token> tokens;
    size_t i = 0;
    while(i < code.size()) {
        char c = code[i];
        if (isspace(c)) { i++; continue; }

        // Handle #include
        if (c == '#' && code.substr(i, 8) == "#include") {
            i += 8;
            while (i < code.size() && isspace(code[i])) i++;
            std::string path;
            if (code[i] == '"') { i++; while (i < code.size() && code[i] != '"') path += code[i++]; i++; }
            else if (code[i] == '<') { i++; while (i < code.size() && code[i] != '>') path += code[i++]; i++; }
            tokens.push_back({"INCLUDE", path});
            continue;
        }

        // Numbers
        if (isdigit(c)) {
            std::string num;
            while (i<code.size() && (isdigit(code[i]) || code[i]=='.')) num += code[i++];
            tokens.push_back({"NUMBER", num});
            continue;
        }

        // Identifiers / keywords
        if (isalpha(c) || c=='_') {
            std::string id;
            while (i<code.size() && (isalnum(code[i])||code[i]=='_')) id+=code[i++];
            if (is_keyword(id)) tokens.push_back({"KEYWORD",id});
            else tokens.push_back({"IDENT",id});
            continue;
        }

        // Symbols
        std::string sym(1, code[i++]);
        if (sym == "{" || sym == "}" || sym == "(" || sym == ")" || sym == ";" || sym == "=" || sym == "," || sym == ".") {
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
    Parser(std::vector<Token> t) : tokens(t) {}

    Token peek() { return pos<tokens.size()?tokens[pos]:Token{"EOF",""}; }
    Token consume() { return tokens[pos++]; }

    ASTNode* parseInclude() {
        Token inc = consume(); // INCLUDE
        return new ASTNode("Include", inc.value);
    }

    ASTNode* parseVar() {
        Token type = consume(); // type
        Token name = consume(); // name
        consume(); // =
        Token val = consume(); // value
        consume(); // ;
        ASTNode* node = new ASTNode("VarDecl", name.value);
        node->addChild(new ASTNode("Type", type.value));
        node->addChild(new ASTNode("Value", val.value));
        return node;
    }

    ASTNode* parseFunc() {
        consume(); // func
        Token name = consume(); // function name
        consume(); // (
        while(peek().value != ")") consume();
        consume(); // )
        consume(); // {
        ASTNode* node = new ASTNode("Func", name.value);
        while(peek().value != "}") consume(); // skip body for simplicity
        consume(); // }
        return node;
    }

    ASTNode* parseClass() {
        consume(); // class
        Token name = consume(); // class name
        ASTNode* node = new ASTNode("Class", name.value);
        consume(); // {
        while(peek().value != "}") {
            Token t = peek();
            if (t.type=="KEYWORD" && t.value=="func") node->addChild(parseFunc());
            else if (t.type=="KEYWORD" && (t.value=="int"||t.value=="float"||t.value=="bool")) node->addChild(parseVar());
            else if (t.type=="INCLUDE") node->addChild(parseInclude());
            else { std::cerr << "Unknown statement: " << t.value << std::endl; consume(); }
        }
        consume(); // }
        return node;
    }

    ASTNode* parse() {
        ASTNode* root = new ASTNode("Program","CorexProgram");
        while(peek().type != "EOF") {
            if (peek().type=="INCLUDE") root->addChild(parseInclude());
            else if (peek().type=="KEYWORD" && peek().value=="class") root->addChild(parseClass());
            else consume();
        }
        return root;
    }
};

// ------------------- Main Test -------------------
int main() {
    std::string code = R"(
#include "Engine.corex"
class Player {
    int health = 100;
    float speed = 5.0;
    func Move() { }
}
)";
    auto tokens = lex(code);
    Parser parser(tokens);
    ASTNode* ast = parser.parse();
    ast->print();
    return 0;
}
