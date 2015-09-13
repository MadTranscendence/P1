#ifndef STANDARD_ALLOCATOR_HPP
#define STANDARD_ALLOCATOR_HPP

#include "../types.hpp"
#include "allocator.hpp"

#include <memory>


namespace Core
{
    template<class T, class SourceClass>
    class StandardAllocator
    {
    public:
        typedef T                 value_type;
        typedef value_type*       pointer;
        typedef const value_type* const_pointer;
        typedef value_type&       reference;
        typedef const value_type& const_reference;
        typedef std::size_t       size_type;
        typedef std::ptrdiff_t    difference_type;

        template<class U>
        struct rebind
        {
            typedef StandardAllocator<U, SourceClass> other;
        };

    public:
        StandardAllocator(Allocator<SourceClass>* source) : m_source(source) {}
        ~StandardAllocator() = default;

        template<class U>
        StandardAllocator(const StandardAllocator<U, SourceClass>& allocator)
            : m_source(allocator.getSourceAllocator()) {}

        pointer address(reference ref)
        {
            return std::addressof(ref);
        }

        const_pointer address(const_reference ref)
        {
            return std::addressof(ref);
        }

        pointer allocate(size_type n)
        {
            return (pointer)m_source->allocPlain(n * sizeof(T), alignof(T));
        }

        void deallocate(pointer ptr, size_type)
        {
            m_source->deallocPlain(ptr);
        }

        size_type max_size() const
        {
            return m_source->getBlockSize() / sizeof(T);
        }

        void construct(pointer ptr, const T& t)
        {
            new (ptr) T(t);
        }

        void destroy(pointer ptr)
        {
            ptr->~T();
        }

        Allocator<SourceClass>* getSourceAllocator()
        {
            return m_source;
        }

        const Allocator<SourceClass>* getSourceAllocator() const
        {
            return (const Allocator<SourceClass>*)m_source;
        }

    private:
        Allocator<SourceClass>* m_source;
    };

    template<class T, class U, class Source>
    constexpr bool operator==(const StandardAllocator<T, Source>& t,
                              const StandardAllocator<U, Source>& u)
    {
        return t.getSourceAllocator() == u.getSourceAllocator();
    }

    template<class T, class U, class Source>
    constexpr bool operator!=(const StandardAllocator<T, Source>& t,
                              const StandardAllocator<U, Source>& u)
    {
        return t.getSourceAllocator() != u.getSourceAllocator();
    }

    template<class T, class U, class TSource, class USource>
    constexpr bool operator==(const StandardAllocator<T, TSource>&,
                              const StandardAllocator<U, USource>&)
    {
        return false;
    }

    template<class T, class U, class TSource, class USource>
    constexpr bool operator!=(const StandardAllocator<T, TSource>&,
                              const StandardAllocator<U, USource>&)
    {
        return true;
    }

    template<class T>
    using BaseStandardAllocator = StandardAllocator<T, BaseAllocator>;

    template<class T>
    using FreeListStandardAllocator = StandardAllocator<T, FreeListAllocator>;

    template<class T>
    using StackStandardAllocator = StandardAllocator<T, StackAllocator>;
}

#endif
