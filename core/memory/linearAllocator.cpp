#include "common.hpp"
#include "linearAllocator.hpp"


namespace Core
{
    LinearAllocator::LinearAllocator(size_t size, void* pointer) : m_memInfo(size, pointer)
    {

    }

    LinearAllocator::~LinearAllocator()
    {

    }

    void* LinearAllocator::allocate(size_t size, u8 alignment)
    {
        return m_memInfo.m_pointer;
    }

    void LinearAllocator::deallocate(void* p)
    {

    }

    void LinearAllocator::clear()
    {
    }

    const MemoryInfo* LinearAllocator::getMemoryInfo() const
    {
        return &m_memInfo;
    }
}
