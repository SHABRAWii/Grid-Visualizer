

#include <iostream>

#include "Custom.h"

using namespace std;

int main(int argc, char* argv[]) {
    // SDL_Window* window = init();
    SDL_Window* window;
    const char Path[] = "src/Commands.txt";
    for(;;){
        // render(window);
        if(is_Modified(Path)){
            cout << "Modified\n";
            cout << "____________\n";
            apply(Path, window);
            cout << "\n____________";
        }
    }
    return 0;
}