#include "../common.hpp"
#include "core.hpp"

#include <xmmintrin.h>
#include <pmmintrin.h>


namespace Core
{
    Core::Core()
        : m_freeListAllocator(MBytesToBytes(256), &m_baseAllocator),
          m_stackAllocator(MBytesToBytes(64), &m_baseAllocator)
    {
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);

        std::cout << "Created Core module\n";
    }

    Core::~Core()
    {
        std::cout << "Destructed Core module\n";
    }

    Allocator<FreeListAllocator>* Core::getFreeListAllocator()
    {
        return &m_freeListAllocator;
    }

    Allocator<StackAllocator>* Core::getStackAllocator()
    {
        return &m_stackAllocator;
    }
}
