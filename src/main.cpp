

#include <iostream>

#include "Custom.h"

using namespace std;

int main(int argc, char* argv[]) {
    SDL_Window* window = init();
    render(window);

    return 0;
}