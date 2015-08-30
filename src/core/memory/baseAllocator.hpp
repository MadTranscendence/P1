#ifndef BASEALLOCATOR_HPP
#define BASEALLOCATOR_HPP

#include "utils.hpp"


namespace Core
{
    class BaseAllocator
    {
    public:
        BaseAllocator();
        ~BaseAllocator();

        BaseAllocator(const BaseAllocator&) = delete;
        BaseAllocator(BaseAllocator&& baseAllocator);

        BaseAllocator& operator=(const BaseAllocator&) = delete;
        BaseAllocator& operator=(BaseAllocator&& baseAllocator);

        void* allocate(size_t size, u8);
        void  deallocate(void* pointer);

        void clear();

        const MemoryInfo* getMemoryInfo() const;

    private:
        MemoryInfo m_memInfo;
    };
}

#endif
