## Queue
### Linked List Queue

#### CQueue.h

```c
/*
Queue : 선입선출 구조의 자료구조
*/
#include <assert.h>
using namespace std;
```
에러처리를 위한 헤더파일과 std 포함 

##### CQueueNode Class
```c
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
```

* 여러 자료형을 받아 들이기위해 template<typename T>를 줍니다.

* CQueueNode는 T형 데이터와 다음 노드의 주소인 m_pNext를 멤버변수로 가집니다.

* 생성자에서 m_pNext를 nullptr로 초기화해주며,

* CQueueList에서 private 변수를 사용할수 있도록 friend class로 선언해줍니다.


##### CQueueList Class
```c
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
```

* CQueueList는 멤버변수
  * 큐에 삽입된 노드의 수(m_iSize)
  * Push 위치를 가리키는 포인터 m_pRear
  * Pop의 위치를 가리키는 포인터 m_pFront로 구성됩니다.
  
* 자료형을 사용하기 쉽게 명명하였습니다.
  * CQueueNode<T>  : NODE
  * CQueueNode<T>* : PNODE

* 생성자에서는 멤버변수들을 0과 nullptr을 통해 초기화시킵니다.

* 소멸자에서는 clear함수를 통해 Queue를 삭제합니다. clear함수는 뒤에서 설명합니다.


##### Push 함수 : 새로운 노드를 큐에 삽입하는 함수
```c
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
```

* 새로운노드 pNode를 생성하고 매개변수에서 받아온 data를 넣어줍니다.

* 이제 두가지 경우가 있습니다.
  * m_pRear가 nullptr인경우 : 삽입된 노드가 없다.
  * m_pRear가 nullptr이 아닌경우 : 삽입된 노드가 있다.
  
* 첫 번 째 경우 if(m_pRear) : Rear의 다음위치에 새로운 노드를 연결하고, Rear은 새로운 노드를 가리키게 합니다. 
* 두 번 째 경우             : 그냥 새로운 노드를 Rear이 가리키게 합니다.

* 그리고 m_pFront가 nullptr이란건, 한 번도 push와 pop이 일어나지 않았다는 의미이다.
* 따라서 맨 처음 노드인 pNode를 가리키게 해둔다. ( pop을 할 때 맨처음 생성된 pNode부터 지우게 된다)

##### empty 함수 : 빈 Queue인지 

```c
bool empty()	const
{
  return m_iSize == 0;
}
```
* Queue에 들어있는 노드의 수를 반환

##### pop 함수 : Queue 데이터를 선입선출구조로 내보내는 함수

```c

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
```
* 먼저 빈 리스트인지 체크를 합니다 ( 빼내올 데이터가 있어야하므로)

* 일단 Front의 다음노드를 미리 저장해둡니다.

* Front를 지우기전에 반환해야할 Front의 데이터를 저장해둡니다.

* 기존의 Front를 지우고, Front는 미리저장해둔 pNext로 대체됩니다.

* 만약 Front가 nullptr이라는 의미는, 모두 pop되어 더이상 노드가 없다는 의미이므로 Rear또한 nullptr로 바꿔줍니다. 
  * (push에서 Rear이 nullptr 인지 아닌지를 판별하여 동작을 수행하는 조건식이 있기때문입니다)

* 사이즈를 줄여주고 미리 저장해둔 data를 반환하며 마칩니다.


##### clear 함수 : 삽입된 모든 노드를 제거하는 함수

```c
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
```

* 탐색노드는 Front부터 시작합니다.

* 노드가 존재한다면 반복문을 수행합니다.
  * 일단 미리 다음 노드(pNext)를 저장해둡니다. 
  * 그리고 현재노드를 지운후, 탐색노드는 pNext가 됩니다.
  
* 큐가 비어있으므로 사이즈는 0이되며, Front와 Rear를 nullptr로 초기화합니다.

##### front 함수 : 제일 먼저 내보내야할 데이터를 반환

```c
	T front()	const
	{
		if (empty())
		{
			assert(false);
		}
	
		return m_pFront->m_Data;
	}
```

* 큐가 비어있다면 에러처리를 합니다.
* 큐의 선입선출구조에서 먼저 출력되야할 Data를 반환합니다.

##### printQueue 함수 : Queue의 노드를 순서대로 출력하는 함수

```c
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
```

* 먼저 탐색노드는 Front부터 시작합니다. 
* pNode가 존재한다면 반복문(Data를 출력하고 다음노드로)을 수행합니다. 

##### size 함수

```c
	int size()	const
	{
		return m_iSize;
	}
```

* private 변수인 사이즈를 반환합니다.



### Circle Queue
#### CCircleQueue.h
* Circle Queue는 맨 끝지점과 첫 지점이 이어져있는 상태의 자료구조입니다.
* 선입선출 구조로, 앞에서부터 데이터를 채우며, 앞에서부터 데이터가 나갑니다.
* pop이 수행되면서 앞에서부터 빈자리가 생기게되는데 이것을 다시 활용합니다.

##### CCircleQueue Class

```c
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
```

* CCircleQueue Class의 멤버변수
  * m_iSize : 큐에 들어온 데이터의 수
  * m_Front : pop을 수행할 위치(배열 인덱스)를 저장하는 변수
  * m_Rear : push을 수행 할 위치(배열 인덱스)를 저장하는 변수

* 생성자에서 Front와 Rear를 -1로 초기화합니다
  * push와 pop이 일어나는 순간 front나 rear에 +1을 한 후 그 위치에서 동작이 수행되도록 구현하였기때문입니다.
  * 배열의 첫번째 인덱스는 0이므로 -1에서 +1을 해주면 0의 위치에 맨처음 데이터가 들어가게됩니다.

##### push 함수 : 데이터를 삽입
```c
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
```

* 배열에 데이터를 추가해야하므로 배열이 가득 차 있으면 false를 반환합니다.

* Rear이 push할 위치를 알려주는데 circle구조이므로 나머지연산을 통해 반복적이고 순차적인 인덱스를 가지게 합니다.

* Rear 위치에 data를 넣어주고, 사이즈를 1증가시키며 true를 반환합니다.

##### pop 함수

```c
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
```
* Circle Queue이므로 나머지 연산(%)을 통해 인덱스(m_Front+1)가 사이즈 크기가 되는순간 0으로 초기화 됩니다.

* Queue에서 Front위치에 있는 data를 얻어온 후, 사이즈를 1 줄이고 그 data를 반환합니다.

##### front 함수 : 가장 먼저 내보내야 할 데이터 반환

```c
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
```

* pop과 거의 동일한 구조이며, 가장 먼저 출력되야할 데이터가 무엇인지를 반환합니다.

```c
void clear()
	{
		m_iSize = 0;
		m_Front = 0;
		m_Rear = 0;
	}
```

##### printQueue : Queue의 데이터를 출력하는 함수
```c
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
```
* 3가지 경우로 나뉩니다
  * empty : Size가 0인 경우
    * 큐가 비어있다는 메세지를 출력합니다.
  * front보다 rear가 큰경우
    * front부터 rear까지의 데이터를 출력합니다
  * rear보다 front가 큰경우 : circle queue기능에 의해 초기위치로 돌아옴
    * 0부터 rear까지 출력하고, front + 1부터 Size까지 출력합니다.
    
##### full 함수 : queue가 가득차있는지 체크하는 함수    
```c
bool full()		const
	{
		return m_iSize == SIZE;
	}
```

* m_iSize가 queue size와 같다면 가득 차있다는 의미이므로 true를 반환, 아니라면 false를 반환합니다


##### empty 함수 : queue가 비어있는지 체크하는 함수    
```c
	bool empty()	const
	{
		return m_iSize == 0;
	}
```

* m_iSize가 0이라면 추가된 데이터가 없다는 의미이므로 true를 반환, 아니면 false를 반환합니다.

##### size 함수 : 현재 queue size를 반환해줍니다.
```c
	int size()		const
	{
		return m_iSize;
	}
```
 
 ##### main
 
 ```c
 #include <iostream>
#include "CQueue.h"
#include "CCircleQueue.h"

using namespace std;

int main()
{
	CQueueList<int> Q;

	cout << "*****List Queue*****" << endl << endl;

	for (int i = 0; i < 10; i++)
	{
		Q.push(i);
	}
	Q.printQueue();

	cout << "Queue Pop [ ";
	for (int i = 0; i < 10; i++)
	{
		cout << Q.pop() << " ";
	}
	cout << "]" << endl << endl;
	Q.printQueue();

	cout << "*****Circle Queue*****" << endl << endl;

	CCircleQueue<int, 10> C_Q;

	for (int j = 0; j < 10; j++)
	{
		C_Q.push(j);
	}
	C_Q.printQueue();

	cout << endl << "Pop [ ";
	for (int j = 0; j < 5; j++)
	{
		cout << C_Q.pop() << " ";
	}
	cout << "]" << endl << endl;

	C_Q.printQueue();

	cout << "Push [ 10 11 12 13 14]" << endl << endl;
	for (int j = 10; j < 15; j++)
	{
		C_Q.push(j);
	}
	C_Q.printQueue();

	return 0;
}
 ```
 
 #### 결과
 
 <img src = "https://user-images.githubusercontent.com/47768726/59918687-6ee84d80-9460-11e9-900b-eba7baace3a3.JPG" width = "90%"></img>
 
