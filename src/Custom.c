#include "Custom.h"

#include <stdbool.h>
#include <stdio.h>

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int DrawGrid(int rows, int columns, SDL_Window *window, SDL_Renderer *renderer) {
    // Declare rect of square
    SDL_Rect board;

    board.w = MIN(SCREEN_WIDTH, SCREEN_HEIGHT);
    board.h = MIN(SCREEN_WIDTH, SCREEN_HEIGHT);

    board.x = (SCREEN_WIDTH - board.w) / 2;
    board.y = (SCREEN_HEIGHT - board.h) / 2;

    SDL_Rect square;
    square.w = board.w / columns;
    square.h = board.h / rows;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            square.x = j * square.w + board.x;
            square.y = i * square.h + board.y;

            if ((i + j) % 2) {
                SDL_SetRenderDrawColor(renderer, 180, 180, 180, 0xFF);
                // Draw filled square
            } else {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0xFF);
            }
            SDL_RenderFillRect(renderer, &square);
        }
    }

    int axisThickness = 8 * square.w / 100;
    for (int i = board.y - square.w / 2; i + square.w / 2 < board.y + board.h; i++) {
        SDL_Rect pixel;
        pixel.w = axisThickness;
        pixel.h = 1;
        pixel.x = (board.x + board.x + board.w) / 2 - axisThickness / 2 + square.w / 2;
        pixel.y = i + square.w / 2;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &pixel);
    }

    for (int i = board.x - square.w / 2; i + square.w / 2 < board.x + board.w; i++) {
        SDL_Rect pixel;
        pixel.h = axisThickness;
        pixel.w = 1;
        pixel.y = (board.y + board.y + board.h) / 2 - axisThickness / 2 + square.w / 2;
        pixel.x = i + square.w / 2;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &pixel);
    }
}

int init() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf(
            "SDL could not be initialized!\n"
            "SDL_Error: %s\n",
            SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Basic C SDL project",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf(
            "Window could not be created!\n"
            "SDL_Error: %s\n",
            SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf(
            "Renderer could not be created!\n"
            "SDL_Error: %s\n",
            SDL_GetError());
        return 1;
    }

    return 0;
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    DrawGrid(11, 11, window, renderer);
    SDL_RenderPresent(renderer);
}

void resizeWindow(int width, int height) {
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
}

void clearWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}