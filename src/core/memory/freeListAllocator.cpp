#include "../../common.hpp"
#include "freeListAllocator.hpp"

#include <cassert>


namespace Core
{
    FreeListAllocator::FreeListAllocator(size_t size, void* pointer)
    {
        assert(pointer != nullptr);
        assert(size > 0);

        m_memInfo.pointer  = pointer;
        m_memInfo.size     = size;
        m_freeBlocks       = (FreeBlock*)pointer;
        m_freeBlocks->size = size;
        m_freeBlocks->next = nullptr;
    }

    FreeListAllocator::~FreeListAllocator()
    {
        assert(m_memInfo.usedMemory == 0);
    }

    FreeListAllocator::FreeListAllocator(FreeListAllocator&& freeListAllocator)
    {
        m_memInfo    = std::move(freeListAllocator.m_memInfo);
        m_freeBlocks = freeListAllocator.m_freeBlocks;
    }

    FreeListAllocator& FreeListAllocator::operator=(FreeListAllocator&& freeListAllocator)
    {
        m_memInfo    = std::move(freeListAllocator.m_memInfo);
        m_freeBlocks = freeListAllocator.m_freeBlocks;

        return *this;
    }

    void* FreeListAllocator::allocate(size_t size, u8 alignment)
    {
        FreeBlock* prevBlock = nullptr;
        FreeBlock* freeBlock = m_freeBlocks;

        while(freeBlock != nullptr)
        {
            u8 adjustment = PointerMath::alignForwardAdjustmentHeader(freeBlock, alignment, sizeof(AllocationHeader));
            size_t totalSize = size + adjustment;

            if(freeBlock->size < totalSize)
            {
                prevBlock = freeBlock;
                freeBlock = freeBlock->next;
                continue;
            }

            FreeBlock* nextBlock;

            constexpr size_t minBlockSize = max(sizeof(AllocationHeader), sizeof(FreeBlock));
            if(freeBlock->size - totalSize > minBlockSize)
            {
                nextBlock = (FreeBlock*)PointerMath::add(freeBlock, totalSize);
                nextBlock->size = freeBlock->size - totalSize;
                nextBlock->next = freeBlock->next;
            }
            else
            {
                nextBlock = freeBlock->next;
                totalSize = freeBlock->size;
            }

            if(prevBlock != nullptr)
                prevBlock->next = nextBlock;
            else
                m_freeBlocks    = nextBlock;

            void* alignedPtr = PointerMath::add(freeBlock, adjustment);

            AllocationHeader* header = (AllocationHeader*)PointerMath::sub(alignedPtr, sizeof(AllocationHeader));
            header->size       = totalSize;
            header->adjustment = adjustment;

            m_memInfo.usedMemory += totalSize;
            m_memInfo.numAllocations++;

            return alignedPtr;
        }

        return nullptr;
    }

    void FreeListAllocator::deallocate(void* pointer)
    {
        if(pointer)
        {
            AllocationHeader* header = (AllocationHeader*)PointerMath::sub(pointer, sizeof(AllocationHeader));

            uptr blockStart  = (uptr)PointerMath::sub(pointer, header->adjustment);
            size_t blockSize = header->size;
            uptr blockEnd    = blockStart + blockSize;

            m_memInfo.usedMemory -= blockSize;
            m_memInfo.numAllocations--;

            FreeBlock* prevBlock = nullptr;
            FreeBlock* freeBlock = m_freeBlocks;

            while(freeBlock != nullptr && (uptr)freeBlock < blockEnd)
            {
                prevBlock = freeBlock;
                freeBlock = freeBlock->next;
            }

            if(prevBlock == nullptr)
            {
                prevBlock = (FreeBlock*)blockStart;
                prevBlock->size = blockSize;
                prevBlock->next = freeBlock;
                m_freeBlocks    = prevBlock;
            }
            else if((uptr)prevBlock + prevBlock->size == blockStart)
            {
                prevBlock->size += blockSize;
            }
            else
            {
                FreeBlock* block = (FreeBlock*)blockStart;
                block->size      = blockSize;
                block->next      = prevBlock->next;
                prevBlock->next  = block;

                prevBlock = block;
            }

            if(freeBlock != nullptr && (uptr)freeBlock == blockEnd)
            {
                prevBlock->size += freeBlock->size;
                prevBlock->next  = freeBlock->next;
            }
        }
    }

    void FreeListAllocator::clear()
    {
        m_memInfo.usedMemory     = 0;
        m_memInfo.numAllocations = 0;
        m_freeBlocks             = (FreeBlock*)m_memInfo.pointer;
    }

    const MemoryInfo* FreeListAllocator::getMemoryInfo() const
    {
        return &m_memInfo;
    }
}
