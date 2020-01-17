
#include "List.h"

void InitList(PLIST pList)
{
	pList->iSize = 0;

	pList->pBegin = new NODE;
	pList->pEnd = new NODE;

	//시작노드의 다음노드는 마지막노드이다
	pList->pBegin->pNext = pList->pEnd;
	//마지막노드의 이전노드는 시작노드이다
	pList->pEnd->pPrev = pList->pBegin;

	//시작노드의 이전 노드는 없다
	pList->pBegin->pPrev = NULL;
	//마지막노드의 다음노드는 없다.
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
	cout << "======================= 학생 추가 =======================" << endl;

	STUDENT tStudent = {};

	cout << "이름 : ";
	InputString(tStudent.strName, NAME_SIZE);

	cout << "학번 : ";
	tStudent.iNumber = InputInt();

	cout << "국어 : ";
	tStudent.iKor = InputInt();

	cout << "영어 : ";
	tStudent.iEng = InputInt();

	cout << "수학 : ";
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
	cout << "======================= 학생 추가 =======================" << endl;

	STUDENT tStudent = {};

	cout << "이름 : ";
	InputString(tStudent.strName, NAME_SIZE);

	cout << "학번 : ";
	tStudent.iNumber = InputInt();

	cout << "국어 : ";
	tStudent.iKor = InputInt();

	cout << "영어 : ";
	tStudent.iEng = InputInt();

	cout << "수학 : ";
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
	cout << "이름 : " << pStudent->strName << "\t학번 : " << pStudent->iNumber << endl;
	cout << "국어 : " << pStudent->iKor << "\t영어 : " << pStudent->iEng << endl;
	cout << "수학 : " << pStudent->iMath << endl;
	cout << "총점 : " << pStudent->iTotal << "\t평균 : " << pStudent->fAvg << endl << endl;
}

void OutputList(PLIST pList)
{
	int iMenu;
	while (true)
	{
		system("cls");
		cout << "======================= 학생 출력 =======================" << endl;
		cout << "1. 정방향 출력" << endl;
		cout << "2. 역방향 출력" << endl;
		cout << "메뉴를 선택하세요.";
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

	cout << "학생 수 : " << pList->iSize << endl;
	system("pause");
}

void Search(PLIST pList)
{
	system("cls");
	cout << "======================= 학생 검색 =======================" << endl;

	cout << "검색할 이름을 입력하세요 : ";
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

	cout << "찾는 학생이 없습니다." << endl;
	system("pause");
}

void Delete(PLIST pList)
{
	system("cls");
	cout << "======================= 학생 삭제 =======================" << endl;

	cout << "삭제할 이름을 입력하세요 : ";
	char	strName[NAME_SIZE];
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin->pNext;

	while (pNode != pList->pEnd)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			cout << strName << "학생 삭제" << endl;

			pNode->pPrev->pNext = pNode->pNext;
			pNode->pNext->pPrev = pNode->pPrev;
			delete pNode;

			cout << strName << "학생 삭제 완료" << endl;
			--pList->iSize;
			system("pause");
			return;
		}
		//해당 학생이 아니라면 현재 노드가 이전 노드가 된다.
		pNode = pNode->pNext;
	}

	cout << "삭제할 학생을 찾을 수 없습니다. " << endl;
	system("pause");
}

void Sort(PLIST pList)
{
	int iMenu;
	while (true)
	{
		system("cls");
		cout << "======================= 학생 정렬 =======================" << endl;
		cout << "1. 학번순" << endl;
		cout << "2. 평균순" << endl;
		cout << "메뉴를 선택하세요.";
		iMenu = InputInt();

		if (iMenu > ST_NONE || iMenu <= ST_AVG)
			break;
	}

	int iOption;
	while (true)
	{
		cout << "1. 오름차순" << endl;
		cout << "2. 내림차순" << endl;
		cout << "메뉴를 선택하세요.";
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

	cout << "정렬이 완료되었습니다." << endl;
	system("pause");

}

