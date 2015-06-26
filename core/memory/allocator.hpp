#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include "../types.hpp"

#include <cassert>


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

    struct MemoryInfo
    {
        void*  pointer;
        size_t size;

        size_t usedMemory;
        size_t numAllocations;
    };

    template<class AllocatorClass>
    class Allocator
    {
    public:
        Allocator(size_t size, void* pointer) : m_allocator(size, pointer) {}
        ~Allocator() = default;
        
        template<class ObjType, class... Args>
        ObjType* alloc(Args&&... args)
        {
            return new (m_allocator.allocate(sizeof(ObjType), alignof(ObjType))) ObjType(std::forward<Args>(args)...);
        }

        template<class ObjType, class... Args>
        ObjType* allocArray(size_t n, Args&&... args)
        {
            assert(n > 0);

            size_t headerSize = sizeof(size_t) / sizeof(ObjType) + ((sizeof(size_t) % sizeof(ObjType)) != 0);
            size_t arraySize = sizeof(ObjType)*(n + headerSize);

            ObjType* pointer = headerSize + (ObjType*)(m_allocator.allocate(arraySize, alignof(ObjType)));
            *((size_t*)pointer - 1) = n;

            for(size_t i = 0; i < n; ++i)
                new (pointer + i) ObjType(std::forward<Args>(args)...);

            return pointer;
        }

        template<class ObjType>
        void dealloc(ObjType* pointer)
        {
            assert(pointer != nullptr);

            pointer->~ObjType();
            m_allocator.deallocate(pointer);
        }

        template<class ObjType>
        void deallocArray(ObjType* pointer)
        {
            assert(pointer != nullptr);

            size_t n = *((size_t*)pointer - 1);

            for(size_t i = 0; i < n; ++i)
                pointer[i].~ObjType();

            size_t headerSize = sizeof(size_t) / sizeof(ObjType) + ((sizeof(size_t) % sizeof(ObjType)) != 0);
            m_allocator.deallocate(pointer - headerSize);
        }

        void clear()
        {
            m_allocator.clear();
        }

        const MemoryInfo* getMemoryInfo() const
        {
            return m_allocator.getMemoryInfo();
        }

    private:
        AllocatorClass m_allocator;
    };
}

#endif
