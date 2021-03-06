
#include <iostream>

using namespace std;

class CListNode
{
public:
	CListNode():
		m_pPrev(NULL),
		m_pNext(NULL)
	{

	}
	~CListNode()
	{

	}

public:
	int m_iData;
	CListNode* m_pNext;
	CListNode* m_pPrev;
};

class CList
{
public:
	CList()
	{
		m_pBegin = new  CListNode;
		m_pEnd = new CListNode;

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}
	~CList()
	{
		Clear();
		delete m_pBegin;
		delete m_pEnd;
	}

private:
	CListNode* m_pBegin;
	CListNode* m_pEnd;
	int m_iSize;

public:
	void Push_back(int iData)
	{
		CListNode * pNode = new CListNode;

		pNode->m_iData = iData;

		CListNode* pPrev = m_pEnd->m_pPrev;

		m_pEnd->m_pPrev = pNode;
		pNode->m_pNext = m_pEnd;

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		++m_iSize;
	}

	int Pop_back()
	{
		CListNode* pPrev = m_pEnd->m_pPrev;

		if (pPrev == m_pBegin)
			return INT_MAX;

		int iData = pPrev->m_iData;

		CListNode* pPrevP = pPrev->m_pPrev;

		pPrevP->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = pPrevP;

		--m_iSize;

		delete pPrev;

		return iData;
	}

	bool empty()
	{
		return m_iSize == 0;
	}

	void Clear()
	{
		CListNode* pNode = m_pBegin->m_pNext;

		while (pNode != m_pEnd)
		{
			CListNode* pNext = pNode->m_pNext;
			delete pNode;
			pNode = pNext;
		}

		m_pBegin->m_pNext = m_pEnd;
		m_pEnd->m_pPrev = m_pBegin;

		m_iSize = 0;
	}
};

int main()
{
	CList list;

	for (int i = 0; i < 100; ++i)
	{
		list.Push_back(i);
	}

	while (!list.empty())
	{
		cout << list.Pop_back() << endl;
	}

	return 0;
}