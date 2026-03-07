#include "interpreter.cpp"  // interpreter finns i src
#include "ast.h"            // AST-definitioner finns i src
#include <iostream>

int main() {
    // 1️⃣ Ladda alla Corex-syntaxer från JSON
    loadCorexSyntaxes("../CorexSyntaxes/corexsyntax.json"); // OBS: sökvägen från src

    // 2️⃣ Skapa exempel AST-noder
    FunctionCall node1;
    node1.name = "print";

    FunctionCall node2;
    node2.name = "spawnThread";

    FunctionCall node3;
    node3.name = "unknownFunc"; // För test av okänd syntax

    // 3️⃣ Kör interpreter
    run(&node1);
    run(&node2);
    run(&node3);

    // 4️⃣ Kör alla syntaxer från JSON automatiskt (valfritt)
    std::cout << "\nExecuting all registered Corex syntaxes:\n";
    for (auto& kv : corexFunctions) {
        std::cout << "Running: " << kv.first << " -> ";
        kv.second();
    }

    return 0;
}
