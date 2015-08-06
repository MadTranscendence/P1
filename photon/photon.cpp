#include "common.hpp"
#include "photon.hpp"

#include <SDL2/SDL.h>


namespace Photon
{
    Photon::Photon()
    {
        SDLLog(SDL_Init(SDL_INIT_VIDEO));

        std::cout << "Created Photon module\n";
    }

    Photon::~Photon()
    {
        SDL_Quit();

        std::cout << "Destructed Photon module\n";
    }
}
