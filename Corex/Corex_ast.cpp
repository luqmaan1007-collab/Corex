#include <iostream>
#include <vector>
#include <string>

// ------------------- AST Node Definition -------------------
struct ASTNode {
    std::string nodeType;         // Class, Func, VarDecl, etc.
    std::string value;            // Name of class, func, variable, etc.
    std::vector<ASTNode*> children;

    ASTNode(std::string type, std::string val) : nodeType(type), value(val) {}

    void addChild(ASTNode* child) {
        children.push_back(child);
    }

    void print(int indent = 0) {
        for (int i = 0; i < indent; i++) std::cout << "  ";
        std::cout << nodeType << ": " << value << std::endl;
        for (auto c : children)
            c->print(indent + 1);
    }
};

// ------------------- Example AST Creation -------------------
int main() {
    // Create root: a class
    ASTNode* playerClass = new ASTNode("Class", "Player");

    // Add a variable
    ASTNode* healthVar = new ASTNode("VarDecl", "health");
    healthVar->addChild(new ASTNode("Type", "int"));
    healthVar->addChild(new ASTNode("Value", "100"));
    playerClass->addChild(healthVar);

    // Add a function
    ASTNode* moveFunc = new ASTNode("Func", "Move");
    // Parameters could be children
    moveFunc->addChild(new ASTNode("Param", "Vector3 direction"));
    moveFunc->addChild(new ASTNode("Param", "float deltaTime"));
    // Body could be children too
    moveFunc->addChild(new ASTNode("Body", "{ position += direction * speed * deltaTime; }"));
    playerClass->addChild(moveFunc);

    // Print AST
    playerClass->print();

    return 0;
}
