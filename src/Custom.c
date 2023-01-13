#include "Custom.h"


#include <stdio.h>
#include <string.h>

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

int CELL[1000][1000];
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Rect board;
SDL_Rect square;
int rows, columns;
int DrawGrid() {
    board.w = MIN(SCREEN_WIDTH, SCREEN_HEIGHT);
    board.h = MIN(SCREEN_WIDTH, SCREEN_HEIGHT);

    board.x = (SCREEN_WIDTH - board.w) / 2;
    board.y = (SCREEN_HEIGHT - board.h) / 2;

    square.w = board.w / columns;
    square.h = board.h / rows;

    board.w = columns * square.w;
    board.h = rows * square.h;

    int verticalPadding = 0;
    int horizontalPadding = 0;
    if (SCREEN_HEIGHT > SCREEN_WIDTH) {
        horizontalPadding = (SCREEN_WIDTH - board.w) / 2;
    } else {
        verticalPadding = (SCREEN_HEIGHT - board.h) / 2;
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            square.x = j * square.w + board.x + horizontalPadding;
            square.y = i * square.h + board.y + verticalPadding;

            if(!~CELL[j][i]){
                if ((i + j) % 2) {
                    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 0xFF);

                } else {
                    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0xFF);
                }
            }else{
                int R = (CELL[j][i] >> 16) & 0xFF;
                int G = (CELL[j][i] >> 8) & 0xFF;
                int B = (CELL[j][i])      & 0xFF;
                SDL_SetRenderDrawColor(renderer, R, G, B, 0xFF);
            }
            SDL_RenderFillRect(renderer, &square);
        }
    }

    int axisThickness = (8 * square.w + 99) / 100;

    for (int i = board.y; i < board.y + board.h; i++) {
        SDL_Rect pixel;
        pixel.w = axisThickness;
        pixel.h = 1;
        pixel.x = (board.x + board.x + board.w) / 2 - axisThickness / 2 + (rows % 2 ? 0 : square.w / 2) + horizontalPadding;
        pixel.y = i + verticalPadding;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &pixel);
    }

    for (int i = board.x; i < board.x + board.w; i++) {
        SDL_Rect pixel;
        pixel.h = axisThickness;
        pixel.w = 1;
        pixel.y = (board.y + board.y + board.h) / 2 - axisThickness / 2 + (columns % 2 ? 0 : square.w / 2) + verticalPadding;
        pixel.x = i + horizontalPadding;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &pixel);
    }
}

int init() {
    memset(CELL, -1, sizeof(CELL));
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
    // scanf("%d", &rows);
    printf("Number of Columns : ");
    // scanf("%d", &columns);
    rows = columns = 5;
    rows = rows * 2 + 1;
    columns = columns * 2 + 1;
    return 0;
}

void render(const char *Path) {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    DrawGrid();
    if(is_Modified(Path)){
        printf("Modified\n");
        printf("____________\n");
        apply(Path);
        printf("\n____________");
    }
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
bool is_Modified(const char *Path) {
    static time_t last_modified = 0;
    struct stat file_stat;
    return (!stat(Path, &file_stat)) && (file_stat.st_mtime > last_modified) && (last_modified = file_stat.st_mtime);
}
void apply(const char *Path) {
    FILE *Commands = fopen(Path,"r");
    char Command[21]; // SP 0000 0000 #000000
    while(fgets(Command, 21, Commands)) {
        // printf("%s", Command);
        int cnt = 0, X = -INT32_MIN, Y = -INT32_MIN, color_HEX = -2;
        if(Command[0] == 'S') {
            sscanf(Command, "SP %d %d #%d", &X, &Y, &color_HEX);
            printf("Setting Pixel at X(%d) Y(%d) to R(-) G(-) B(-)", X, Y);
        } else if(Command[0] == 'C') {
            if(Command[2] == 'A'){
                memset(CELL, -1, sizeof(CELL)); // Clear All cells
                continue;
            }else{
                sscanf(Command, "CL %d %d", &X, &Y);
                color_HEX = -1; // This is tag of Cleared Cell
            }
        }
        if(X == -INT32_MIN || Y == -INT32_MIN || color_HEX == -2){ // Invalid Command
            break;
        }
        CELL[(X + rows / 2)][ - Y + columns / 2] = color_HEX; // Apply formatting to the cell at X, Y
    }
    return;
}