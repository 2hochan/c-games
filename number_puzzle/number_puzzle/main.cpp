
#include <iostream>
#include <time.h>

//console input output
//콘솔에서의 입출력 기능 추가
#include<conio.h>

using namespace std;

int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = {};

	for (int i = 0; i < 24; i++) {
		iNumber[i] = i + 1;
	}

	//마지막 칸은 공백. 공백 값은 INT_MAX로 사용
	//INT_MAX는 이미 정의되어있는 숫자 int값의 최대치
	iNumber[24] = INT_MAX;

	//별이 있는 위치를 저장할 변수를 만들어준다
	int iStarIndex = 24;

	// 1 - 24까지 숫자만 섞어준다
	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}
	while (true) {
		system("cls");
		// i for문이 세로줄을 의미
		for (int i = 0; i < 5; i++) {
			//j for문이 가로 칸을 의미한다.
			for (int j = 0; j < 5; j++) {
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}

		bool bWin = true;

		for (int i = 0; i < 24; i++) {
			if (iNumber[i] != i + 1) {
				bWin = false;
				break;
			}
		}

		if (bWin == true) {
			cout << "숫자를 모두 맞췄습니다." << endl;
			break;
		}

		cout << "w : 위 s : 아래 a: 왼쪽 d: 오른쪽 q : 종료 \n";
		//문자 1개 입력 enter없이도 문자를 누르는 순간 반환하고 종료
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		switch (cInput) {
		case 'w':
		case 'W':
			//별이 있는 위치에 바로 값을 넣어준다
			if (iStarIndex >= 5) {
				iNumber[iStarIndex] = iNumber[iStarIndex - 5];
				iNumber[iStarIndex - 5] = INT_MAX;
				iStarIndex -= 5;
			}
			else {
				iNumber[iStarIndex] = iNumber[iStarIndex + 20];
				iNumber[iStarIndex + 20] = INT_MAX;
				iStarIndex += 20;
			}
			break;
		case 's':
		case 'S':
			//별이 있는 위치에 바로 값을 넣어준다
			if (iStarIndex < 20) {
				iNumber[iStarIndex] = iNumber[iStarIndex + 5];
				iNumber[iStarIndex + 5] = INT_MAX;
				iStarIndex += 5;
			}
			else {
				iNumber[iStarIndex] = iNumber[iStarIndex - 20];
				iNumber[iStarIndex - 20] = INT_MAX;
				iStarIndex -= 20;
			}
			break;
		case 'a':
		case 'A':
			//별이 있는 위치에 바로 값을 넣어준다
			if (iStarIndex % 5 > 0) {
				iNumber[iStarIndex] = iNumber[iStarIndex - 1];
				iNumber[iStarIndex - 1] = INT_MAX;
				iStarIndex -= 1;
			}
			else {
				iNumber[iStarIndex] = iNumber[iStarIndex + 4];
				iNumber[iStarIndex + 4] = INT_MAX;
				iStarIndex += 4;
			}
			break;
			break;
		case 'd':
		case 'D':
			//별이 있는 위치에 바로 값을 넣어준다
			if (iStarIndex % 5 < 4) {
				iNumber[iStarIndex] = iNumber[iStarIndex + 1];
				iNumber[iStarIndex + 1] = INT_MAX;
				iStarIndex += 1;
			}
			else {
				iNumber[iStarIndex] = iNumber[iStarIndex - 4];
				iNumber[iStarIndex - 4] = INT_MAX;
				iStarIndex -= 4;
			}
			break;
		}

	}

	cout << "게임을 종료합니다." << endl;

	return 0;

}