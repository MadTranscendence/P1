#include "../../common.hpp"
#include "utils.hpp"


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

    size_t KBytesToBytes(size_t kiloBytes)
    {
        return kiloBytes * (1 << 10);
    }

    size_t MBytesToBytes(size_t megaBytes)
    {
        return megaBytes * (1 << 20);
    }

    size_t GBytesToBytes(size_t gigaBytes)
    {
        return gigaBytes * (1 << 30);
    }
}
