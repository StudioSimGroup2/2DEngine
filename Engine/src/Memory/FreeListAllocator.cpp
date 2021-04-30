#include "FreeListAllocator.h"
#include <Memory/Heap.h>

// TODO: Byte alignment
struct Header
{
	int size;
};

namespace Engine
{
	FreeListAllocator::FreeListAllocator()
	{
		mHeap = nullptr;
	}

	FreeListAllocator::~FreeListAllocator()
	{
	}

	void FreeListAllocator::Init(Heap* heap, size_t initSize)
	{
		mHeap = heap;
		RequestFromOS(initSize);
	}

	void* FreeListAllocator::Alloc(size_t size)
	{
		return nullptr;
	}

	void FreeListAllocator::Free(void* ptr)
	{
	}

	MemNode* FreeListAllocator::RequestFromOS(size_t size)
	{
		return nullptr;
	}
}