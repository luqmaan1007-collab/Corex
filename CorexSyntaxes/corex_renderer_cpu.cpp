#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>

// Förenklad Corex-syntax demo (CPU-only preview)
int main() {
    std::vector<std::string> syntaxes = {
        "continueLoop", "breakLoop", "exitLoop", "returnValue", "throwError"
    };

    std::cout << "Corex CPU Preview\n";

    for (int frame = 0; frame < 10; ++frame) {
        std::cout << "[Frame " << frame + 1 << "] Syntaxes executed: ";
        for (auto &s : syntaxes) {
            std::cout << s << " ";
        }
        std::cout << std::endl;  // <-- stäng rad korrekt
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    std::cout << "Done preview.\n";
    return 0;
}
