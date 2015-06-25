#ifndef CORE_HPP
#define CORE_HPP

#include "memory/linearAllocator.hpp"


namespace Core
{
    class Core
    {
    public:
        Core();
        ~Core();

    private:
        Allocator<LinearAllocator> m_allocator;
    };
}

#endif
