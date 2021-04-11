#include "PoolAllocator.h"
#include "Heap.h"
#include <stdlib.h>  // malloc, free
#include <iostream>



namespace Engine
{
    PoolAllocator::PoolAllocator()
    {
        mHeap = nullptr;
        mNode = nullptr;
        mSize = 0;
    }

    PoolAllocator::~PoolAllocator()
    {
    }

    void PoolAllocator::Init(size_t object, Heap* heap, size_t sizeOfBlock)
    {
        // TODO: Byte alignment of object
        
        mSize = sizeOfBlock;
        mHeap = heap;

        mNode = RequestFromOS(object);
    }

    void* PoolAllocator::Alloc(size_t size)
    {
        //TODO: Handle pool allocator full

        if (mNode == nullptr)
        {
            std::cout << "Unable to allocate space" << std::endl;
            return nullptr;
        }

        MemNode* freeNode = mNode;

        mNode = mNode->next;

        /*if (mHeap != nullptr)
            mHeap->AddHeader(freeNode->mHeader, size);*/

        return freeNode;
    }

    void PoolAllocator::Free(void* ptr)
    {
        reinterpret_cast<MemNode*>(ptr)->next = mNode;

        mNode = reinterpret_cast<MemNode*>(ptr);
    }

    MemNode* PoolAllocator::RequestFromOS(size_t size)
    {
        size_t requestedSize = mSize * size;

        MemNode* block = reinterpret_cast<MemNode*>(malloc(requestedSize));

        MemNode* data = block;

        for (int i = 0; i < requestedSize - 1; i++)
        {
            data->next = reinterpret_cast<MemNode*>(reinterpret_cast<char*>(data) + size);

            data = data->next;
        }

        data->next = nullptr;

        return block;
    }

}