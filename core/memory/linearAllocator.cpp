#include "common.hpp"
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

    void* LinearAllocator::allocate(size_t size, u8 alignment)
    {
        u8 adjustment = PointerMath::alignForwardAdjustment(m_currentPtr, alignment);

        if(m_memInfo.usedMemory + adjustment + size > m_memInfo.size)
            return nullptr;

        uptr alignedPtr = uptr(m_currentPtr) + adjustment;
        m_currentPtr = (void*)(alignedPtr + size);

        m_memInfo.usedMemory += size + adjustment;
        m_memInfo.numAllocations++;

        return (void*)alignedPtr;
    }

    void LinearAllocator::deallocate(void*)
    {
        assert(0 && "Linear allocator does not implement deallocate. Use clear instead");
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
