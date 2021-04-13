#include "Heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>

struct Header
{
	int           size;

	Heap* pHeap;
	Header* pNext;
	Header* pPrev;
};

void Heap::Initialize()
{
	m_status = false;
	m_size = 0;
	m_pos = 0;
	m_Header = nullptr;

	m_pParent = nullptr;
	m_pNext = nullptr;
	m_pPrev = nullptr;
	m_pFirstChild = nullptr;
}

void Heap::Enable(const char* name)
{
	if (name == nullptr)
		return;

	strcpy_s(m_name, name);
	m_size = 0;
	m_pos = 0;
	m_status = true;
}

void Heap::Disable()
{
	strcpy_s(m_name, "");

	m_size = 0;
	m_pos = 0;
	m_status = false;
}

const char* Heap::GetName() const
{
	return m_name;
}

void* Heap::AllocBytes(size_t size)
{
	size_t nRequestedBytes = size + sizeof(Header);
	char* pMem = (char*)malloc(nRequestedBytes);
	Header* pHeader = (Header*)pMem;

	pHeader->size = size;
	pHeader->pHeap = this;
	pHeader->pNext = m_Header;
	pHeader->pPrev = nullptr;

	if (m_Header != nullptr)
		m_Header->pPrev = pHeader;

	m_Header = pHeader;

	m_size += size;

	void* pStartMemBlock = pMem + sizeof(Header);
	return pStartMemBlock;
}

Header* Heap::AddHeader(Header* header, size_t size)
{
	//std::lock_guard<std::mutex> guard(m_mutex);

	header->size = size;
	header->pHeap = this;
	header->pNext = m_Header;
	header->pPrev = nullptr;

	if (m_Header != nullptr)
		m_Header->pPrev = header;

	m_Header = header;

	m_size += size;

	return header;
}

Header* Heap::RemoveHeader(Header* header)
{
	if (header->pPrev == nullptr)
	{
		if (header != m_Header)
			return nullptr;

		m_Header = header->pNext;
	}
	else
		header->pPrev->pNext = header->pNext;

	if (header->pNext != nullptr)
		header->pNext->pPrev = header->pPrev;

	m_size -= header->size;
	m_pos--;

	header->size = 0;

	return header;
}

void Heap::DeAllocBytes(void* pMem)
{
	Header* pHeader = (Header*)((char*)pMem -
		sizeof(Header));

	pHeader->pHeap->DeAllocBytes(pHeader);
}

void Heap::DeAllocBytes(Header* pHeader)
{

	if (pHeader->pPrev == nullptr)
	{
		if (pHeader != m_Header)
			return;

		m_Header = pHeader->pNext;
	}
	else
		pHeader->pPrev->pNext = pHeader->pNext;

	if (pHeader->pNext != nullptr)
		pHeader->pNext->pPrev = pHeader->pPrev;

	m_size -= pHeader->size;
	m_pos--;

	free(pHeader);
}

void Heap::AttachToParent(Heap* pParent)
{
	if (pParent == m_pParent)
		return;

	DetachFromParent();

	m_pNext = pParent->m_pFirstChild;
	m_pPrev = nullptr;
	m_pParent = pParent;
	pParent->m_pFirstChild = this;
}

void Heap::DetachFromParent()
{
	if (m_pParent == nullptr)
		return;

	if (m_pPrev != nullptr)
		m_pPrev->m_pNext = m_pNext;
	else
		m_pParent->m_pFirstChild = m_pNext;

	if (m_pNext != nullptr)
		m_pNext->m_pPrev = m_pPrev;
}