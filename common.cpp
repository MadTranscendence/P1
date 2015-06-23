#include "common.hpp"
#include <SDL2/SDL.h>


void SDLLog(int result)
{
    if(result < 0)
        std::cout << "SDL Error: " << SDL_GetError() << '\n';

    SDL_ClearError();
}
