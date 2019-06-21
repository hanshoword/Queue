#pragma once

/*
Queue : 선입선출 구조의 자료구조
*/

#include <assert.h>

using namespace std;

template <typename T>
class CQueueNode
{
	template<typename T>
	friend class CQueueList;
private:
	CQueueNode()	:
		m_pNext(nullptr)
	{
		
	}
	~CQueueNode()
	{

	}
private:
	CQueueNode<T>*	m_pNext;
	T				m_Data;
};

template <typename T>
class CQueueList
{
public:
	CQueueList()	:
		m_pFront(nullptr),
		m_pRear(nullptr),
		m_iSize(0)
	{
	}
	~CQueueList()
	{
		clear();
	}

private:
	typedef CQueueNode<T> NODE;
	typedef CQueueNode<T>* PNODE;
private:
	int		m_iSize;
	PNODE	m_pFront;
	PNODE	m_pRear;

public:
	void push(const T& data)
	{
		//추가할 노드를 생성한다
		PNODE	pNode = new NODE;
		pNode->m_Data = data;

		//  m_pRear != nullptr, 즉 이미 추가된 노드가 있을경우에만
		//  Rear의 다음에 새로운 노드를 연결한다.
		if (m_pRear)
		{
			m_pRear->m_pNext = pNode;
		}
		
		//Rear에 새로운 노드의 주소를 준다
		m_pRear = pNode;

		// m_pFront == nullptr이라면(처음 추가하는 경우라면)
		// Front에 새로운 노드 주소를 준다
		if (!m_pFront)
		{
			m_pFront = pNode;
		}

		m_iSize++;
	}

	T front()	const
	{
		if (empty())
		{
			assert(false);
		}
	
		return m_pFront->m_Data;
	}

	T pop()
	{
		if (empty())
		{
			assert(false);
		}

		//front 다음노드의 주소를 저장
		PNODE	pNext = m_pFront->m_pNext;

		// front의 데이터 저장
		T	data = m_pFront->m_Data;

		delete m_pFront;

		m_pFront = pNext;

		// front가 nullptr이란 것은 노드가 모두 삭제되었다는 의미이다.
		// 노드가 남아있지않으므로 Rear또한 nullptr로 해준다.
		if (!m_pFront) 
		{
			m_pRear = nullptr;
		}

		m_iSize--;

		return data;
	}

	void clear()
	{
		PNODE	pNode = m_pFront;

		// pNode가 nullptr이 아니면 반복
		// nullptr이라면 모든 노드를 지웠다는 의미이다.
		while (pNode)
		{
			// 지울노드의 다음노드를 저장
			PNODE	pNext = pNode->m_pNext;

			// 노드를 지운다
			delete pNode;

			// 미리 저장해둔 다음노드로 갱신
			pNode = pNext;
		}

		m_iSize = 0;

		m_pFront = nullptr;
		m_pRear = nullptr;
	}

	void printQueue()
	{
		PNODE	pNode = m_pFront;
		
		cout << "Queue [ ";
		while (pNode)
		{
			PNODE	pNext = pNode->m_pNext;

			cout << pNode->m_Data << " ";

			pNode = pNext;
		}
		cout << "]" << endl << endl;
	}
	bool empty()	const
	{
		return m_iSize == 0;
	}

	int size()	const
	{
		return m_iSize;
	}
};
