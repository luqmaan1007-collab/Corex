#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>

// Force software rendering for Termux / Android
void set_cpu_mode_env() {
    setenv("LIBGL_ALWAYS_SOFTWARE", "1", 1);
    setenv("SDL_VIDEODRIVER", "software", 1);
}

// Simple CPU renderer: draws a moving rectangle
int main(int argc, char* argv[]) {
    set_cpu_mode_env();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Corex CPU Renderer",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       640, 480,
                                       SDL_WINDOW_SHOWN);
    if (!win) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
    if (!ren) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event e;
    int rectX = 0;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        // Clear screen
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
        SDL_RenderClear(ren);

        // Draw moving rectangle
        SDL_Rect rect{rectX, 200, 100, 100};
        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
        SDL_RenderFillRect(ren, &rect);

        SDL_RenderPresent(ren);

        rectX += 5;
        if (rectX > 640) rectX = -100;

        std::this_thread::sleep_for(std::chrono::milliseconds(33)); // ~30 FPS
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
