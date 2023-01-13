#ifdef __cplusplus
extern "C" {
#endif

    #include <SDL2/SDL.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <time.h>
    #include <stdbool.h>
    SDL_Window* init();
    void render(SDL_Window*);
    bool is_Modified(const char *Path);
    void apply(const char *Path, SDL_Window *window);
    
#ifdef __cplusplus
}
#endif