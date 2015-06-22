#include "common.h"
#include "photon.h"

#include <SDL2/SDL.h>


namespace Photon
{
    bool init()
    {
        SDL_Init(SDL_INIT_VIDEO);

        SDL_GL_SetSwapInterval(1);

        //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,    1);
        //SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,    2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,    1);

        return true;
    }

    void release()
    {
        SDL_Quit();
    }
}
