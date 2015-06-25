#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include "../types.hpp"


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
        MemoryInfo(size_t size, void* pointer);
        ~MemoryInfo();

        void*  m_pointer;
        size_t m_size;

        size_t m_usedMemory;
        size_t m_numAllocations;
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
        void dealloc(ObjType* obj, Args&&... args)
        {
            obj->~ObjType();
            m_allocator.deallocate(obj);
        }

        const MemoryInfo* getMemoryInfo() const
        {
            m_allocator.getMemoryInfo();
        }

    private:
        AllocatorClass m_allocator;
    };
}

#endif
/*

    template<class T> T* allocateArray(Allocator& allocator, size_t length)
    {
        ASSERT(length != 0);

        u8 headerSize = sizeof(size_t)/sizeof(T);

        if(sizeof(size_t)%sizeof(T) > 0)
            headerSize += 1;

        //Allocate extra space to store array length in the bytes before the array
        T* p = ( (T*) allocator.allocate(sizeof(T)*(length + headerSize), __alignof(T)) ) + headerSize;

        *( ((size_t*)p) - 1 ) = length;

        for(size_t i = 0; i < length; i++)
            new (&p[i]) T;

        return p;
    }

    template<class T> void deallocateArray(Allocator& allocator, T* array)
    {
        ASSERT(array != nullptr);

        size_t length = *( ((size_t*)array) - 1 );

        for(size_t i = 0; i < length; i++)
            array[i].~T();

        //Calculate how much extra memory was allocated to store the length before the array
        u8 headerSize = sizeof(size_t)/sizeof(T);

        if(sizeof(size_t)%sizeof(T) > 0)
            headerSize += 1;

        allocator.deallocate(array - headerSize);
*/
