#ifndef PHOTON_HPP
#define PHOTON_HPP

#include "../core/core.hpp"


namespace Photon
{
    class Photon
    {
    public:
        Photon(Core::Core* core);
        ~Photon();

        Core::Allocator<Core::FreeListAllocator,
                        Core::FreeListAllocator>* getFreeListAllocator();
        Core::Allocator<Core::StackAllocator,
                        Core::FreeListAllocator>* getStackAllocator();

    private:
        Core::Allocator<Core::FreeListAllocator,
                        Core::FreeListAllocator> m_freeListAllocator;
        Core::Allocator<Core::StackAllocator,
                        Core::FreeListAllocator> m_stackAllocator;
    };
}

#endif
