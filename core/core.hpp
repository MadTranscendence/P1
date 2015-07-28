#ifndef CORE_HPP
#define CORE_HPP

#include "memory/linearAllocator.hpp"
#include "memory/stackAllocator.hpp"


namespace Core
{
    class Core
    {
    public:
        Core();
        ~Core();

    private:
        Allocator<StackAllocator> m_allocator;
    };
}

#endif
