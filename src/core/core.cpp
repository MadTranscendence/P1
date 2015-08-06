#include "common.hpp"
#include "core.hpp"

#include <xmmintrin.h>
#include <pmmintrin.h>


namespace Core
{
    Core::Core() : m_stackAllocator(200*1024*1024, malloc(200*1024*1024))
    {
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);

        std::cout << "Created Core utils\n";

        free(m_stackAllocator.getMemoryInfo()->pointer);
    }

    Core::~Core()
    {
        std::cout << "Destructed Core utils\n";
    }
}
