#include <iostream>
#include "CorexRuntime.cpp"

int main() {
    std::cout << "Corex CPU Preview\n";
    for(int frame=1; frame<=10; frame++) {
        std::cout << "[Frame " << frame << "] Syntaxes executed: continueLoop breakLoop exitLoop returnValue\n";
    }
    std::cout << "Done preview.\n";
    return CorexMain();
}
