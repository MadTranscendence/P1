#include "test/catch.hpp"
#include "src/core/memory/standardAllocator.hpp"

#include <vector>

using namespace Core;


TEST_CASE("Test Standard Allocator", "[core][memory][standardAllocator]")
{
    Allocator<BaseAllocator> baseAllocator;
    Allocator<FreeListAllocator> freeListAllocator(MBytesToBytes(512), &baseAllocator);

    std::vector<int, FreeListStandardAllocator<int>> vec =
        std::vector<int, FreeListStandardAllocator<int>>
        (FreeListStandardAllocator<int>(&freeListAllocator));

    vec.resize(0);
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    CHECK(vec[0] == 1);
    CHECK(vec[1] == 2);
    CHECK(vec[2] == 3);
    CHECK(vec[3] == 4);

    vec.erase(vec.begin() + 1);

    CHECK(vec[0] == 1);
    CHECK(vec[1] == 3);
    CHECK(vec[2] == 4);

    Allocator<FreeListAllocator> freeListAllocatorB(MBytesToBytes(512), &baseAllocator);

    FreeListStandardAllocator<int>    intAllocatorA(&freeListAllocator);
    FreeListStandardAllocator<int>    intAllocatorB(&freeListAllocatorB);
    FreeListStandardAllocator<double> doubleAllocator(&freeListAllocator);

    CHECK(  intAllocatorA  == intAllocatorA);
    CHECK(!(intAllocatorA  != intAllocatorA));

    CHECK(  intAllocatorA  != intAllocatorB);
    CHECK(!(intAllocatorA  == intAllocatorB));

    CHECK(  intAllocatorA  == doubleAllocator);
    CHECK(!(intAllocatorA  != doubleAllocator));

    CHECK(  intAllocatorB  != doubleAllocator);
    CHECK(!(intAllocatorB  == doubleAllocator));
}
