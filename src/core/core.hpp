#ifndef CORE_HPP
#define CORE_HPP

#include "memory/allocator.hpp"


namespace Core
{
    class Core
    {
    public:
        Core();
        ~Core();

    private:
        Allocator<BaseAllocator>  m_baseAllocator;
        Allocator<StackAllocator> m_stackAllocator;
    };
}

#endif
