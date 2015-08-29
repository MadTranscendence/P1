#include "test/catch.hpp"
#include "src/core/memory/allocator.hpp"
#include "src/core/memory/utils.hpp"
#include "src/core/timer.hpp"
#include "src/core/types.hpp"

#include <iostream>
#include <string>

using namespace Core;


std::string sizeToReadable(size_t size)
{
    std::string units[] = {"B", "KB", "MB", "GB", "TB"};
    uint i = 0;
    while(size >= 1024)
    {
        size /= 1024;
        ++i;
    }
    return std::to_string(size) + units[i];
}

TEST_CASE("Test Allocator", "[core][memory][allocator]")
{
    Allocator<BaseAllocator>   baseAllocator;
    Allocator<LinearAllocator> linearAllocator(MBytesToBytes(512), &baseAllocator);
    Allocator<StackAllocator>  stackAllocator(MBytesToBytes(512), &baseAllocator);

    const uint   multiplier = 1000;
    const uint   numPasses = 4;
    const uint   numAllocs[numPasses]  = {10000, 4000, 2000, 400};
    const size_t allocSizes[numPasses] = {16, 256, KBytesToBytes(128), MBytesToBytes(1)};

    int mallocTime[numPasses];
    int baseAllocatorTime[numPasses];
    int linearAllocatorTime[numPasses];
    int stackAllocatorTime[numPasses];

    const uint numAllocsMax = numAllocs[0];
    std::vector<void*> allocPointers(numAllocsMax);

    Timer<TimerHighResolution> timer;
    timer.start();

    int timeStart;

    for(uint pass = 0; pass < numPasses; ++pass)
    {
        timeStart = timer.getTicks();

        for(uint i = 0; i < multiplier; ++i)
        {
            for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
            {
                allocPointers[alloc] = malloc(allocSizes[pass]);
            }

            for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
            {
                free(allocPointers[alloc]);
            }
        }

        mallocTime[pass] = timer.getTicks() - timeStart;
    }

    for(uint pass = 0; pass < numPasses; ++pass)
    {
        timeStart = timer.getTicks();

        for(uint i = 0; i < multiplier; ++i)
        {
            for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
            {
                allocPointers[alloc] = baseAllocator.allocPlain(allocSizes[pass], 1);
            }

            for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
            {
                baseAllocator.deallocPlain(allocPointers[alloc]);
            }
        }

        baseAllocatorTime[pass] = timer.getTicks() - timeStart;
    }

    for(uint pass = 0; pass < numPasses; ++pass)
    {
        timeStart = timer.getTicks();

        for(uint i = 0; i < multiplier; ++i)
        {
            for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
            {
                allocPointers[alloc] = linearAllocator.allocPlain(allocSizes[pass], 1);
            }

            linearAllocator.clear();
        }

        linearAllocatorTime[pass] = timer.getTicks() - timeStart;
    }

    for(uint pass = 0; pass < numPasses; ++pass)
    {
        timeStart = timer.getTicks();

        for(uint i = 0; i < multiplier; ++i)
        {
            for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
            {
                allocPointers[alloc] = stackAllocator.allocPlain(allocSizes[pass], 1);
            }

            for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
            {
                stackAllocator.deallocPlain(allocPointers[numAllocs[pass] - alloc - 1]);
            }
        }

        stackAllocatorTime[pass] = timer.getTicks() - timeStart;
    }

    timer.stop();

    std::cout << "Allocators benchmark [multiplier = " << multiplier << "x] :\n";

    std::cout << "  Malloc:\n";
    for(uint pass = 0; pass < numPasses; ++pass)
        std::cout << "    " << numAllocs[pass] << " x " << sizeToReadable(allocSizes[pass]) << ": " << mallocTime[pass] << "ms\n";

    std::cout << "  BaseAllocator:\n";
    for(uint pass = 0; pass < numPasses; ++pass)
        std::cout << "    " << numAllocs[pass] << " x " << sizeToReadable(allocSizes[pass]) << ": " << baseAllocatorTime[pass] << "ms\n";

    std::cout << "  LinearAllocator:\n";
    for(uint pass = 0; pass < numPasses; ++pass)
        std::cout << "    " << numAllocs[pass] << " x " << sizeToReadable(allocSizes[pass]) << ": " << linearAllocatorTime[pass] << "ms\n";

    std::cout << "  StackAllocator:\n";
    for(uint pass = 0; pass < numPasses; ++pass)
        std::cout << "    " << numAllocs[pass] << " x " << sizeToReadable(allocSizes[pass]) << ": " << stackAllocatorTime[pass] << "ms\n";
}
