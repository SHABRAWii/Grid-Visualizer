

#include <iostream>

#include "Custom.h"

using namespace std;

int main(int argc, char* argv[]) {
    init();

    const char Path[] = "src/Commands.txt";
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
        if(is_Modified(Path)){
            cout << "Modified\n";
            cout << "____________\n";
            apply(Path, window);
            cout << "\n____________";
        }
    }

    clearWindow();

    return 0;
}