
#include <iostream>
#include <time.h>

//console input output
//�ֿܼ����� ����� ��� �߰�
#include<conio.h>

using namespace std;

int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = {};

	for (int i = 0; i < 24; i++) {
		iNumber[i] = i + 1;
	}

	//������ ĭ�� ����. ���� ���� INT_MAX�� ���
	//INT_MAX�� �̹� ���ǵǾ��ִ� ���� int���� �ִ�ġ
	iNumber[24] = INT_MAX;

	//���� �ִ� ��ġ�� ������ ������ ������ش�
	int iStarIndex = 24;

	// 1 - 24���� ���ڸ� �����ش�
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
		// i for���� �������� �ǹ�
		for (int i = 0; i < 5; i++) {
			//j for���� ���� ĭ�� �ǹ��Ѵ�.
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
			cout << "���ڸ� ��� ������ϴ�." << endl;
			break;
		}

		cout << "w : �� s : �Ʒ� a: ���� d: ������ q : ���� \n";
		//���� 1�� �Է� enter���̵� ���ڸ� ������ ���� ��ȯ�ϰ� ����
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		switch (cInput) {
		case 'w':
		case 'W':
			//���� �ִ� ��ġ�� �ٷ� ���� �־��ش�
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
			//���� �ִ� ��ġ�� �ٷ� ���� �־��ش�
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
			//���� �ִ� ��ġ�� �ٷ� ���� �־��ش�
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
			//���� �ִ� ��ġ�� �ٷ� ���� �־��ش�
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

	cout << "������ �����մϴ�." << endl;

	return 0;

}