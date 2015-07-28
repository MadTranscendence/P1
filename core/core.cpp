#include "common.hpp"
#include "core.hpp"

#include <xmmintrin.h>
#include <pmmintrin.h>


namespace Core
{
    struct A
    {
        A(int i) {std::cout << "Created A\n";}
        ~A() {std::cout << "Destructed A\n";}

        int a;
        int b;
    };

    struct B
    {
        B(int i) {std::cout << "Created B\n";}
        ~B() {std::cout << "Destructed B\n";}

        int a;
        int b;
    };

    Core::Core() : m_allocator(sizeof(A)*1000, malloc(sizeof(A)*1000))
    {
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);

        std::cout << "Created Core utils\n";

        A* a = m_allocator.allocArray<A>(3, 5);
        B* b = m_allocator.allocArray<B>(2, 5);

        m_allocator.deallocArray(b);
        m_allocator.deallocArray(a);

        free(m_allocator.getMemoryInfo()->pointer);
    }

    Core::~Core()
    {
        std::cout << "Destructed Core utils\n";
    }
}
