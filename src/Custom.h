#ifdef __cplusplus
extern "C" {
#endif

#include <SDL2/SDL.h>

int init();
void render();
void clearWindow();
void resizeWindow(int, int);

#ifdef __cplusplus
}
#endif