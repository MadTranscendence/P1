#include "../common.hpp"
#include "core.hpp"

#include <xmmintrin.h>
#include <pmmintrin.h>


namespace Core
{
    Core::Core() : m_baseAllocator(0, nullptr)
    {
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        _MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);

        std::cout << "Created Core utils\n";
    }

    Core::~Core()
    {
        std::cout << "Destructed Core utils\n";
    }
}
