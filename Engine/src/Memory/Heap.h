#pragma once

#include <cstddef>

struct Header;

class Heap
{
public:
	void Initialize();
	void Enable(const char* name);
	void Disable();
	void AttachToParent(Heap* pParent);
	void DetachFromParent();

	void* AllocBytes(size_t size);
	Header* AddHeader(Header* header, size_t size);
	Header* RemoveHeader(Header* header);
	static void DeAllocBytes(void* pMem);

	bool GetStatus() const { return m_status; }
	size_t GetSize() const { return m_size; }

	const char* GetName() const;

private:
	void DeAllocBytes(Header* pHeader);

	int    m_pos;

	bool   m_status;

	char   m_name[64]; // Increase as needed

	Header* m_Header;

	size_t m_size;

	Heap* m_pParent;
	Heap* m_pNext;
	Heap* m_pPrev;
	Heap* m_pFirstChild;
};
