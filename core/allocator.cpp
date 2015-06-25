#include "common.hpp"
#include "allocator.hpp"

#include <cassert>


namespace Core
{
    namespace PointerMath
    {
        void* alignForward(void* address, u8 alignment)
        {
            return (void*)((uptr(address) + uptr(alignment-1)) & uptr(~(alignment-1)));
        }

        const void* alignForward(const void* address, u8 alignment)
        {
            return (const void*)((uptr(address) + uptr(alignment-1)) & uptr(~(alignment-1)));
        }

        void* alignBackward(void* address, u8 alignment)
        {
            return (void*)(uptr(address) & uptr(~(alignment-1)));
        }

        const void* alignBackward(const void* address, u8 alignment)
        {
            return (const void*)(uptr(address) & uptr(~(alignment-1)));
        }

        u8 alignForwardAdjustment(const void* address, u8 alignment)
        {
            u8 adjustment = alignment - (uptr(address) & uptr(alignment-1));

            if(adjustment == alignment)
                return 0;

            return adjustment;
        }

        u8 alignForwardAdjustmentHeader(const void* address, u8 alignment, u8 headerSize)
        {
            return headerSize + alignForwardAdjustment(add(address, headerSize), alignment);
        }

        u8 alignBackwardAdjustment(const void* address, u8 alignment)
        {
            u8 adjustment = (uptr(address) & uptr(alignment-1));

            if(adjustment == alignment)
                return 0;

            return adjustment;
        }

        void* add(void* ptr, size_t sz)
        {
            return (void*)(uptr(ptr) + sz);
        }

        const void* add(const void* ptr, size_t sz)
        {
            return (const void*)(uptr(ptr) + sz);
        }

        void* sub(void* ptr, size_t sz)
        {
            return (void*)(uptr(ptr) - sz);
        }

        const void* sub(const void* ptr, size_t sz)
        {
            return (const void*)(uptr(ptr) - sz);
        }
    }

    Allocator::Allocator(size_t size, void* start)
    {
        m_start          = start;
        m_size           = size;

        m_usedMemory     = 0;
        m_numAllocations = 0;
    }

    Allocator::~Allocator()
    {
        assert(m_numAllocations == 0 && m_usedMemory == 0);

        m_start = nullptr;
        m_size  = 0;
    }

    void* Allocator::getStart() const
    {
        return m_start;
    }

    size_t Allocator::getSize() const
    {
        return m_size;
    }

    size_t Allocator::getUsedMemory() const
    {
        return m_usedMemory;
    }

    size_t Allocator::getNumAllocations() const
    {
        return m_numAllocations;
    }
}
