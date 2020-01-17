
#include <iostream>
#include <conio.h>
#include <time.h>

using namespace std;

/*
0 : ��
1 : ��
2 : ������
3 : ������
4 : ��ź
5 : ��ź�Ŀ�������
6 : ���б� ������
7 : ���� ������
8 : ��Ȧ
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
				cout << "��";
			}

			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "��";

			else if (Maze[i][j] == '0')
				cout << "��";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "��";
			else if (Maze[i][j] == '3')
				cout << "��";
			else if (Maze[i][j] == '5')
				cout << "��";
			else if (Maze[i][j] == '6')
				cout << "��";
			else if (Maze[i][j] == '7')
				cout << "��";
		}
		cout << endl;
	}

	cout << "��ź �Ŀ� : " << pPlayer->iBombPower << endl;
	cout << "�� ��� : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";

	cout << "���б� : ";
	if (pPlayer->bWallPush)
	{
		cout << "���� / ";
		if (pPlayer->bPushOnOff)
			cout << "ON" << endl;
		else
			cout << "OFF" << endl;
	}
	else
		cout << "�Ұ��� / OFF" << endl;
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
		//������ üũ�Ѵ�.
		if (maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' && 
			maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			--pPlayer->tPos.y;
		}

		//�� �бⰡ �����ϰ� �ٷ� ��ĭ�� ���� ���
		else if (pPlayer->bWallPush && maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '0')
		{
			//�� �бⰡ ON�� ���
			if (pPlayer->bPushOnOff)
			{
				//���� ��ĭ�� 0���� ũ�ų� ���� ��� �ε����� ����
				if (pPlayer->tPos.y - 2 >= 0) 
				{
					//���� ��ĭ�� ���̾�� �бⰡ ����. ������ Ȯ�� ��
					if (maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '1')
					{
						//���� ��ĭ�� ������ �����
						maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
						//�� ĭ�� ��� �����.
						maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
						//�÷��̾ �̵�
						--pPlayer->tPos.y;
					}

					//���� �ƴ� ���
					else if (pPlayer->bTransparency)
						--pPlayer->tPos.y;					
				}
			}

			//���б� ���� OFF�� ���
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
		//������ üũ�Ѵ�.
		if (maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' && 
			maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			++pPlayer->tPos.y;
		}

		//�� �бⰡ �����ϰ� �ٷ� ��ĭ�� ���� ���
		else if (pPlayer->bWallPush && maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] == '0')
		{
			//�� �бⰡ ON�� ���
			if (pPlayer->bPushOnOff)
			{
				//���� ��ĭ�� 0���� ũ�ų� ���� ��� �ε����� ����
				if (pPlayer->tPos.y + 2 < 20)
				{
					//���� ��ĭ�� ���̾�� �бⰡ ����. ������ Ȯ�� ��
					if (maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] == '1')
					{
						//���� ��ĭ�� ������ �����
						maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] = '0';
						//�� ĭ�� ��� �����.
						maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
						//�÷��̾ �̵�
						++pPlayer->tPos.y;
					}

					//���� �ƴ� ���
					else if (pPlayer->bTransparency)
						++pPlayer->tPos.y;
				}
			}

			//���б� ���� OFF�� ���
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
		//������ üũ�Ѵ�.
		if (maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' && 
			maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			++pPlayer->tPos.x;
		}

		//�� �бⰡ �����ϰ� �ٷ� ��ĭ�� ���� ���
		else if (pPlayer->bWallPush && maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] == '0')
		{
			//�� �бⰡ ON�� ���
			if (pPlayer->bPushOnOff)
			{
				//���� ��ĭ�� 0���� ũ�ų� ���� ��� �ε����� ����
				if (pPlayer->tPos.x + 2 < 20)
				{
					//���� ��ĭ�� ���̾�� �бⰡ ����. ������ Ȯ�� ��
					if (maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] == '1')
					{
						//���� ��ĭ�� ������ �����
						maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] = '0';
						//�� ĭ�� ��� �����.
						maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] = '1';
						//�÷��̾ �̵�
						++pPlayer->tPos.x;
					}

					//���� �ƴ� ���
					else if (pPlayer->bTransparency)
						++pPlayer->tPos.x;
				}
			}

			//���б� ���� OFF�� ���
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
		//������ üũ�Ѵ�.
		if (maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' &&
			maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}

		//�� �бⰡ �����ϰ� �ٷ� ��ĭ�� ���� ���
		else if (pPlayer->bWallPush && maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '0')
		{
			//�� �бⰡ ON�� ���
			if (pPlayer->bPushOnOff)
			{
				//���� ��ĭ�� 0���� ũ�ų� ���� ��� �ε����� ����
				if (pPlayer->tPos.x - 2 >= 0)
				{
					//���� ��ĭ�� ���̾�� �бⰡ ����. ������ Ȯ�� ��
					if (maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] == '1')
					{
						//���� ��ĭ�� ������ �����
						maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] = '0';
						//�� ĭ�� ��� �����.
						maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
						//�÷��̾ �̵�
						--pPlayer->tPos.x;
					}

					//���� �ƴ� ���
					else if (pPlayer->bTransparency)
						--pPlayer->tPos.x;
				}
			}

			//���б� ���� OFF�� ���
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
					//������ ��� Ȯ���� ���Ѵ�.
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

				//�÷��̾ ��ź�� �¾��� �� ���������� ������.
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

				//�÷��̾ ��ź�� �¾��� �� ���������� ������.
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

				//�÷��̾ ��ź�� �¾��� �� ���������� ������.
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

				//�÷��̾ ��ź�� �¾��� �� ���������� ������.
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

	//20 x 20 �̷θ� ������ش�.
	char strMaze[21][21] = {};

	PLAYER tPlayer = {};
	POINT tStartPos;
	POINT tEndPos;
	
	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT tBombPos[5];


	//�̷θ� �����Ѵ�.
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	//�̷θ� ����Ѵ�.

	while (true)
	{
		system("cls");


		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "�����߽��ϴ�." << endl;
			break;
		}

		cout << "t : ��ź ��ġ u : ��ź �Ͷ߸��� i : ���б� ON/OFF" << endl;
		cout << "w : �� a : ����  s : �Ʒ� d : ������ q : ����";
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