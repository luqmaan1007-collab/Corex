#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "Corex CPU Preview\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "[";
        for (int j = 0; j < i; ++j) std::cout << "#";
        for (int j = i; j < 10; ++j) std::cout << " ";
        std::cout << "] Frame " << i+1 << "\r";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << std::endl << "Done preview.\n";
}
