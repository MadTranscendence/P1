#include "../../common.hpp"
#include "allocator.hpp"


namespace Core
{
    template<>
    Allocator<BaseAllocator, BaseAllocator>::Allocator() : m_size(0), m_source(nullptr) {}

    template<>
    Allocator<BaseAllocator, BaseAllocator>::Allocator(size_t, Allocator<BaseAllocator>*) {}

    template<>
    Allocator<BaseAllocator, BaseAllocator>::~Allocator() {}

    template<>
    void* Allocator<BaseAllocator, BaseAllocator>::allocPlain(size_t size, u8 alignment)
    {
        if(m_allocators.empty())
            m_allocators.emplace_back();

        return m_allocators.back().allocate(size, alignment);
    }

    template<>
    void Allocator<BaseAllocator, BaseAllocator>::deallocPlain(void* pointer)
    {
        if(m_allocators.empty())
            assert(false && "Attempted to deallocate pointer without valid BaseAllocator");

        return m_allocators.back().deallocate(pointer);
    }
}
