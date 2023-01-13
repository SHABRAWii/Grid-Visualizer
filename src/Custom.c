#include "Custom.h"

#include <stdbool.h>
#include <stdio.h>

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int DrawGrid(int rows, int columns, SDL_Window *window, SDL_Renderer *renderer) {
    // Declare rect of square
    SDL_Rect squareRect;

    // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
    squareRect.w = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / columns;
    squareRect.h = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / rows;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            squareRect.x = j * squareRect.w;
            squareRect.y = i * squareRect.h;

            if (i + j % 2) {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                // Draw filled square
            } else {
                SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
            }
            SDL_RenderFillRect(renderer, &squareRect);
            printf("%d %d\n", squareRect.x, squareRect.y);
        }
    }
}

SDL_Window *init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf(
            "SDL could not be initialized!\n"
            "SDL_Error: %s\n",
            SDL_GetError());
        return NULL;
    }

    // Create window
    SDL_Window *window = SDL_CreateWindow("Basic C SDL project",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        printf(
            "Window could not be created!\n"
            "SDL_Error: %s\n",
            SDL_GetError());
        return NULL;
    }

    return window;
}

void render(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf(
            "Renderer could not be created!\n"
            "SDL_Error: %s\n",
            SDL_GetError());
    }
    bool quit = false;

    // Event loop
    while (!quit) {
        SDL_Event e;

        // Wait indefinitely for the next available event
        SDL_WaitEvent(&e);

        // User requests quit
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        SDL_RenderClear(renderer);
        DrawGrid(10, 10, window, renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}