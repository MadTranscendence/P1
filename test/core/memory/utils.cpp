#include "test/catch.hpp"
#include "src/core/memory/utils.hpp"
#include "src/core/types.hpp"

using namespace Core;


TEST_CASE("Testing Pointer Math", "[core][memory][utils]")
{
    SECTION("Aligning with alignment = 1")
    {
        u8 alignment = 1;
        void* alignedPointer = (void*)0x8880;

        INFO("alignment := " << (uint)alignment);
        CAPTURE(alignedPointer);

        SECTION("Aligning forward")
        {
            CHECK(PointerMath::alignForward(alignedPointer, alignment) == alignedPointer);
        }

        SECTION("Aligning backward")
        {
            CHECK(PointerMath::alignBackward(alignedPointer, alignment) == alignedPointer);
        }

        SECTION("Aligning forward adjustment")
        {
            CHECK(PointerMath::alignForwardAdjustment(alignedPointer, alignment) == 0);
        }

        SECTION("Aligning backward adjustment")
        {
            CHECK(PointerMath::alignBackwardAdjustment(alignedPointer, alignment) == 0);
        }
    }

    SECTION("Aligning with alignment = 16")
    {
        u8 alignment = 16;
        void* alignedPointer   = (void*)0x8880;
        void* unalignedPointer = (void*)0x8879;

        INFO("alignment := " << (uint)alignment);
        CAPTURE(alignedPointer);
        CAPTURE(unalignedPointer);

        SECTION("Aligning forward")
        {
            CHECK(PointerMath::alignForward(alignedPointer, alignment) == alignedPointer);
            CHECK(PointerMath::alignForward(unalignedPointer, alignment) > unalignedPointer);
            CHECK(((uptr)PointerMath::alignForward(unalignedPointer, alignment) % alignment) == 0);
        }

        SECTION("Aligning backward")
        {
            CHECK(PointerMath::alignBackward(alignedPointer, alignment) == alignedPointer);
            CHECK(PointerMath::alignBackward(unalignedPointer, alignment) < unalignedPointer);
            CHECK(((uptr)PointerMath::alignBackward(unalignedPointer, alignment) % alignment) == 0);
        }

        SECTION("Aligning forward adjustment")
        {
            CHECK(PointerMath::alignForwardAdjustment(alignedPointer, alignment) == 0);
            CHECK(PointerMath::alignForwardAdjustment(unalignedPointer, alignment) < alignment);
            CHECK(((PointerMath::alignForwardAdjustment(unalignedPointer, alignment) + (uptr)unalignedPointer) % alignment) == 0);
        }

        SECTION("Aligning backward adjustment")
        {
            CHECK(PointerMath::alignBackwardAdjustment(alignedPointer, alignment) == 0);
            CHECK(PointerMath::alignBackwardAdjustment(unalignedPointer, alignment) < alignment);
            CHECK(((-PointerMath::alignBackwardAdjustment(unalignedPointer, alignment) + (uptr)unalignedPointer) % alignment) == 0);
        }
    }

    SECTION("Pointers arithmetic")
    {
        void* pointer = (void*)0x8880;
        size_t offset = 24;

        CAPTURE(pointer);
        CAPTURE(offset);

        CHECK((uptr)PointerMath::add(pointer, offset) == (uptr)pointer + offset);
        CHECK((uptr)PointerMath::sub(pointer, offset) == (uptr)pointer - offset);
    }
}
