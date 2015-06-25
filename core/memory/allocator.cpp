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

    MemoryInfo::MemoryInfo(size_t size, void* pointer)
    {
        m_pointer        = pointer;
        m_size           = size;

        m_usedMemory     = 0;
        m_numAllocations = 0;
    }

    MemoryInfo::~MemoryInfo() {}
}
