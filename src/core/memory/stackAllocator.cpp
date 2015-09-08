#include "../../common.hpp"
#include "stackAllocator.hpp"

#include <cassert>


namespace Core
{
    StackAllocator::StackAllocator(size_t size, void* pointer)
    {
        assert(pointer != nullptr);
        assert(size > 0);

        m_memInfo.pointer = pointer;
        m_memInfo.size    = size;
        m_currentPtr      = pointer;

        #ifndef NDEBUG
        m_prevPtr = nullptr;
        #endif
    }

    StackAllocator::~StackAllocator()
    {
        assert(m_memInfo.usedMemory == 0);
    }

    StackAllocator::StackAllocator(StackAllocator&& stackAllocator)
    {
        m_memInfo    = std::move(stackAllocator.m_memInfo);
        m_currentPtr = stackAllocator.m_currentPtr;

        #ifndef NDEBUG
        m_prevPtr = stackAllocator.m_prevPtr;
        #endif
    }

    StackAllocator& StackAllocator::operator=(StackAllocator&& stackAllocator)
    {
        m_memInfo    = std::move(stackAllocator.m_memInfo);
        m_currentPtr = stackAllocator.m_currentPtr;

        #ifndef NDEBUG
        m_prevPtr = stackAllocator.m_prevPtr;
        #endif

        return *this;
    }

    void* StackAllocator::allocate(size_t size, u8 alignment)
    {
        u8 adjustment = PointerMath::alignForwardAdjustmentHeader(m_currentPtr, alignment, sizeof(AllocationHeader));

        if(m_memInfo.usedMemory + adjustment + size > m_memInfo.size)
            return nullptr;

        void* alignedPtr = PointerMath::add(m_currentPtr, adjustment);
        m_currentPtr = PointerMath::add(alignedPtr, size);

        AllocationHeader* header = (AllocationHeader*)PointerMath::sub(alignedPtr, sizeof(AllocationHeader));
        header->adjustment = adjustment;

        #ifndef NDEBUG
        header->prevPtr = m_prevPtr;
        m_prevPtr       = alignedPtr;
        #endif

        m_memInfo.usedMemory += size + adjustment;
        m_memInfo.numAllocations++;

        return alignedPtr;
    }

    void StackAllocator::deallocate(void* pointer)
    {
        if(pointer)
        {
            AllocationHeader* header = (AllocationHeader*)PointerMath::sub(pointer, sizeof(AllocationHeader));

            #ifndef NDEBUG
            assert(m_prevPtr == pointer && "Stack allocator performs deallocation only in reverse order of allocation.");
            m_prevPtr = header->prevPtr;
            #endif

            m_memInfo.usedMemory -= (uptr)m_currentPtr;
            m_memInfo.usedMemory += (uptr)pointer;
            m_memInfo.usedMemory -= header->adjustment;

            m_memInfo.numAllocations--;

            m_currentPtr = PointerMath::sub(pointer, header->adjustment);
        }
    }

    void StackAllocator::clear()
    {
        m_memInfo.usedMemory     = 0;
        m_memInfo.numAllocations = 0;
        m_currentPtr             = m_memInfo.pointer;
    }

    const MemoryInfo* StackAllocator::getMemoryInfo() const
    {
        return &m_memInfo;
    }
}
