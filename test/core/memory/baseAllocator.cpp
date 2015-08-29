#include "test/catch.hpp"
#include "src/core/memory/baseAllocator.hpp"
#include "src/core/types.hpp"

using namespace Core;


TEST_CASE("Test Base Allocator", "[core][memory][baseAllocator]")
{
    u8 alignment = 64;
    INFO("alignment := " << (uint)alignment);

    BaseAllocator baseAllocator;

    CHECK_NOTHROW(baseAllocator.deallocate(nullptr));

    const size_t allocCount = 4;
    size_t allocSizes[allocCount] = {32, 128, 512, 1024};
    void*  allocPointers[allocCount];

    SECTION("Allocate and deallocate memory")
    {
        for(uint i = 0; i < allocCount; ++i)
        {
            CAPTURE(i);

            allocPointers[i] = baseAllocator.allocate(allocSizes[i], alignment);
            CAPTURE(allocPointers[i]);

            CHECK(baseAllocator.getMemoryInfo()->numAllocations == i+1);
            CHECK(allocPointers[i] != nullptr);
        }

        for(uint i = 0; i < allocCount; ++i)
        {
            CAPTURE(i);
            CAPTURE(allocPointers[i]);

            baseAllocator.deallocate(allocPointers[i]);
            CHECK(baseAllocator.getMemoryInfo()->numAllocations == allocCount-i-1);
        }
    }
}
