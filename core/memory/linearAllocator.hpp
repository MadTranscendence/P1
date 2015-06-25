#ifndef LINEAR_ALLOCATOR_HPP
#define LINEAR_ALLOCATOR_HPP

#include "allocator.hpp"


namespace Core
{
    class LinearAllocator
    {
    public:
        LinearAllocator(size_t size, void* pointer);
        ~LinearAllocator();

        LinearAllocator(const LinearAllocator&) = delete;
        LinearAllocator(LinearAllocator&&) = delete;

        LinearAllocator& operator=(const LinearAllocator&) = delete;
        LinearAllocator& operator=(LinearAllocator&&) = delete;

        void* allocate(size_t size, u8 alignment);
        void deallocate(void* p);

        void clear();

        const MemoryInfo* getMemoryInfo() const;

    private:
        MemoryInfo m_memInfo;
        void*      m_currentPtr;
    };
}

#endif
