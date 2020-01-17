
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
		//player 빙고 숫자 넣기
		bingoNumber[i] = i + 1;

		//AI 빙고 숫자 넣기
		AIbingoNumber[i] = i + 1;
	}
	//빙고 숫자 섞기
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		//player 숫자 섞기
		idx1 = rand() % 25;
		idx2 = rand() % 25;
				
		iTemp = bingoNumber[idx1];
		bingoNumber[idx1] = bingoNumber[idx2];
		bingoNumber[idx2] = iTemp;

		//AI 숫자 섞기
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = AIbingoNumber[idx1];
		AIbingoNumber[idx1] = AIbingoNumber[idx2];
		AIbingoNumber[idx2] = iTemp;
	}

	int bingo_number = 0, AI_bingo_number = 0;
	int iAIMode;
	// AI 난이도를 선택한다.
	while (true) {
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "AI 모드를 선택하세요 : ";		
		cin >> iAIMode;

		if (iAIMode >= AI_EASY && iAIMode <= AI_HARD)
			break;
	}

	//선택안된 배열을 저장
	int iNoneSelect[25] = {};
	//카운트 숫자
	int iNoneSelectCount = 0;

	while (true) {
		system("cls");

		//player 빙고판 표시
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
		cout << "\n\n 현재 빙고 수 : " << bingo_number << endl << endl;

		//AI 빙고판 표시

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
		cout << "\n\n 현재 AI 빙고 수 : " << AI_bingo_number << endl << endl;

		int cInput;
		cout << "빙고 숫자를 써주세요(1 ~ 25)(0: 종료) : " << endl;
		cin >> cInput;
		if (cInput == 0) {
			cout << "게임을 종료합니다" << endl;
			break;
		}
		else if (cInput < 1 || cInput > 25)
			continue;
		//유저 숫자 바꾸기
		for (int i = 0; i < 25; i++) {
			if (bingoNumber[i] == cInput) {
				bingoNumber[i] = INT_MAX;
				break;
			}			
		}
		//AI 숫자 바꾸기
		for (int i = 0; i < 25; i++) {
			if (AIbingoNumber[i] == cInput) {
				AIbingoNumber[i] = INT_MAX;
				--iNoneSelectCount;
				break;
			}
		}

		//AI 선택 모드에따라 달라짐
		switch (iAIMode) {
		case AI_EASY:
			iNoneSelectCount = 0;
			//선택 안된 숫자목록을 만들어준다.
			for (int i = 0; i < 25; i++) {				
				if (AIbingoNumber[i] != INT_MAX) {
					iNoneSelect[iNoneSelectCount] = AIbingoNumber[i];
					iNoneSelectCount++;
				}
			}

			cInput = iNoneSelect[rand() % iNoneSelectCount];			
			break;

		case AI_HARD:
			//빙고 가능성이 제일 높은 줄 선택 그 줄에 있는 숫자중 하나 *로 만들어준다
			int iLine = 0;
			int iStarCount = 0;
			int iSaveCount = 0;

			//가로 중 *이많은 라인 찾아내기
			for (int i = 0; i < 5; i++) {
				iStarCount = 0;
				for (int j = 0; j < 5; j++) {					
					if (AIbingoNumber[i * 5 + j] == INT_MAX)
						iStarCount++;
				}

				//현재로 별이 가장많은 줄
				if (iStarCount < 5 && iSaveCount < iStarCount) {
					iLine = i;
					iSaveCount = iStarCount;
				}
			}

			//세로 중 *이 많은 라인 찾아내기 가로와 비교
			for (int i = 0; i < 5; i++) {
				iStarCount = 0;
				for (int j = 0; j < 5; j++) {					
					if (AIbingoNumber[j * 5 + i] == INT_MAX)
						iStarCount++;
				}

				//현재로 별이 가장많은 줄
				if (iStarCount < 5 && iSaveCount < iStarCount) {
					iLine = i + 5;
					iSaveCount = iStarCount;
				}
			}

			iStarCount = 0;
			//좌상단부터 우하단 대각 빙고 여부확인
			for (int i = 0; i < 25; i += 6) {
				if (bingoNumber[i] == INT_MAX)
					iStarCount++;
			}
			if (iStarCount < 5 && iSaveCount < iStarCount) {
				iLine = LN_LT;
				iSaveCount = iStarCount;
			}
			
			//우상단부터 좌하단 대각 빙고 여부확인
			for (int i = 4; i < 21; i += 4) {
				if (bingoNumber[i] == INT_MAX)
					iStarCount++;
			}
			if (iStarCount < 5 && iSaveCount < iStarCount) {
				iLine = LN_RT;
				iSaveCount = iStarCount;
			}

			// iLine에 줄번호 저장
			// 가로줄일 경우
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

		//유저 숫자 바꾸기
		for (int i = 0; i < 25; i++) {
			if (bingoNumber[i] == cInput) {
				bingoNumber[i] = INT_MAX;
				break;
			}
		}
		//AI 숫자 바꾸기
		for (int i = 0; i < 25; i++) {
			if (AIbingoNumber[i] == cInput) {
				AIbingoNumber[i] = INT_MAX;
				--iNoneSelectCount;
				break;
			}
		}

		//빙고 확인
		bingo_number = 0;
		AI_bingo_number = 0;
		int iStar1 = 0, iStar2 = 0;
		int iAIStar1 = 0, iAIStar2 = 0;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				//가로 빙고 여부 확인
				if (bingoNumber[i * 5 + j] == INT_MAX)
					iStar1++;
				//세로 빙고 여부 확인
				if (bingoNumber[j * 5 + i] == INT_MAX)
					iStar2++;
				// AI
				//가로 빙고 여부 확인
				if (AIbingoNumber[i * 5 + j] == INT_MAX)
					iAIStar1++;
				//세로 빙고 여부 확인
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
		//좌상단부터 우하단 대각 빙고 여부확인
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
		//우상단부터 좌하단 대각 빙고 여부확인
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