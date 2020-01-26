
#include <iostream>
#include "Vector.h"

using namespace std;

int main()
{
	CVector<int>	vecInt;

	vecInt.reserve(100);

	for (int i = 0; i < 100; ++i)
	{
		vecInt.push_back(i + 1);
	}

	for (int i = 0; i < vecInt.size(); ++i)
	{
		cout << vecInt[i] << endl;
	}

	cout << "========= iterator test ==========" << endl;
	CVector<int>::iterator iter;
	for (iter = vecInt.begin(); iter != vecInt.end(); ++iter)
	{
		cout << *iter << endl;
	}
	return 0;
}