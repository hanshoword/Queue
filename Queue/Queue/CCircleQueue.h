#pragma once
#include <assert.h>

template <typename T, int SIZE = 100>
class CCircleQueue
{
public:
	CCircleQueue() :
		m_iSize(0),
		m_Front(-1),
		m_Rear(-1)
	{
	}
	~CCircleQueue()
	{
		clear();
	}
private:
	T	m_Array[SIZE] = { NULL, };
	int m_iSize;
	int m_Front;
	int m_Rear;

public:
	bool push(const T& data)
	{
		if (full())
		{
			return false;
		}

		int Rear = (m_Rear + 1) % (SIZE);

		m_Array[Rear] = data;
		m_Rear = Rear;
	
		m_iSize++;

		return true;
	}

	T front()	const
	{
		if (empty())
		{
			assert(false);
		}

		int Front = (m_Front + 1) % (SIZE);

		int data = m_Array[Front];

		return data;
	}

	T pop()
	{
		if (empty())
		{
			assert(false);
		}

		int Front = (m_Front + 1) % (SIZE);
		T	data = m_Array[Front];

		m_Front = Front;

		m_iSize--;

		return data;
	}

	void clear()
	{
		m_iSize = 0;
		m_Front = 0;
		m_Rear = 0;
	}

	void printQueue()
	{
		if (m_Front == m_Rear && m_iSize == 0)
		{
			cout << "Queue is empty.." << endl << endl;
		}
		else if (m_Front < m_Rear)
		{
			cout << "Queue [ ";
			for (int i = m_Front+1; i <= m_Rear; i++)
			{
				cout << m_Array[i] << " ";
			}
			cout << "]" << endl << endl;
		}
		else
		{
			cout << "Queue [ ";
			for (int j = 0; j <= m_Rear; j++)
			{
				cout << m_Array[j] << " ";
			}
			for (int i = m_Front + 1; i < SIZE; i++)
			{
				cout << m_Array[i] << " ";
			}
			cout << "]" << endl << endl;
		}
	}

	bool full()		const
	{
		return m_iSize == SIZE;
	}

	bool empty()	const
	{
		return m_iSize == 0;
	}

	int size()		const
	{
		return m_iSize;
	}
};

