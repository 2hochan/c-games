#pragma once

template<typename T>
class CQueueNode
{
private:
	CQueueNode():
		m_pNext(NULL),
		m_pPrev(NULL)
	{}
	~CQueueNode()
	{}

private:
	template <typename T>
	friend class CQueue;

private:
	T	m_Data;
	CQueueNode<T>*	m_pNext;
	CQueueNode<T>*	m_pPrev;
};

template <typename T>
class CQueue
{
public:
	CQueue()
	{
		m_pBegin = new NODE;
		m_pEnd = new NODE;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;
		m_iSize = 0;
	}

	~CQueue()
	{
	}

private:
	typedef CQueueNode<T>	NODE;
	typedef CQueueNode<T>*	PNODE;

private:
	unsigned int m_iSize;
	PNODE m_pBegin;
	PNODE m_pEnd;

public:
	void push(const T& data)
	{
		PNODE pNode = new NODE;

		pNode->m_Data = data;
		PNODE pPrev = m_pEnd->m_pPrev;

		pNode->m_pPrev = pPrev;
		pPrev->m_pNext = pNode;

		m_pEnd->m_pPrev = pNode;
		pNode->m_pNext = m_pEnd;
		
		++m_iSize;
	}

	T pop()
	{
		if (empty())
			return 0;

		PNODE pNode = m_pBegin->m_pNext;

		T data = pNode->m_Data;

		m_pBegin->m_pNext = pNode->m_pNext;
		pNode->m_pNext->m_pPrev = m_pBegin;

		delete pNode;
		--m_iSize;
		return data;
	}

	bool empty()
	{
		return m_iSize == 0;
	}

};

template <typename T, int SIZE = 100>
class CCircleQueue
{
public:
	CCircleQueue()
	{
		m_iSize = 0;
		m_iHead = 0;
		m_iTail = 0;
	}
	~CCircleQueue()
	{}

private:
	T	m_Data[SIZE + 1];
	unsigned int m_iSize;
	unsigned int m_iHead;
	unsigned int m_iTail;

public:
	void push(const T& data)
	{
		if (full())
			return;

		int idx = (m_iTail + 1) % (SIZE + 1);

		m_Data[idx] = data;

		m_iTail = idx;

		++m_iSize;
	}

	T pop()
	{
		if (empty())
			return 0;

		int idx = (m_iHead + 1) % (SIZE + 1);

		T data = m_Data[idx];

		m_iHead = idx;
		--m_iSize;

		return data;
	}

	bool full()
	{
		return m_iSize == SIZE;
	}

	bool empty()
	{
		return m_iSize == 0;
	}
};