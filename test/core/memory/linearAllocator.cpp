#include "test/catch.hpp"
#include "src/core/memory/linearAllocator.hpp"
#include "src/core/types.hpp"

using namespace Core;


TEST_CASE("Test Linear Allocator", "[core][memory][linearAllocator]")
{
    u8 alignment = 64;
    INFO("alignment := " << (uint)alignment);

    size_t allocSize = 4096;
    LinearAllocator linearAllocator(allocSize, malloc(allocSize));

    CAPTURE(linearAllocator.getMemoryInfo()->pointer);

    const size_t allocCount = 4;
    size_t allocSizes[allocCount] = {32, 128, 512, 1024};
    void*  allocPointers[allocCount];

    SECTION("Allocate and clear memory")
    {
        for(uint i = 0; i < allocCount; ++i)
        {
            CAPTURE(i);

            allocPointers[i] = linearAllocator.allocate(allocSizes[i], alignment);
            CAPTURE(allocPointers[i]);

            CHECK(linearAllocator.getMemoryInfo()->numAllocations == i+1);
            CHECK(allocPointers[i] != nullptr);
            CHECK(((uptr)allocPointers[i] % alignment) == 0);
        }

        linearAllocator.clear();
        CHECK(linearAllocator.getMemoryInfo()->numAllocations == 0);
        CHECK(linearAllocator.getMemoryInfo()->usedMemory == 0);
    }

    free(linearAllocator.getMemoryInfo()->pointer);
}
