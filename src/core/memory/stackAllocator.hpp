#ifndef STACK_ALLOCATOR_HPP
#define STACK_ALLOCATOR_HPP

#include "allocator.hpp"


namespace Core
{
    class StackAllocator
    {
    public:
        StackAllocator(size_t size, void* pointer);
        ~StackAllocator();

        StackAllocator(const StackAllocator&) = delete;
        StackAllocator(StackAllocator&&) = delete;

        StackAllocator& operator=(const StackAllocator&) = delete;
        StackAllocator& operator=(StackAllocator&&) = delete;

        void* allocate(size_t size, u8 alignment);
        void deallocate(void* pointer);

        void clear();

        const MemoryInfo* getMemoryInfo() const;

    private:
        MemoryInfo m_memInfo;
        void*      m_currentPtr;

        #ifndef NDEBUG
        void* m_prevPtr;
        #endif

        struct AllocationHeader
        {
            u8 adjustment;

            #ifndef NDEBUG
            void* prevPtr;
            #endif
        };
    };
}

#endif
