#pragma once

#include <cstddef>

class Heap;
struct Header;

struct MemNode
{
	Header* pHeader;
	MemNode* pNext;
};

namespace Engine
{
	class FreeListAllocator
	{
	public:
		FreeListAllocator();
		~FreeListAllocator();

		void Init(Heap* heap, size_t initSize = 1024);

		void* Alloc(size_t size);
		void Free(void* ptr);

	private:
		MemNode* RequestFromOS(size_t size);

		Heap* mHeap;
	};
}