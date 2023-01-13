

#include <iostream>

#include "Custom.h"

using namespace std;

int main(int argc, char* argv[]) {
    init();

    bool quit = false;

    // Event loop
    while (!quit) {
        SDL_Event e;

        // Wait indefinitely for the next available event
        if (SDL_PollEvent(&e) > 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                        resizeWindow(e.window.data1, e.window.data2);
                    }

                default:
                    break;
            }
        }

        render();

        
    }

    clearWindow();

    return 0;
}