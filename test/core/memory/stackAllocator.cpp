#include "test/catch.hpp"
#include "src/core/memory/stackAllocator.hpp"
#include "src/core/types.hpp"

using namespace Core;


TEST_CASE("Test Stack Allocator", "[core][memory][stackAllocator]")
{
    u8 alignment = 64;
    INFO("alignment := " << (uint)alignment);

    size_t allocSize = 4096;
    StackAllocator stackAllocator(allocSize, malloc(allocSize));

    CHECK_NOTHROW(stackAllocator.deallocate(nullptr));

    CAPTURE(stackAllocator.getMemoryInfo()->pointer);

    const size_t allocCount = 4;
    size_t allocSizes[allocCount] = {32, 128, 512, 1024};
    void*  allocPointers[allocCount];

    SECTION("Allocate and deallocate memory")
    {
        for(uint i = 0; i < allocCount; ++i)
        {
            CAPTURE(i);

            allocPointers[i] = stackAllocator.allocate(allocSizes[i], alignment);
            CAPTURE(allocPointers[i]);

            CHECK(stackAllocator.getMemoryInfo()->numAllocations == i+1);
            CHECK(allocPointers[i] != nullptr);
            CHECK(((uptr)allocPointers[i] % alignment) == 0);
        }

        for(int i = allocCount-1; i >= 0; --i)
        {
            CAPTURE(i);
            CAPTURE(allocPointers[i]);

            stackAllocator.deallocate(allocPointers[i]);
            CHECK(stackAllocator.getMemoryInfo()->numAllocations == i);
        }

        CHECK(stackAllocator.getMemoryInfo()->numAllocations == 0);
        CHECK(stackAllocator.getMemoryInfo()->usedMemory == 0);
    }

    SECTION("Allocate and clear memory")
    {
        for(uint i = 0; i < allocCount; ++i)
        {
            CAPTURE(i);

            allocPointers[i] = stackAllocator.allocate(allocSizes[i], alignment);
            CAPTURE(allocPointers[i]);

            CHECK(stackAllocator.getMemoryInfo()->numAllocations == i+1);
            CHECK(allocPointers[i] != nullptr);
            CHECK(((uptr)allocPointers[i] % alignment) == 0);
        }

        stackAllocator.clear();
        CHECK(stackAllocator.getMemoryInfo()->numAllocations == 0);
        CHECK(stackAllocator.getMemoryInfo()->usedMemory == 0);
    }

    free(stackAllocator.getMemoryInfo()->pointer);
}
