#include "../../common.hpp"
#include "linearAllocator.hpp"

#include <cassert>


namespace Core
{
    LinearAllocator::LinearAllocator(size_t size, void* pointer)
    {
        assert(pointer != nullptr);
        assert(size > 0);

        m_memInfo.pointer        = pointer;
        m_memInfo.size           = size;
        m_memInfo.usedMemory     = 0;
        m_memInfo.numAllocations = 0;
        m_currentPtr = pointer;
    }

    LinearAllocator::~LinearAllocator()
    {
        assert(m_memInfo.usedMemory == 0);
    }

    LinearAllocator::LinearAllocator(LinearAllocator&& linearAllocator)
    {
        m_memInfo = std::move(linearAllocator.m_memInfo);
        m_currentPtr = linearAllocator.m_currentPtr;
    }

    LinearAllocator& LinearAllocator::operator=(LinearAllocator&& linearAllocator)
    {
        m_memInfo = std::move(linearAllocator.m_memInfo);
        m_currentPtr = linearAllocator.m_currentPtr;

        return *this;
    }

    void* LinearAllocator::allocate(size_t size, u8 alignment)
    {
        u8 adjustment = PointerMath::alignForwardAdjustment(m_currentPtr, alignment);

        if(m_memInfo.usedMemory + adjustment + size > m_memInfo.size)
            return nullptr;

        void* alignedPtr = PointerMath::add(m_currentPtr, adjustment);
        m_currentPtr = PointerMath::add(alignedPtr, size);

        m_memInfo.usedMemory += size + adjustment;
        m_memInfo.numAllocations++;

        return alignedPtr;
    }

    void LinearAllocator::deallocate(void*)
    {
        assert(false && "Linear allocator does not implement deallocate(). Use clear() instead.");
    }

    void LinearAllocator::clear()
    {
        m_memInfo.usedMemory     = 0;
        m_memInfo.numAllocations = 0;
        m_currentPtr = m_memInfo.pointer;
    }

    const MemoryInfo* LinearAllocator::getMemoryInfo() const
    {
        return &m_memInfo;
    }
}
