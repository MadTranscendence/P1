#include "../../common.hpp"
#include "baseAllocator.hpp"

#include <cassert>


namespace Core
{
    BaseAllocator::BaseAllocator()
    {
        m_memInfo.pointer        = nullptr;
        m_memInfo.size           = 0;
        m_memInfo.usedMemory     = 0;
        m_memInfo.numAllocations = 0;
    }

    BaseAllocator::~BaseAllocator()
    {
        assert(m_memInfo.numAllocations == 0);
    }

    BaseAllocator::BaseAllocator(BaseAllocator&& baseAllocator)
    {
        m_memInfo = std::move(baseAllocator.m_memInfo);
    }

    BaseAllocator& BaseAllocator::operator=(BaseAllocator&& baseAllocator)
    {
        m_memInfo = std::move(baseAllocator.m_memInfo);

        return *this;
    }

    void* BaseAllocator::allocate(size_t size, u8 alignment)
    {
        m_memInfo.numAllocations++;
        return aligned_alloc(alignment, size);
    }

    void BaseAllocator::deallocate(void* pointer)
    {
        if(pointer)
        {
            m_memInfo.numAllocations--;
            free(pointer);
        }
    }

    void BaseAllocator::clear()
    {
        assert(false && "Base allocator does not implement clear(). Use deallocate() instead.");
    }

    const MemoryInfo* BaseAllocator::getMemoryInfo() const
    {
        return &m_memInfo;
    }
}
