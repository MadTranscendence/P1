#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include "../types.hpp"
#include "baseAllocator.hpp"
#include "freeListAllocator.hpp"
#include "linearAllocator.hpp"
#include "stackAllocator.hpp"

#include <cassert>
#include <vector>


namespace Core
{
    template<class AllocatorClass, class SourceClass = BaseAllocator>
    class Allocator
    {
    public:
        Allocator()
        {
            assert(false && "Allocator of type other than BaseAllocator takes block size and source as parameters.");
        }

        Allocator(size_t size, Allocator<SourceClass>* source)
            : m_size(size), m_source(source) {}

        ~Allocator()
        {
            for(AllocatorClass& allocator : m_allocators)
                m_source->deallocPlain(allocator.getMemoryInfo()->pointer);
        }

        template<class ObjType, class... Args>
        ObjType* alloc(Args&&... args)
        {
            return new (allocPlain(sizeof(ObjType), alignof(ObjType))) ObjType(std::forward<Args>(args)...);
        }

        template<class ObjType, class... Args>
        ObjType* allocArray(size_t n, Args&&... args)
        {
            assert(n > 0);

            size_t headerSize = sizeof(size_t) / sizeof(ObjType) + ((sizeof(size_t) % sizeof(ObjType)) != 0);
            size_t arraySize = sizeof(ObjType)*(n + headerSize);

            ObjType* pointer = headerSize + (ObjType*)(allocPlain(arraySize, alignof(ObjType)));
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
            deallocPlain(pointer);
        }

        template<class ObjType>
        void deallocArray(ObjType* pointer)
        {
            assert(pointer != nullptr);

            size_t n = *((size_t*)pointer - 1);

            for(size_t i = 0; i < n; ++i)
                pointer[n-i-1].~ObjType();

            size_t headerSize = sizeof(size_t) / sizeof(ObjType) + ((sizeof(size_t) % sizeof(ObjType)) != 0);
            deallocPlain(pointer - headerSize);
        }

        void clear()
        {
            for(AllocatorClass& allocator : m_allocators)
                allocator.clear();
        }

        void* allocPlain(size_t size, u8 alignment)
        {
            for(AllocatorClass& allocator : m_allocators)
            {
                void* pointer = allocator.allocate(size, alignment);
                if(pointer != nullptr)
                    return pointer;
            }

            m_allocators.emplace_back(m_size, m_source->allocPlain(m_size, alignof(char)));
            return m_allocators.back().allocate(size, alignment);
        }

        void deallocPlain(void* pointer)
        {
            for(AllocatorClass& allocator : m_allocators)
            {
                const MemoryInfo* memInfo = allocator.getMemoryInfo();
                void* pointerMin = (char*)memInfo->pointer;
                void* pointerMax = (char*)memInfo->pointer + memInfo->size;

                if(pointer >= pointerMin && pointer < pointerMax)
                {
                    allocator.deallocate(pointer);
                    return;
                }
            }
        }

        AllocatorClass* getInternalAllocator(uint i)
        {
            return &m_allocators[i];
        }

        const MemoryInfo* getMemoryInfo(uint i) const
        {
            return m_allocators[i].getMemoryInfo();
        }

        uint getNumAllocators()
        {
            return m_allocators.size();
        }

        size_t getBlockSize()
        {
            return m_size;
        }

    private:
        std::vector<AllocatorClass> m_allocators;
        size_t                      m_size;
        Allocator<SourceClass>*     m_source;
    };

    template<>
    Allocator<BaseAllocator, BaseAllocator>::Allocator();

    template<>
    Allocator<BaseAllocator, BaseAllocator>::Allocator(size_t, Allocator<BaseAllocator>*);

    template<>
    Allocator<BaseAllocator, BaseAllocator>::~Allocator();

    template<>
    void* Allocator<BaseAllocator, BaseAllocator>::allocPlain(size_t size, u8 alignment);

    template<>
    void Allocator<BaseAllocator, BaseAllocator>::deallocPlain(void* pointer);
}

#endif
