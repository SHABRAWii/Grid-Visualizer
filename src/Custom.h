#ifdef __cplusplus
extern "C" {
#endif

#include <SDL2/SDL.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
int init();
void render();
void clearWindow();
void resizeWindow(int, int);
bool is_Modified(const char *Path);
void apply(const char *Path);

#ifdef __cplusplus
}
#endif