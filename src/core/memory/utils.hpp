#ifndef UTILS_HPP
#define UTILS_HPP

#include "../types.hpp"


namespace Core
{
    struct MemoryInfo
    {
        void*  pointer;
        size_t size;

        size_t usedMemory;
        size_t numAllocations;
    };

    namespace PointerMath
    {
        void*       alignForward(void* address, u8 alignment);
        const void* alignForward(const void* address, u8 alignment);
        void*       alignBackward(void* address, u8 alignment);
        const void* alignBackward(const void* address, u8 alignment);

        u8          alignForwardAdjustment(const void* address, u8 alignment);
        u8          alignForwardAdjustmentHeader(const void* address, u8 alignment, u8 headerSize);

        u8          alignBackwardAdjustment(const void* address, u8 alignment);

        void*       add(void* ptr, size_t sz);
        const void* add(const void* ptr, size_t sz);

        void*       sub(void* ptr, size_t sz);
        const void* sub(const void* ptr, size_t sz);
    }
}

#endif
