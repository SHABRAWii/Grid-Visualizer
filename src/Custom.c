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
SDL_Rect board;
SDL_Rect square;
int rows, columns;
int DrawGrid(SDL_Window *window, SDL_Renderer *renderer) {
    board.w = MIN(SCREEN_WIDTH, SCREEN_HEIGHT);
    board.h = MIN(SCREEN_WIDTH, SCREEN_HEIGHT);

    board.x = (SCREEN_WIDTH - board.w) / 2;
    board.y = (SCREEN_HEIGHT - board.h) / 2;

    square.w = board.w / columns;
    square.h = board.h / rows;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            square.x = j * square.w + board.x;
            square.y = i * square.h + board.y;

            if ((i + j) % 2) {
                SDL_SetRenderDrawColor(renderer, 180, 180, 180, 0xFF);

            } else {
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0xFF);
            }
            SDL_RenderFillRect(renderer, &square);
        }
    }

    int axisThickness = (8 * square.w + 99) / 100;
    printf("%d\n", board.y + board.h);
    int mxi = -1;
    for (int i = board.y; i < board.y + board.h; i++) {
        SDL_Rect pixel;
        pixel.w = axisThickness;
        pixel.h = 1;
        pixel.x = (board.x + board.x + board.w) / 2 - axisThickness / 2 + (rows % 2 ? 0 : square.w / 2);
        pixel.y = i;
        mxi = MAX(i, mxi);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &pixel);
    }

    printf("%d\n", mxi);
    for (int i = board.x; i < board.x + board.w; i++) {
        SDL_Rect pixel;
        pixel.h = axisThickness;
        pixel.w = 1;
        pixel.y = (board.y + board.y + board.h) / 2 - axisThickness / 2 + (columns % 2 ? 0 : square.w / 2);
        pixel.x = i;

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
    printf("Number of Rows : ");
    scanf("%d", &rows);
    printf("Number of Columns : ");
    scanf("%d", &columns);
    rows = rows * 2 + 1;
    columns = columns * 2 + 1;
    return 0;
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    DrawGrid(window, renderer);
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