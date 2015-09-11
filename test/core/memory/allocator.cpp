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

std::string ratioToReadable(int numerator, int denominator)
{
    float ratio = float(numerator)/float(denominator);
    if(ratio < 1.0f)
        ratio = 1.0f/ratio;

    return std::to_string(ratio) + (numerator > denominator ? " x slower" : " x faster");
}

template<class T>
void performBenchmark(T& allocator, const uint& multiplier, const uint* numAllocs, const uint& numAllocsMax, const size_t* allocSizes, uint& pass)
{
    static std::vector<void*> allocPointers(numAllocsMax);

    for(uint i = 0; i < multiplier; ++i)
    {
        for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
        {
            allocPointers[alloc] = allocator.allocPlain(allocSizes[pass], 1);
        }

        for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
        {
            allocator.deallocPlain(allocPointers[alloc]);
        }
    }
}

template<>
void performBenchmark(Allocator<LinearAllocator>& allocator, const uint& multiplier, const uint* numAllocs, const uint& numAllocsMax, const size_t* allocSizes, uint& pass)
{
    static std::vector<void*> allocPointers(numAllocsMax);

    for(uint i = 0; i < multiplier; ++i)
    {
        for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
        {
            allocPointers[alloc] = allocator.allocPlain(allocSizes[pass], 1);
        }

        allocator.clear();
    }
}

template<>
void performBenchmark(Allocator<StackAllocator>& allocator, const uint& multiplier, const uint* numAllocs, const uint& numAllocsMax, const size_t* allocSizes, uint& pass)
{
    static std::vector<void*> allocPointers(numAllocsMax);

    for(uint i = 0; i < multiplier; ++i)
    {
        for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
        {
            allocPointers[alloc] = allocator.allocPlain(allocSizes[pass], 1);
        }

        for(uint alloc = 0; alloc < numAllocs[pass]; ++alloc)
        {
            allocator.deallocPlain(allocPointers[numAllocs[pass] - alloc - 1]);
        }
    }
}

TEST_CASE("Test Allocator", "[core][memory][allocator]")
{
    Allocator<BaseAllocator>     baseAllocator;
    Allocator<LinearAllocator>   linearAllocator(MBytesToBytes(512), &baseAllocator);
    Allocator<StackAllocator>    stackAllocator(MBytesToBytes(512), &baseAllocator);
    Allocator<FreeListAllocator> freeListAllocator(MBytesToBytes(512), &baseAllocator);

    const uint   multiplier = 1500;
    const uint   numPasses = 7;
    const uint   numAllocs[numPasses]  = {2000, 2000, 2000, 1500, 1000, 600, 400};
    const size_t allocSizes[numPasses] = {256, KBytesToBytes(1), KBytesToBytes(4), KBytesToBytes(64), KBytesToBytes(128), KBytesToBytes(256), MBytesToBytes(1)};

    int baseAllocatorTime[numPasses];
    int linearAllocatorTime[numPasses];
    int stackAllocatorTime[numPasses];
    int freeListAllocatorTime[numPasses];

    int baseAllocatorTimeSummary = 0;
    int linearAllocatorTimeSummary = 0;
    int stackAllocatorTimeSummary = 0;
    int freeListAllocatorTimeSummary = 0;

    const uint numAllocsMax = numAllocs[0];

    Timer<TimerHighResolution, TimerMilliseconds> timer;
    timer.start();

    int timeStart;

    for(uint pass = 0; pass < numPasses; ++pass)
    {
        timeStart = timer.getTicks();

        performBenchmark(baseAllocator, multiplier, numAllocs, numAllocsMax, allocSizes, pass);

        baseAllocatorTime[pass] = timer.getTicks() - timeStart;
        baseAllocatorTimeSummary += baseAllocatorTime[pass];
    }

    for(uint pass = 0; pass < numPasses; ++pass)
    {
        timeStart = timer.getTicks();

        performBenchmark(linearAllocator, multiplier, numAllocs, numAllocsMax, allocSizes, pass);

        linearAllocatorTime[pass] = timer.getTicks() - timeStart;
        linearAllocatorTimeSummary += linearAllocatorTime[pass];
    }

    for(uint pass = 0; pass < numPasses; ++pass)
    {
        timeStart = timer.getTicks();

        performBenchmark(stackAllocator, multiplier, numAllocs, numAllocsMax, allocSizes, pass);

        stackAllocatorTime[pass] = timer.getTicks() - timeStart;
        stackAllocatorTimeSummary += stackAllocatorTime[pass];
    }

    for(uint pass = 0; pass < numPasses; ++pass)
    {
        timeStart = timer.getTicks();

        performBenchmark(freeListAllocator, multiplier, numAllocs, numAllocsMax, allocSizes, pass);

        freeListAllocatorTime[pass] = timer.getTicks() - timeStart;
        freeListAllocatorTimeSummary += freeListAllocatorTime[pass];
    }

    timer.stop();

    std::cout << "Allocators benchmark [multiplier = " << multiplier << "x] :\n";

    for(uint pass = 0; pass < numPasses; ++pass)
    {
        std::cout << "  " << numAllocs[pass] << " x " << sizeToReadable(allocSizes[pass]) << ":\n";
        std::cout << "    BaseAllocator.... " << baseAllocatorTime[pass]      << " ms\n";
        std::cout << "    LinearAllocator.. " << linearAllocatorTime[pass]    << " ms  (" << ratioToReadable(linearAllocatorTime[pass], baseAllocatorTime[pass]) << ")\n";
        std::cout << "    StackAllocator... " << stackAllocatorTime[pass]     << " ms  (" << ratioToReadable(stackAllocatorTime[pass], baseAllocatorTime[pass]) << ")\n";
        std::cout << "    FreeListAllocator " << freeListAllocatorTime[pass]  << " ms  (" << ratioToReadable(freeListAllocatorTime[pass], baseAllocatorTime[pass]) << ")\n";
    }

    std::cout << "  Summary:\n";
    std::cout << "    BaseAllocator.... " << baseAllocatorTimeSummary     << " ms\n";
    std::cout << "    LinearAllocator.. " << linearAllocatorTimeSummary   << " ms  (" << ratioToReadable(linearAllocatorTimeSummary, baseAllocatorTimeSummary) << ")\n";
    std::cout << "    StackAllocator... " << stackAllocatorTimeSummary    << " ms  (" << ratioToReadable(stackAllocatorTimeSummary, baseAllocatorTimeSummary) << ")\n";
    std::cout << "    FreeListAllocator " << freeListAllocatorTimeSummary << " ms  (" << ratioToReadable(freeListAllocatorTimeSummary, baseAllocatorTimeSummary) << ")\n";
}
