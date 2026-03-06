#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>
#include <regex>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

enum TokenType {
    IDENTIFIER,
    NUMBER,
    STRING,
    KEYWORD,
    END
};

struct Token {
    TokenType type;
    string value;
};

class Lexer {
public:

    vector<Token> tokenize(string code) {

        vector<Token> tokens;
        string current;

        for(char c : code) {

            if(isspace(c)) {
                if(!current.empty()) {
                    tokens.push_back({IDENTIFIER,current});
                    current.clear();
                }
            }
            else if(isalnum(c) || c=='_')
                current += c;

            else {

                if(!current.empty()) {
                    tokens.push_back({IDENTIFIER,current});
                    current.clear();
                }

                string s(1,c);
                tokens.push_back({STRING,s});
            }
        }

        if(!current.empty())
            tokens.push_back({IDENTIFIER,current});

        tokens.push_back({END,""});
        return tokens;
    }
};

class ASTNode {
public:
    string value;
    vector<ASTNode*> children;

    ASTNode(string v) {
        value = v;
    }
};

class Parser {

public:

    ASTNode* parse(vector<Token> tokens) {

        ASTNode* root = new ASTNode("PROGRAM");

        for(auto &t : tokens) {

            if(t.type == IDENTIFIER) {
                ASTNode* node = new ASTNode(t.value);
                root->children.push_back(node);
            }
        }

        return root;
    }
};

class Runtime {

public:

    map<string,function<void()>> functions;

    void registerFunction(string name,function<void()> fn) {
        functions[name] = fn;
    }

    void execute(string name) {

        if(functions.count(name))
            functions[name]();

        else
            cout<<"Unknown syntax: "<<name<<endl;
    }
};

Runtime runtime;

class Interpreter {

public:

    void executeAST(ASTNode* node) {

        if(node->value!="PROGRAM")
            runtime.execute(node->value);

        for(auto child : node->children)
            executeAST(child);
    }
};

void loadSyntaxPatterns(string path) {

    ifstream file(path);
    json data;
    file >> data;

    for(auto &p : data["patterns"]) {

        string name = p["name"];

        runtime.registerFunction(name,[name](){

            cout<<"Executing syntax pattern: "<<name<<endl;

        });
    }
}

void registerCoreFunctions() {

    runtime.registerFunction("greet",[](){
        cout<<"Hello from Corex"<<endl;
    });

    runtime.registerFunction("initialize",[](){
        cout<<"Corex runtime initialized"<<endl;
    });

    runtime.registerFunction("pingServer",[](){
        system("ping -c 1 8.8.8.8");
    });

    runtime.registerFunction("readFile",[](){
        cout<<"File reading executed"<<endl;
    });

    runtime.registerFunction("writeFile",[](){
        cout<<"File writing executed"<<endl;
    });
}

int main() {

    loadSyntaxPatterns("corexsyntax.json");

    registerCoreFunctions();

    string code = R"(

        initialize
        greet
        pingServer
        readFile
        writeFile

    )";

    Lexer lexer;
    Parser parser;
    Interpreter interpreter;

    vector<Token> tokens = lexer.tokenize(code);

    ASTNode* tree = parser.parse(tokens);

    interpreter.executeAST(tree);

}
