
#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

/*
0 : 벽
1 : 길
2 : 시작점
3 : 도착점
4 : 폭탄
5 : 폭탄파워아이템
6 : 벽밀기 아이템
7 : 투명 아이템
8 : 웜홀
*/

struct _tagPoint
{
	int x;
	int y;
};

typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagPlayer
{
	_tagPoint tPos;
	bool bWallPush;
	bool bPushOnOff;
	bool bTransparency;
	int iBombPower;
}PLAYER, *PPLAYER;

void SetMaze(char Maze[21][21], PPLAYER pPlayer , PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;

	strcpy_s(Maze[0],  "21100000000000000000");
	strcpy_s(Maze[1],  "00111111111000000000");
	strcpy_s(Maze[2],  "00100100001111111100");
	strcpy_s(Maze[3],  "01100100000000000100");
	strcpy_s(Maze[4],  "01000111100000000100");
	strcpy_s(Maze[5],  "01000100000000111100");
	strcpy_s(Maze[6],  "01001100000111100000");
	strcpy_s(Maze[7],  "00111000000100000000");
	strcpy_s(Maze[8],  "00100000111111000000");
	strcpy_s(Maze[9],  "00100001100001100000");
	strcpy_s(Maze[10], "00111111000000111110");
	strcpy_s(Maze[11], "00001001110000000010");
	strcpy_s(Maze[12], "00001000011110000010");
	strcpy_s(Maze[13], "00001000001100001110");
	strcpy_s(Maze[14], "00011000000111001000");
	strcpy_s(Maze[15], "00010000000001001100");
	strcpy_s(Maze[16], "00010000011111000110");
	strcpy_s(Maze[17], "00011110010000000000");
	strcpy_s(Maze[18], "01110000011111110000");
	strcpy_s(Maze[19], "11000000000000011113");	
}

void Output(char Maze[21][21], PPLAYER pPlayer)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (Maze[i][j] == '4') {
				cout << "♨";
			}

			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "☆";

			else if (Maze[i][j] == '0')
				cout << "■";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "★";
			else if (Maze[i][j] == '3')
				cout << "◎";
			else if (Maze[i][j] == '5')
				cout << "▲";
			else if (Maze[i][j] == '6')
				cout << "※";
			else if (Maze[i][j] == '7')
				cout << "♡";
		}
		cout << endl;
	}

	cout << "폭탄 파워 : " << pPlayer->iBombPower << endl;
	cout << "벽 통과 : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";

	cout << "벽밀기 : ";
	if (pPlayer->bWallPush)
	{
		cout << "가능 / ";
		if (pPlayer->bPushOnOff)
			cout << "ON" << endl;
		else
			cout << "OFF" << endl;
	}
	else
		cout << "불가능 / OFF" << endl;
}

bool AddItem(char cItemType, PPLAYER pPlayer)
{
	if (cItemType == '5') {
		if(pPlayer->iBombPower < 5)
			++pPlayer->iBombPower;
		return true;
	}
	else if (cItemType == '6') {
		pPlayer->bWallPush = true;
		pPlayer->bPushOnOff = true;
		return true;
	}
	else if (cItemType == '7') {
		pPlayer->bTransparency = true;
		return true;
	}
	return false;
}

void MoveUp(char maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y - 1 >= 0)
	{
		//벽인지 체크한다.
		if (maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' && 
			maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			--pPlayer->tPos.y;
		}

		//벽 밀기가 가능하고 바로 윗칸이 벽일 경우
		else if (pPlayer->bWallPush && maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '0')
		{
			//벽 밀기가 ON일 경우
			if (pPlayer->bPushOnOff)
			{
				//위의 위칸이 0보다 크거나 같을 경우 인덱스가 존재
				if (pPlayer->tPos.y - 2 >= 0) 
				{
					//위의 위칸이 길이어야 밀기가 가능. 길인지 확인 후
					if (maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '1')
					{
						//위의 위칸을 벽으로 만들고
						maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
						//위 칸을 길로 만든다.
						maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
						//플레이어를 이동
						--pPlayer->tPos.y;
					}

					//길이 아닐 경우
					else if (pPlayer->bTransparency)
						--pPlayer->tPos.y;					
				}
			}

			//벽밀기 상태 OFF일 경우
			else if (pPlayer->bTransparency)
				--pPlayer->tPos.y;
		}

		else if (pPlayer->bTransparency)
			--pPlayer->tPos.y;

		if (AddItem(maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
				maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveDown(char maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y + 1 < 20)
	{
		//벽인지 체크한다.
		if (maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' && 
			maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			++pPlayer->tPos.y;
		}

		//벽 밀기가 가능하고 바로 윗칸이 벽일 경우
		else if (pPlayer->bWallPush && maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] == '0')
		{
			//벽 밀기가 ON일 경우
			if (pPlayer->bPushOnOff)
			{
				//위의 위칸이 0보다 크거나 같을 경우 인덱스가 존재
				if (pPlayer->tPos.y + 2 < 20)
				{
					//위의 위칸이 길이어야 밀기가 가능. 길인지 확인 후
					if (maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] == '1')
					{
						//위의 위칸을 벽으로 만들고
						maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] = '0';
						//위 칸을 길로 만든다.
						maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
						//플레이어를 이동
						++pPlayer->tPos.y;
					}

					//길이 아닐 경우
					else if (pPlayer->bTransparency)
						++pPlayer->tPos.y;
				}
			}

			//벽밀기 상태 OFF일 경우
			else if (pPlayer->bTransparency)
				++pPlayer->tPos.y;
		}

		else if (pPlayer->bTransparency)
			++pPlayer->tPos.y;

		if (AddItem(maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveRight(char maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x + 1 < 20)
	{
		//벽인지 체크한다.
		if (maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' && 
			maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			++pPlayer->tPos.x;
		}

		//벽 밀기가 가능하고 바로 윗칸이 벽일 경우
		else if (pPlayer->bWallPush && maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] == '0')
		{
			//벽 밀기가 ON일 경우
			if (pPlayer->bPushOnOff)
			{
				//위의 위칸이 0보다 크거나 같을 경우 인덱스가 존재
				if (pPlayer->tPos.x + 2 < 20)
				{
					//위의 위칸이 길이어야 밀기가 가능. 길인지 확인 후
					if (maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] == '1')
					{
						//위의 위칸을 벽으로 만들고
						maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] = '0';
						//위 칸을 길로 만든다.
						maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] = '1';
						//플레이어를 이동
						++pPlayer->tPos.x;
					}

					//길이 아닐 경우
					else if (pPlayer->bTransparency)
						++pPlayer->tPos.x;
				}
			}

			//벽밀기 상태 OFF일 경우
			else if (pPlayer->bTransparency)
				++pPlayer->tPos.x;
		}


		else if (pPlayer->bTransparency)
			++pPlayer->tPos.x;

		if (AddItem(maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveLeft(char maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 >= 0)
	{
		//벽인지 체크한다.
		if (maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' &&
			maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}

		//벽 밀기가 가능하고 바로 윗칸이 벽일 경우
		else if (pPlayer->bWallPush && maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '0')
		{
			//벽 밀기가 ON일 경우
			if (pPlayer->bPushOnOff)
			{
				//위의 위칸이 0보다 크거나 같을 경우 인덱스가 존재
				if (pPlayer->tPos.x - 2 >= 0)
				{
					//위의 위칸이 길이어야 밀기가 가능. 길인지 확인 후
					if (maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] == '1')
					{
						//위의 위칸을 벽으로 만들고
						maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] = '0';
						//위 칸을 길로 만든다.
						maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
						//플레이어를 이동
						--pPlayer->tPos.x;
					}

					//길이 아닐 경우
					else if (pPlayer->bTransparency)
						--pPlayer->tPos.x;
				}
			}

			//벽밀기 상태 OFF일 경우
			else if (pPlayer->bTransparency)
				--pPlayer->tPos.x;
		}

		else if (pPlayer->bTransparency)
			--pPlayer->tPos.x;

		if (AddItem(maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MovePlayer(char maze[21][21], PPLAYER pPlayer, char cInput)
{
	switch (cInput)
	{
	case 'w':
	case 'W':
		MoveUp(maze, pPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(maze, pPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(maze, pPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(maze, pPlayer);
		break;
	}
}

void CreateBomb(char maze[21][21], const PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount)
{
	if (*pBombCount == 5)
		return;

	else if (maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
		return;

	for (int i = 0; i < *pBombCount; ++i)
	{
		if (pPlayer->tPos.x == pBombArr[i].x &&
			pPlayer->tPos.y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCount] = pPlayer->tPos;
	++(*pBombCount);

	maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void Fire(char maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount)
{
	for (int i = 0; i < *pBombCount; ++i)
	{
		maze[pBombArr[i].y][pBombArr[i].x] = '1';
		for (int j = 0; j <= pPlayer->iBombPower; ++j) {
			if (pBombArr[i].y - j >= 0)
			{
				if (maze[pBombArr[i].y - j][pBombArr[i].x] == '0') {
					//아이템 드랍 확률을 구한다.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
						{
							maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
						}
						else if (iPercent < 80)
						{
							maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
						}
						else
						{
							maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
						}
					}
					else
						maze[pBombArr[i].y - j][pBombArr[i].x] = '1';
				}

				//플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].y + j < 20)
			{
				if (maze[pBombArr[i].y + j][pBombArr[i].x] == '0') {
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
						{
							maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
						}
						else if (iPercent < 80)
						{
							maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
						}
						else
						{
							maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
						}
					}
					else
						maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
				}

				//플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x - j >= 0)
			{
				if (maze[pBombArr[i].y][pBombArr[i].x - j] == '0') {
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
						{
							maze[pBombArr[i].y][pBombArr[i].x - j] = '5';
						}
						else if (iPercent < 80)
						{
							maze[pBombArr[i].y][pBombArr[i].x - j] = '6';
						}
						else
						{
							maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
						}
					}
					else
						maze[pBombArr[i].y][pBombArr[i].x - j] = '1';
				}

				//플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x + 1 < 20)
			{
				if (maze[pBombArr[i].y][pBombArr[i].x + j] == '0') {					
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
						{
							maze[pBombArr[i].y][pBombArr[i].x + j] = '5';
						}
						else if (iPercent < 80)
						{
							maze[pBombArr[i].y][pBombArr[i].x + j] = '6';
						}
						else
						{
							maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
						}
					}
					else
						maze[pBombArr[i].y][pBombArr[i].x + j] = '1';
				}

				//플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
		}
	}
	*pBombCount = 0;
}

int main()
{
	srand((unsigned int)time(0));

	//20 x 20 미로를 만들어준다.
	char strMaze[21][21] = {};

	PLAYER tPlayer = {};
	POINT tStartPos;
	POINT tEndPos;
	
	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT tBombPos[5];


	//미로를 설정한다.
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	//미로를 출력한다.

	while (true)
	{
		system("cls");


		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "도착했습니다." << endl;
			break;
		}

		cout << "t : 폭탄 설치 u : 폭탄 터뜨리기 i : 벽밀기 ON/OFF" << endl;
		cout << "w : 위 a : 왼쪽  s : 아래 d : 오른쪽 q : 종료";
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		else if (cInput == 't' || cInput == 'T')
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);

		else if (cInput == 'u' || cInput == 'U')
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);

		else if (cInput == 'i' || cInput == 'I')
		{
			if (tPlayer.bWallPush)
				tPlayer.bPushOnOff = !tPlayer.bPushOnOff;
		}


		MovePlayer(strMaze, &tPlayer, cInput);
	}

	return 0;
}