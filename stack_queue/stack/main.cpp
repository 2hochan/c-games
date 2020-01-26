
#include <iostream>
#include "stack.h"
#include "Queue.h"

using namespace std;

int main()
{
	CStack<int> stackInt;

	for (int i = 0; i < 100; ++i)
	{
		stackInt.push(i + 1);
	}

	while (!stackInt.empty())
	{
		cout << stackInt.pop() << endl;
	}

	cout << "=============== Queue Test ================" << endl;

	CQueue<int> queueInt;

	for (int i = 0; i < 100; ++i)
	{
		queueInt.push(i + 1);
	}

	while (!queueInt.empty())
	{
		cout << queueInt.pop() << endl;
	}

	CCircleQueue<int, 15> queue1;

	for (int i = 0; i < 10; ++i)
	{
		queue1.push(i + 1);
	}

	cout << "3개 pop" << endl;
	for (int i = 0; i < 3; ++i)
	{
		cout << queue1.pop() << endl;
	}

	cout << "4개 push" << endl;
	for (int i = 0; i < 4; ++i)
	{
		queue1.push(i + 1);
	}

	cout << "전부 pop" << endl;
	while (!queue1.empty())
	{
		cout << queue1.pop() << endl;
	}

	return 0;
}