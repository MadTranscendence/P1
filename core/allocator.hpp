#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include "types.hpp"


namespace Core
{
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

    class Allocator
    {
    public:
        Allocator(size_t size, void* start);
        virtual ~Allocator();

        virtual void* allocate(size_t size, u8 alignment = 4) = 0;
        virtual void  deallocate(void* ptr) = 0;

        void*  getStart() const;
        size_t getSize() const;
        size_t getUsedMemory() const;
        size_t getNumAllocations() const;

    protected:
        void*  m_start;
        size_t m_size;

        size_t m_usedMemory;
        size_t m_numAllocations;
    };
}

#endif
