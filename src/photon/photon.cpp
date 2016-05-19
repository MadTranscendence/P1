#include "../common.hpp"
#include "photon.hpp"

#include <SDL2/SDL.h>


namespace Photon
{
    Photon::Photon(Core::Core* core)
        : m_freeListAllocator(Core::MBytesToBytes(64), core->getFreeListAllocator()),
          m_stackAllocator(Core::MBytesToBytes(64), core->getFreeListAllocator())
    {
        SDLLog(SDL_Init(SDL_INIT_VIDEO));

        std::cout << "Created Photon module\n";
    }

    Photon::~Photon()
    {
        SDL_Quit();

        std::cout << "Destructed Photon module\n";
    }

    Core::Allocator<Core::FreeListAllocator,
                    Core::FreeListAllocator>* Photon::getFreeListAllocator()
    {
        return &m_freeListAllocator;
    }

    Core::Allocator<Core::StackAllocator,
                    Core::FreeListAllocator>* Photon::getStackAllocator()
    {
        return &m_stackAllocator;
    }
}
