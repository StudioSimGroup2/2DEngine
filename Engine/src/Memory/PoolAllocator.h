#pragma once

#include <cstddef>

class Heap;
struct Header;

struct MemNode
{
	MemNode* next;
};

namespace Engine
{
	class PoolAllocator
	{
	public:
		PoolAllocator();
		~PoolAllocator();
		
		void Init(size_t object, Heap* heap, size_t sizeOfBlock = 1024);

		void* Alloc(size_t size);
		void Free(void* ptr);

	private:
		MemNode* RequestFromOS(size_t size);

		size_t mSize;

		MemNode* mNode;

		Heap* mHeap;
	};
}

