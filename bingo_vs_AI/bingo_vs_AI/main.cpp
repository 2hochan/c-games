
#include <iostream>
#include <time.h>

using namespace std;

enum AI_MODE {
	AI_EASY = 1,
	AI_HARD
};

enum LINE_NUMBER {
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	LN_LT,
	LN_RT
};

int main() {

	int bingoNumber[25] = {};
	int AIbingoNumber[25] = {};

	

	srand((unsigned int)time(0));

	
	for (int i = 0; i < 25; i++) {
		//player ���� ���� �ֱ�
		bingoNumber[i] = i + 1;

		//AI ���� ���� �ֱ�
		AIbingoNumber[i] = i + 1;
	}
	//���� ���� ����
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		//player ���� ����
		idx1 = rand() % 25;
		idx2 = rand() % 25;
				
		iTemp = bingoNumber[idx1];
		bingoNumber[idx1] = bingoNumber[idx2];
		bingoNumber[idx2] = iTemp;

		//AI ���� ����
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = AIbingoNumber[idx1];
		AIbingoNumber[idx1] = AIbingoNumber[idx2];
		AIbingoNumber[idx2] = iTemp;
	}

	int bingo_number = 0, AI_bingo_number = 0;
	int iAIMode;
	// AI ���̵��� �����Ѵ�.
	while (true) {
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "AI ��带 �����ϼ��� : ";		
		cin >> iAIMode;

		if (iAIMode >= AI_EASY && iAIMode <= AI_HARD)
			break;
	}

	//���þȵ� �迭�� ����
	int iNoneSelect[25] = {};
	//ī��Ʈ ����
	int iNoneSelectCount = 0;

	while (true) {
		system("cls");

		//player ������ ǥ��
		cout << "============  PLAYER  ============" << endl << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (bingoNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << bingoNumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}
		cout << "\n\n ���� ���� �� : " << bingo_number << endl << endl;

		//AI ������ ǥ��

		cout << "============    AI    ============" << endl << endl;

		switch (iAIMode) {
			case AI_EASY:
				cout << "AI Mode : Easy" << endl;
				break;
			case AI_HARD:
				cout << "AI Mode : Hard" << endl;
				break;
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (AIbingoNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << AIbingoNumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}
		cout << "\n\n ���� AI ���� �� : " << AI_bingo_number << endl << endl;

		int cInput;
		cout << "���� ���ڸ� ���ּ���(1 ~ 25)(0: ����) : " << endl;
		cin >> cInput;
		if (cInput == 0) {
			cout << "������ �����մϴ�" << endl;
			break;
		}
		else if (cInput < 1 || cInput > 25)
			continue;
		//���� ���� �ٲٱ�
		for (int i = 0; i < 25; i++) {
			if (bingoNumber[i] == cInput) {
				bingoNumber[i] = INT_MAX;
				break;
			}			
		}
		//AI ���� �ٲٱ�
		for (int i = 0; i < 25; i++) {
			if (AIbingoNumber[i] == cInput) {
				AIbingoNumber[i] = INT_MAX;
				--iNoneSelectCount;
				break;
			}
		}

		//AI ���� ��忡���� �޶���
		switch (iAIMode) {
		case AI_EASY:
			iNoneSelectCount = 0;
			//���� �ȵ� ���ڸ���� ������ش�.
			for (int i = 0; i < 25; i++) {				
				if (AIbingoNumber[i] != INT_MAX) {
					iNoneSelect[iNoneSelectCount] = AIbingoNumber[i];
					iNoneSelectCount++;
				}
			}

			cInput = iNoneSelect[rand() % iNoneSelectCount];			
			break;

		case AI_HARD:
			//���� ���ɼ��� ���� ���� �� ���� �� �ٿ� �ִ� ������ �ϳ� *�� ������ش�
			int iLine = 0;
			int iStarCount = 0;
			int iSaveCount = 0;

			//���� �� *�̸��� ���� ã�Ƴ���
			for (int i = 0; i < 5; i++) {
				iStarCount = 0;
				for (int j = 0; j < 5; j++) {					
					if (AIbingoNumber[i * 5 + j] == INT_MAX)
						iStarCount++;
				}

				//����� ���� ���帹�� ��
				if (iStarCount < 5 && iSaveCount < iStarCount) {
					iLine = i;
					iSaveCount = iStarCount;
				}
			}

			//���� �� *�� ���� ���� ã�Ƴ��� ���ο� ��
			for (int i = 0; i < 5; i++) {
				iStarCount = 0;
				for (int j = 0; j < 5; j++) {					
					if (AIbingoNumber[j * 5 + i] == INT_MAX)
						iStarCount++;
				}

				//����� ���� ���帹�� ��
				if (iStarCount < 5 && iSaveCount < iStarCount) {
					iLine = i + 5;
					iSaveCount = iStarCount;
				}
			}

			iStarCount = 0;
			//�»�ܺ��� ���ϴ� �밢 ���� ����Ȯ��
			for (int i = 0; i < 25; i += 6) {
				if (bingoNumber[i] == INT_MAX)
					iStarCount++;
			}
			if (iStarCount < 5 && iSaveCount < iStarCount) {
				iLine = LN_LT;
				iSaveCount = iStarCount;
			}
			
			//���ܺ��� ���ϴ� �밢 ���� ����Ȯ��
			for (int i = 4; i < 21; i += 4) {
				if (bingoNumber[i] == INT_MAX)
					iStarCount++;
			}
			if (iStarCount < 5 && iSaveCount < iStarCount) {
				iLine = LN_RT;
				iSaveCount = iStarCount;
			}

			// iLine�� �ٹ�ȣ ����
			// �������� ���
			if (iLine <= LN_H5) {
				for (int i = 0; i < 5; i++) {
					if (AIbingoNumber[iLine * 5 + i] != INT_MAX) {
						cInput = AIbingoNumber[iLine * 5 + i];
						break;
					}
				}
			}

			else if (iLine <= LN_V5) {
				for (int i = 0; i < 5; i++) {
					if (AIbingoNumber[i * 5 + (iLine - 5)] != INT_MAX) {
						cInput = AIbingoNumber[i * 5 + (iLine - 5)];
						break;
					}
				}
			}

			else if (iLine == LN_LT) {
				for (int i = 0; i < 25; i += 6) {
					if (AIbingoNumber[i] != INT_MAX) {
						cInput = AIbingoNumber[i];
						break;
					}
				}
			}

			else if (iLine == LN_RT) {
				for (int i = 4; i <= 20; i += 4) {
					if (AIbingoNumber[i] != INT_MAX) {
						cInput = AIbingoNumber[i];
						break;
					}
				}
			}
			break;
		}

		//���� ���� �ٲٱ�
		for (int i = 0; i < 25; i++) {
			if (bingoNumber[i] == cInput) {
				bingoNumber[i] = INT_MAX;
				break;
			}
		}
		//AI ���� �ٲٱ�
		for (int i = 0; i < 25; i++) {
			if (AIbingoNumber[i] == cInput) {
				AIbingoNumber[i] = INT_MAX;
				--iNoneSelectCount;
				break;
			}
		}

		//���� Ȯ��
		bingo_number = 0;
		AI_bingo_number = 0;
		int iStar1 = 0, iStar2 = 0;
		int iAIStar1 = 0, iAIStar2 = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				//���� ���� ���� Ȯ��
				if (bingoNumber[i * 5 + j] == INT_MAX)
					iStar1++;
				//���� ���� ���� Ȯ��
				if (bingoNumber[j * 5 + i] == INT_MAX)
					iStar2++;
				// AI
				//���� ���� ���� Ȯ��
				if (AIbingoNumber[i * 5 + j] == INT_MAX)
					iAIStar1++;
				//���� ���� ���� Ȯ��
				if (AIbingoNumber[j * 5 + i] == INT_MAX)
					iAIStar2++;
			}
			if (iStar1 == 5 || iStar2 == 5)
				bingo_number++;
			if (iAIStar1 == 5 || iAIStar2 == 5)
				AI_bingo_number++;
			iStar1 = iStar2 = 0;
			iAIStar1 = iAIStar2 = 0;
		}
		//�»�ܺ��� ���ϴ� �밢 ���� ����Ȯ��
		for (int i = 0; i < 25; i += 6) {
			if (bingoNumber[i] == INT_MAX)
				iStar1++;
			if (AIbingoNumber[i] == INT_MAX)
				iAIStar1++;
		}
		if (iStar1 == 5)
			bingo_number++;
		if (iAIStar1 == 5)
			AI_bingo_number++;
		//���ܺ��� ���ϴ� �밢 ���� ����Ȯ��
		for (int i = 4; i < 21; i += 4) {
			if (bingoNumber[i] == INT_MAX)
				iStar2++;
			if (AIbingoNumber[i] == INT_MAX)
				iAIStar2++;
		}
		if (iAIStar2 == 5)
			AI_bingo_number++;


		if (bingo_number >= 5) {
			cout << "\n\nPLAYER WIN\n\n" << endl;
			break;
		}
		if (AI_bingo_number >= 5) {
			cout << "\n\nAI WIN\n\n" << endl;
			break;
		}
		
	}
	return 0;
}