#include "test/catch.hpp"
#include "src/core/memory/freeListAllocator.hpp"
#include "src/core/types.hpp"

using namespace Core;


TEST_CASE("Test Free List Allocator", "[core][memory][freeListAllocator]")
{
    std::vector<int> vector;






    u8 alignment = 64;
    INFO("alignment := " << (uint)alignment);

    size_t allocSize = 4096;
    FreeListAllocator freeListAllocator(allocSize, malloc(allocSize));

    CHECK_NOTHROW(freeListAllocator.deallocate(nullptr));

    CAPTURE(freeListAllocator.getMemoryInfo()->pointer);

    const size_t allocCount = 4;
    size_t allocSizes[allocCount] = {32, 128, 512, 1024};
    void*  allocPointers[allocCount];

    SECTION("Allocate and deallocate memory")
    {
        for(uint i = 0; i < allocCount; ++i)
        {
            CAPTURE(i);

            allocPointers[i] = freeListAllocator.allocate(allocSizes[i], alignment);
            CAPTURE(allocPointers[i]);

            CHECK(freeListAllocator.getMemoryInfo()->numAllocations == i+1);
            CHECK(allocPointers[i] != nullptr);
            CHECK(((uptr)allocPointers[i] % alignment) == 0);
        }

        for(int i = allocCount-1; i >= 0; --i)
        {
            CAPTURE(i);
            CAPTURE(allocPointers[i]);

            freeListAllocator.deallocate(allocPointers[i]);
            CHECK(freeListAllocator.getMemoryInfo()->numAllocations == i);
        }

        CHECK(freeListAllocator.getMemoryInfo()->numAllocations == 0);
        CHECK(freeListAllocator.getMemoryInfo()->usedMemory == 0);
    }

    SECTION("Allocate and clear memory")
    {
        for(uint i = 0; i < allocCount; ++i)
        {
            CAPTURE(i);

            allocPointers[i] = freeListAllocator.allocate(allocSizes[i], alignment);
            CAPTURE(allocPointers[i]);

            CHECK(freeListAllocator.getMemoryInfo()->numAllocations == i+1);
            CHECK(allocPointers[i] != nullptr);
            CHECK(((uptr)allocPointers[i] % alignment) == 0);
        }

        freeListAllocator.clear();
        CHECK(freeListAllocator.getMemoryInfo()->numAllocations == 0);
        CHECK(freeListAllocator.getMemoryInfo()->usedMemory == 0);
    }

    free(freeListAllocator.getMemoryInfo()->pointer);
}
