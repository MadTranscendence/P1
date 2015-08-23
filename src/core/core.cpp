#include "../common.hpp"
#include "core.hpp"

#include <xmmintrin.h>
#include <pmmintrin.h>


namespace Core
{
    Core::Core() : m_stackAllocator(1024*30, &m_baseAllocator)
    {
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);

        std::cout << "Created Core utils\n";

        int* arr1 = m_stackAllocator.allocArray<int>(5, 2);
        int* arr2 = m_stackAllocator.allocArray<int>(15, 2);
        int* arr3 = m_stackAllocator.allocArray<int>(35, 2);
        int* arr4 = m_stackAllocator.allocArray<int>(75, 2);
        int* arr5 = m_stackAllocator.allocArray<int>(125, 2);
        m_stackAllocator.deallocArray(arr5);
        m_stackAllocator.deallocArray(arr4);
        m_stackAllocator.deallocArray(arr3);
        m_stackAllocator.deallocArray(arr2);
        m_stackAllocator.deallocArray(arr1);

        int* a = m_stackAllocator.alloc<int>(2);
        m_stackAllocator.dealloc(a);
    }

    Core::~Core()
    {
        std::cout << "Destructed Core utils\n";
    }
}
