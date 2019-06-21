#pragma once

/*
Queue : ���Լ��� ������ �ڷᱸ��
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
		//�߰��� ��带 �����Ѵ�
		PNODE	pNode = new NODE;
		pNode->m_Data = data;

		//  m_pRear != nullptr, �� �̹� �߰��� ��尡 ������쿡��
		//  Rear�� ������ ���ο� ��带 �����Ѵ�.
		if (m_pRear)
		{
			m_pRear->m_pNext = pNode;
		}
		
		//Rear�� ���ο� ����� �ּҸ� �ش�
		m_pRear = pNode;

		// m_pFront == nullptr�̶��(ó�� �߰��ϴ� �����)
		// Front�� ���ο� ��� �ּҸ� �ش�
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

		//front ��������� �ּҸ� ����
		PNODE	pNext = m_pFront->m_pNext;

		// front�� ������ ����
		T	data = m_pFront->m_Data;

		delete m_pFront;

		m_pFront = pNext;

		// front�� nullptr�̶� ���� ��尡 ��� �����Ǿ��ٴ� �ǹ��̴�.
		// ��尡 �������������Ƿ� Rear���� nullptr�� ���ش�.
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

		// pNode�� nullptr�� �ƴϸ� �ݺ�
		// nullptr�̶�� ��� ��带 �����ٴ� �ǹ��̴�.
		while (pNode)
		{
			// �������� ������带 ����
			PNODE	pNext = pNode->m_pNext;

			// ��带 �����
			delete pNode;

			// �̸� �����ص� �������� ����
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
