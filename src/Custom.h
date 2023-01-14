#ifdef __cplusplus
extern "C" {
#endif

#include <SDL2/SDL.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
int init(int max_X, int max_Y);
void render(const char *Path);
void clearWindow();
void resizeWindow(int, int);
bool is_Modified(const char *Path);
void apply(const char *Path);
void Bresenham_Algorithm(int x1, int y1, int x2, int y2, int color_HEX);
void Draw_Circle(int x, int y, int r, int color_HEX);

#ifdef __cplusplus
}
#endif