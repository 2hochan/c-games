#pragma once

template <typename T>
class CVectorNode
{
private:
	CVectorNode():
		m_pNext(NULL),
		m_pPrev(NULL)
	{}
	~CVectorNode()
	{}

private:
	template <typename T>
	friend class CVector;
	template <typename T>
	friend class CVectorIterator;

private:
	T		m_Data;
	int		m_iIndex;
	CVectorNode<T>* m_pNext;
	CVectorNode<T>* m_pPrev;
};

// vector의 iterator 구현
template <typename T>
class CVectorIterator
{
private:
	template <typename T>
	friend class CVector;

private:
	typedef CVectorNode<T>	NODE;
	typedef CVectorNode<T>*	PNODE;

public:
	PNODE m_pNode;

public:
	bool operator ==(const CVectorIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}
	bool operator !=(const CVectorIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}
	void operator ++()
	{
		m_pNode = m_pNode->m_pNext;
	}
	void operator --()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	T operator *()
	{
		return m_pNode->m_Data;
	}
};

template <typename T>
class CVector
{
public:
	CVector()
	{
		m_iSize = 0;
		m_iCapacity = 2;

		m_pArray = new NODE[m_iCapacity + 2];
	}

	CVector(int iSize)
	{
		m_pArray = new NODE[iSize + 2];
		m_iCapacity = iSize;
		m_iSize = 0;
	}

	~CVector()
	{
		delete[] m_pArray;
	}

private:
	typedef CVectorNode<T>	NODE;
	typedef CVectorNode<T>*	PNODE;

public:
	typedef CVectorIterator<T> iterator;

private:
	PNODE m_pArray;
	unsigned int	m_iSize;
	unsigned int	m_iCapacity;

public:
	void push_back(const T& data)
	{
		if (full())
			resize(m_iSize * 2);

		m_pArray[m_iSize + 1].m_Data = data;
		m_pArray[m_iSize + 1].m_iIndex = m_iSize;

		// iterator ++ operator를 위해 다음 주소 넣어주기
		m_pArray[m_iSize].m_pNext = &m_pArray[m_iSize + 1];
		m_pArray[m_iSize + 1].m_pPrev = &m_pArray[m_iSize];

		++m_iSize;
	}

	void resize(int iSize)
	{
		// begin과 end를 포함시켜 생성하기위해 +2
		PNODE pArray = new NODE[iSize + 2];

		// 위에서 2배만큼 공간을 새로 할당하고 기존에 있는 노드의
		// 데이터를 새로 할당한 공간에 복사
		// 1번 인덱스부터 시작이 되기때문에 +1을 해주어 1번 메모리부터
		// 복사를 시작한다.
		memcpy(pArray + 1, m_pArray + 1, sizeof(NODE) * m_iSize);

		// 기존 노드를 삭제한다.
		delete[] m_pArray;

		m_pArray = pArray;
		m_iCapacity = iSize;
	}

	void clear()
	{
		delete[] m_pArray;
		m_iSize = 0;
		m_iCapacity = 2;
		m_pArray = new NODE[m_iCapacity + 2];
	}

	bool full()
	{
		return m_iSize == m_iCapacity;
	}

	bool empty()
	{
		return m_iSize == 0;
	}

	unsigned int size() const
	{
		return m_iSize;
	}

	unsigned int capacity() const
	{
		return m_iCapacity;
	}

	T operator [](int idx)
	{
		return m_pArray[idx + 1].m_Data;
	}

	void reserve(int iSize)
	{
		delete[] m_pArray;

		m_pArray = new NODE[iSize + 2];

		m_iCapacity = iSize;
		m_iSize = 0;
	}

	iterator begin()
	{
		iterator iter;
		iter.m_pNode = &m_pArray[1];
		return iter;
	}
	iterator end()
	{
		iterator iter;
		iter.m_pNode = &m_pArray[m_iCapacity + 2];
		return iter;
	}

};

