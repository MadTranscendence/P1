#ifndef FREE_LIST_ALLOCATOR_HPP
#define FREE_LIST_ALLOCATOR_HPP

#include "utils.hpp"


namespace Core
{
    class FreeListAllocator
    {
    public:
        FreeListAllocator(size_t size, void* pointer);
        ~FreeListAllocator();

        FreeListAllocator(const FreeListAllocator&) = delete;
        FreeListAllocator(FreeListAllocator&& freeListAllocator);

        FreeListAllocator& operator=(const FreeListAllocator&) = delete;
        FreeListAllocator& operator=(FreeListAllocator&& freeListAllocator);

        void* allocate(size_t size, u8 alignment);
        void  deallocate(void* pointer);

        void clear();

        const MemoryInfo* getMemoryInfo() const;

    private:
        struct FreeBlock
        {
            size_t     size;
            FreeBlock* next;
        };

        struct AllocationHeader
        {
            size_t size;
            u8     adjustment;
        };

        MemoryInfo m_memInfo;
        FreeBlock* m_freeBlocks;
    };
}

#endif
