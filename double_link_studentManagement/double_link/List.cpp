
#include "List.h"

void InitList(PLIST pList)
{
	pList->iSize = 0;

	pList->pBegin = new NODE;
	pList->pEnd = new NODE;

	//���۳���� �������� ����������̴�
	pList->pBegin->pNext = pList->pEnd;
	//����������� �������� ���۳���̴�
	pList->pEnd->pPrev = pList->pBegin;

	//���۳���� ���� ���� ����
	pList->pBegin->pPrev = NULL;
	//����������� �������� ����.
	pList->pEnd->pNext = NULL;
}

void DestroyList(PLIST pList)
{
	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->iSize = 0;
	pList->pBegin = NULL;
	pList->pEnd = NULL;
}

void Push_Back(PLIST pList)
{
	system("cls");
	cout << "======================= �л� �߰� =======================" << endl;

	STUDENT tStudent = {};

	cout << "�̸� : ";
	InputString(tStudent.strName, NAME_SIZE);

	cout << "�й� : ";
	tStudent.iNumber = InputInt();

	cout << "���� : ";
	tStudent.iKor = InputInt();

	cout << "���� : ";
	tStudent.iEng = InputInt();

	cout << "���� : ";
	tStudent.iMath = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;

	PNODE pNode = new NODE;

	pNode->tStudent = tStudent;


	PNODE pPrev = pList->pEnd->pPrev;
	pPrev->pNext = pNode;
	pNode->pPrev = pPrev;

	pNode->pNext = pList->pEnd;
	pList->pEnd->pPrev = pNode;

	++pList->iSize;
}

void Push_Front(PLIST pList)
{
	system("cls");
	cout << "======================= �л� �߰� =======================" << endl;

	STUDENT tStudent = {};

	cout << "�̸� : ";
	InputString(tStudent.strName, NAME_SIZE);

	cout << "�й� : ";
	tStudent.iNumber = InputInt();

	cout << "���� : ";
	tStudent.iKor = InputInt();

	cout << "���� : ";
	tStudent.iEng = InputInt();

	cout << "���� : ";
	tStudent.iMath = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;

	PNODE pNode = new NODE;

	pNode->tStudent = tStudent;


	PNODE pNext = pList->pBegin->pNext;
	pNext->pPrev = pNode;
	pNode->pNext = pNext;

	pNode->pPrev = pList->pBegin;
	pList->pBegin->pNext = pNode;

	++pList->iSize;

}


void OutputStudent(const PSTUDENT pStudent)
{
	cout << "�̸� : " << pStudent->strName << "\t�й� : " << pStudent->iNumber << endl;
	cout << "���� : " << pStudent->iKor << "\t���� : " << pStudent->iEng << endl;
	cout << "���� : " << pStudent->iMath << endl;
	cout << "���� : " << pStudent->iTotal << "\t��� : " << pStudent->fAvg << endl << endl;
}

void OutputList(PLIST pList)
{
	int iMenu;
	while (true)
	{
		system("cls");
		cout << "======================= �л� ��� =======================" << endl;
		cout << "1. ������ ���" << endl;
		cout << "2. ������ ���" << endl;
		cout << "�޴��� �����ϼ���.";
		iMenu = InputInt();

		if (iMenu > OT_NONE || iMenu <= OT_INVERSE)
			break;
	}

	PNODE pNode = NULL;

	switch (iMenu)
	{
	case OT_OUTPUT:
		pNode = pList->pBegin->pNext;

		while (pNode != pList->pEnd)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pNext;
		}
		break;
	case OT_INVERSE:
		pNode = pList->pEnd->pPrev;

		while (pNode != pList->pBegin)
		{
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pPrev;
		}
		break;
	}

	cout << "�л� �� : " << pList->iSize << endl;
	system("pause");
}

void Search(PLIST pList)
{
	system("cls");
	cout << "======================= �л� �˻� =======================" << endl;

	cout << "�˻��� �̸��� �Է��ϼ��� : ";
	char	strName[NAME_SIZE];
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin->pNext;

	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			OutputStudent(&pNode->tStudent);
			system("pause");
			return;
		}

		pNode = pNode->pNext;
	}

	cout << "ã�� �л��� �����ϴ�." << endl;
	system("pause");
}

void Delete(PLIST pList)
{
	system("cls");
	cout << "======================= �л� ���� =======================" << endl;

	cout << "������ �̸��� �Է��ϼ��� : ";
	char	strName[NAME_SIZE];
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin->pNext;

	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			cout << strName << "�л� ����" << endl;

			pNode->pPrev->pNext = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;
			delete pNode;

			cout << strName << "�л� ���� �Ϸ�" << endl;
			--pList->iSize;
			system("pause");
			return;
		}
		//�ش� �л��� �ƴ϶�� ���� ��尡 ���� ��尡 �ȴ�.
		pNode = pNode->pNext;
	}

	cout << "������ �л��� ã�� �� �����ϴ�. " << endl;
	system("pause");
}

void Sort(PLIST pList)
{
	int iMenu;
	while (true)
	{
		system("cls");
		cout << "======================= �л� ���� =======================" << endl;
		cout << "1. �й���" << endl;
		cout << "2. ��ռ�" << endl;
		cout << "�޴��� �����ϼ���.";
		iMenu = InputInt();

		if (iMenu > ST_NONE || iMenu <= ST_AVG)
			break;
	}

	int iOption;
	while (true)
	{
		cout << "1. ��������" << endl;
		cout << "2. ��������" << endl;
		cout << "�޴��� �����ϼ���.";
		iOption = InputInt();

		if (iOption > SO_NONE || iOption <= SO_DESCREIVE)
			break;
	}

	PNODE pFirst = pList->pBegin->pNext;
	PNODE pSecond = pFirst->pNext;
		
	while (pFirst != pList->pEnd->pPrev)
	{
		pSecond = pFirst->pNext;

		while (pSecond != pList->pEnd)
		{
			bool bSwap = false;

			switch (iMenu)
			{
			case ST_NUMBER:
				switch (iOption)
				{
				case SO_CREIVE:
					if (pFirst->tStudent.iNumber > pSecond->tStudent.iNumber)
						bSwap = true;
					break;
				case SO_DESCREIVE:
					if (pFirst->tStudent.iNumber < pSecond->tStudent.iNumber)
						bSwap = true;
					break;
				}
				break;
			case ST_AVG:
				switch (iOption)
				{
				case SO_CREIVE:
					if (pFirst->tStudent.fAvg > pSecond->tStudent.fAvg)
						bSwap = true;
					break;
				case SO_DESCREIVE:
					if (pFirst->tStudent.fAvg < pSecond->tStudent.fAvg)
						bSwap = true;
					break;
				}
				break;
			}

			if (bSwap)
			{
				PNODE pFirstPrev = pFirst->pPrev;
				PNODE pFirstNext = pFirst->pNext;

				PNODE pSecondPrev = pSecond->pPrev;
				PNODE pSecondNext = pSecond->pNext;

				pFirstPrev->pNext = pSecond;
				pSecond->pPrev = pFirstPrev;

				if (pSecond != pFirst->pNext)
				{
					pFirstNext->pPrev = pSecond;
					pSecond->pNext = pFirstNext;

					pSecondPrev->pNext = pFirst;
					pFirst->pPrev = pSecondPrev;
				}
				else
				{
					pSecond->pNext = pFirst;
					pFirst->pPrev = pSecond;
				}
				pSecondNext->pPrev = pFirst;
				pFirst->pNext = pSecondNext;

				PNODE pTemp = pFirst;
				pFirst = pSecond;
				pSecond = pTemp;

			}

			pSecond = pSecond->pNext;
		}

		pFirst = pFirst->pNext;
	}

	cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
	system("pause");

}

