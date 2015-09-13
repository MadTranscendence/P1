#ifndef CORE_HPP
#define CORE_HPP

#include "memory/standardAllocator.hpp"


namespace Core
{
    class Core
    {
    public:
        Core();
        ~Core();

    private:
        Allocator<BaseAllocator>     m_baseAllocator;
        Allocator<FreeListAllocator> m_freeListAllocator;
        Allocator<StackAllocator>    m_stackAllocator;
    };
}

#endif
