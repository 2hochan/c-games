
#include <iostream>
#include <time.h>

using namespace std;

#define NAME_SIZE			32
#define ITEM_DESC_LENGTH	512
#define INVENTORY_MAX		20
#define STORE_WEAPON_MAX	3
#define STORE_ARMOR_MAX		3
#define LEVEL_MAX			10

enum GAME_MODE {
	GM_NONE,
	GM_NEW,
	GM_LOAD,
	GM_END
};

enum MAIN_MENU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_TYPE {
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB {
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum EQUIP {
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

enum BATTLE {
	BT_NONE,
	BT_ATTACK,
	BT_RUN,
};

enum STORE_MENU {
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};


struct _tagItem {
	char	strName[NAME_SIZE];
	char	strTypeName[NAME_SIZE];
	ITEM_TYPE eType;
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory {
	_tagItem	tItem[INVENTORY_MAX];
	int			iItemCount;
	int			iGold;
};

struct _tagPlayer {
	char	strName[NAME_SIZE];
	char	strJobName[NAME_SIZE];
	JOB		eJOB;
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iLevel;
	_tagItem	tEquip[EQ_MAX];
	bool		bEquip[EQ_MAX];
	_tagInventory tInventory;
};


struct _tagMonster {
	char	strName[NAME_SIZE];
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iExp;
	int		iGoldMin;
	int		iGoldMax;
};

struct _tagLevelUpStatus {
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHPMin;
	int iMPMin;
	int iHPMax;
	int iMPMax;
};

const int g_iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000, 200000, 400000 };
_tagLevelUpStatus g_tLvUpTable[JOB_END - 1] = {};


//숫자입력을 받는다.
//입력오류를 처리해주며 INT_MAX가 리턴되면 오류가 발생한 경우이다.
int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return iInput;
}

//메뉴를 화면에 보여주고 입력받은 메뉴를 리턴해준다.
//입력오류일경우 MM_NONE을 리턴해준다.
int OutputMainMenu()
{
	system("cls");
	cout << "*********************** 로비 ***********************" << endl;
	cout << "1. 맵" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 가방" << endl;
	cout << "4. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT)
		return MM_NONE;
	return iMenu;
}

int OutputMapMenu()
{
	system("cls");
	cout << "*********************** 맵 ***********************" << endl;
	cout << "1. 쉬움" << endl;
	cout << "2. 보통" << endl;
	cout << "3. 어려움" << endl;
	cout << "4. 뒤로가기" << endl;
	cout << "맵을 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MT_NONE || iMenu > MT_BACK)
		return MT_NONE;
	return iMenu;
}

int OutputBattleMenu()
{
	cout << "1. 공격" << endl;
	cout << "2. 도망가기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= BT_NONE || iMenu > BT_RUN)
		return BT_NONE;
	return iMenu;
}

void OutputBattleTag(int iMenu)
{
	switch (iMenu) {
	case MT_EASY:
		system("cls");
		cout << "*********************** 쉬움 ***********************" << endl;
		break;
	case MT_NORMAL:
		system("cls");
		cout << "*********************** 보통 ***********************" << endl;
		break;
	case MT_HARD:
		system("cls");
		cout << "*********************** 어려움 ***********************" << endl;
		break;
	}
}

void OutputPlayer(_tagPlayer* pPlayer)
{
	//플레이어 정보를 출력한다.
	cout << "============================ Player ============================" << endl;
	cout << "이름 : " << pPlayer->strName << "\t직업 : " << pPlayer->strJobName << endl;
	cout << "레벨 : " << pPlayer->iLevel << "\t경험치 : " << pPlayer->iExp << " / " << g_iLevelUpExp[pPlayer->iLevel - 1] << endl;

	//무기를 장착하고 있을 경우 무기 공격력을 추가해서 보여준다.
	if (pPlayer->bEquip[EQ_WEAPON] == true) {
		cout << "공격력 : " << pPlayer->iAttackMin << " + " << pPlayer->tEquip[EQ_WEAPON].iMin << " - " << pPlayer->iAttackMax << " + " << pPlayer->tEquip[EQ_WEAPON].iMax;
	}
	else
		cout << "공격력 : " << pPlayer->iAttackMin << " - " << pPlayer->iAttackMax;

	//방어구를 장착하고 있을 경우 방어구 방어력을 추가해서 출력한다. 
	if (pPlayer->bEquip[EQ_ARMOR] == true) {
		cout << "\t방어력 : " << pPlayer->iArmorMin << " + " << pPlayer->tEquip[EQ_ARMOR].iMin << " - " << pPlayer->iArmorMax << " + " << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
	}
	else
		cout << "\t방어력 : " << pPlayer->iArmorMin << " - " << pPlayer->iArmorMax << endl;

	cout << "체력 : " << pPlayer->iHP << " / " << pPlayer->iHPMax << "\t마나 : " << pPlayer->iMP << " / " << pPlayer->iMPMax << endl;
	cout << "보유 골드 : " << pPlayer->tInventory.iGold << "Gold" << endl << endl;
}

void OutputMonster(_tagMonster* pMonster)
{
	//몬스터 정보를 출력
	cout << "============================ Monster ============================" << endl;
	cout << "이름 : " << pMonster->strName << "\t레벨 : " << pMonster->iLevel << endl;
	cout << "공격력 : " << pMonster->iAttackMin << " - " << pMonster->iAttackMax << "\t방어력 : " << pMonster->iArmorMin << " - " << pMonster->iArmorMax << endl;
	cout << "체력 : " << pMonster->iHP << " / " << pMonster->iHPMax << "\t마나 : " << pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "획득 경험치 : " << pMonster->iExp << "\t획득 골드 : " << pMonster->iGoldMin << " - " << pMonster->iGoldMax << endl << endl;
}

_tagLevelUpStatus CreateLvUpStatus(int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax, int iHPMin, int iHPMax,
	int iMPMin, int iMPMax)
{
	_tagLevelUpStatus tStatus = {};

	tStatus.iAttackMin = iAttackMin;
	tStatus.iAttackMax = iAttackMax;
	tStatus.iArmorMin = iArmorMin;
	tStatus.iArmorMax = iArmorMax;
	tStatus.iHPMin = iHPMin;
	tStatus.iHPMax = iHPMax;
	tStatus.iMPMin = iMPMin;
	tStatus.iMPMax = iMPMax;

	return tStatus;
}

void Battle(_tagPlayer* pPlayer, _tagMonster* pMonster)
{
	int iAttackMin = pPlayer->iAttackMin;
	int iAttackMax = pPlayer->iAttackMax;

	//무기를 장착하고 있을 경우 무기 공격력을 추가해준다.
	if (pPlayer->bEquip[EQ_WEAPON]) {
		iAttackMin += pPlayer->tEquip[EQ_WEAPON].iMin;
		iAttackMax += pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	int iAttack = rand() % (iAttackMax - iAttackMin + 1) + iAttackMin;
	int iArmor = rand() % (pMonster->iArmorMax - pMonster->iArmorMin + 1) + pMonster->iArmorMin;

	int iDamage = iAttack - iArmor;
	iDamage = iDamage < 1 ? 1 : iDamage;

	//몬스터 HP를 감소시킨다.
	pMonster->iHP -= iDamage;

	cout << pPlayer->strName << "가 " << pMonster->strName << "에게 " << iDamage << " 피해를 입혔습니다." << endl;

	//몬스터가 죽었을 경우를 처리한다.
	if (pMonster->iHP <= 0) {
		cout << pMonster->strName << " 몬스터가 사망하였습니다." << endl;

		pPlayer->iExp += pMonster->iExp;
		int iGold = (rand() % pMonster->iGoldMax - pMonster->iGoldMin + 1) + pMonster->iGoldMin;
		pPlayer->tInventory.iGold += iGold;

		cout << pMonster->iExp << "경험치를 획득하였습니다." << endl;
		cout << iGold << " Gold를 획득하였습니다." << endl;

		pMonster->iHP = pMonster->iHPMax;
		pMonster->iMP = pMonster->iMPMax;


		//레벨업을 했는지 체크해본다
		if (pPlayer->iExp >= g_iLevelUpExp[pPlayer->iLevel - 1]) {
			//플레이어 경험치를 레벨업에 필요한 경험치만큼 차감한다.
			pPlayer->iExp -= g_iLevelUpExp[pPlayer->iLevel - 1];

			//레벨을 증가시킨다.
			pPlayer->iLevel++;

			cout << "레벨업 하였습니다." << endl;

			//능력치를 상승시킨다.
			//직업 인덱스를 구한다.
			int iJobIdx = pPlayer->eJOB - 1;
			int iHPUp = rand() % (g_tLvUpTable[iJobIdx].iHPMax - g_tLvUpTable[iJobIdx].iHPMin + 1) + g_tLvUpTable[iJobIdx].iHPMin;
			int iMPUp = rand() % (g_tLvUpTable[iJobIdx].iMPMax - g_tLvUpTable[iJobIdx].iMPMin + 1) + g_tLvUpTable[iJobIdx].iMPMin;

			pPlayer->iAttackMin += g_tLvUpTable[iJobIdx].iAttackMin;
			pPlayer->iAttackMax += g_tLvUpTable[iJobIdx].iAttackMax;
			pPlayer->iArmorMin += g_tLvUpTable[iJobIdx].iArmorMin;
			pPlayer->iArmorMax += g_tLvUpTable[iJobIdx].iArmorMax;

			pPlayer->iHPMax += iHPUp;
			pPlayer->iMPMax += iMPUp;

			//체력과 마나를 회복시킨다.
			pPlayer->iHP = pPlayer->iHPMax;
			pPlayer->iMP = pPlayer->iMPMax;
		}
		return;
	}

	//몬스터가 살아있다면 플레이어를 공격한다.
	iAttack = rand() % (pMonster->iAttackMax - pMonster->iAttackMin + 1) + pMonster->iAttackMin;

	int iArmorMin = pPlayer->iArmorMin;
	int iArmorMax = pPlayer->iArmorMax;
	//방어구를 장착하고 있을 경우 방어력을 추가해준다.
	if (pPlayer->bEquip[EQ_ARMOR]) {
		iArmorMin += pPlayer->tEquip[EQ_ARMOR].iMin;
		iArmorMax += pPlayer->tEquip[EQ_ARMOR].iMax;
	}

	iArmor = rand() % (iArmorMax - iArmorMin + 1) + iArmorMin;

	iDamage = iAttack - iArmor;
	iDamage = iDamage < 1 ? 1 : iDamage;

	//플레이어 HP를 감소시킨다.
	pPlayer->iHP -= iDamage;

	cout << pMonster->strName << "가 " << pPlayer->strName << "에게 " << iDamage << " 피해를 입혔습니다." << endl;
	if (pPlayer->iHP <= 0) {
		cout << pPlayer->strName << " 플레이어가 사망하였습니다." << endl;

		int iExp = pPlayer->iExp * 0.1f;
		int iGold = pPlayer->tInventory.iGold * 0.1f;

		pPlayer->iExp -= iExp;
		pPlayer->tInventory.iGold -= iGold;

		cout << iExp << " 경험치를 잃었습니다." << endl;
		cout << iGold << " Gold를 잃었습니다." << endl;

		//플레이어의 HP와 MP를 회복한다.
		pPlayer->iHP = pPlayer->iHPMax;
		pPlayer->iMP = pPlayer->iMPMax;
	}
	return;
}


void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr, int iMenu)
{
	_tagMonster tMonster = pMonsterArr[iMenu - 1];

	while (true)
	{
		system("cls");
		OutputBattleTag(iMenu);
		//플레이어 출력
		OutputPlayer(pPlayer);
		//몬스터 출력
		OutputMonster(&tMonster);

		switch (OutputBattleMenu())
		{
		case BT_ATTACK:
			Battle(pPlayer, &tMonster);
			system("pause");
			break;
		case BT_RUN:
			return;
		}
	}
}

//맵에 관련된 동작을 처리한다.
void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr)
{
	bool bLoop = true;
	while (bLoop)
	{
		int iMenu = OutputMapMenu();
		
		if (iMenu == MT_BACK)
			return;		

		//전투를 시작한다.
		RunBattle(pPlayer, pMonsterArr, iMenu);
	}
}

int SelectJob()
{
	int iJob = JOB_NONE;
	while (iJob == JOB_NONE) {
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		iJob = InputInt();

		if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}

	return iJob;
}

void SetPlayer(_tagPlayer *pPlayer)
{
	system("cls");
	cin.clear();
	cin.ignore(1024, '\n');

	cout << "이름 : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	pPlayer->eJOB = (JOB)SelectJob();
	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->tInventory.iGold = 10000;
	pPlayer->tInventory.iItemCount = 0;


	switch (pPlayer->eJOB) {
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "기사");
		pPlayer->iAttackMin = 5;
		pPlayer->iAttackMax = 10;
		pPlayer->iArmorMin = 15;
		pPlayer->iArmorMax = 20;
		pPlayer->iHP = 500;
		pPlayer->iHPMax = 500;
		pPlayer->iMP = 100;
		pPlayer->iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "궁수");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 15;
		pPlayer->iArmorMin = 10;
		pPlayer->iArmorMax = 15;
		pPlayer->iHP = 400;
		pPlayer->iHPMax = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "마법사");
		pPlayer->iAttackMin = 15;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 5;
		pPlayer->iArmorMax = 10;
		pPlayer->iHP = 300;
		pPlayer->iHPMax = 300;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;
	}

}

_tagMonster CreateMonster(char* pName, int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax, 
	int iHP, int iMP, int iLevel, int iExp, int iGoldMin, int iGoldMax)
{
	_tagMonster tMonster = {};

	strcpy_s(tMonster.strName, pName);
	tMonster.iAttackMin = iAttackMin;
	tMonster.iAttackMax = iAttackMax;

	tMonster.iArmorMin = iArmorMin;
	tMonster.iArmorMin = iArmorMin;

	tMonster.iHP = iHP;
	tMonster.iHPMax = iHP;

	tMonster.iMP = iMP;
	tMonster.iMPMax = iMP;

	tMonster.iLevel = iLevel;
	tMonster.iExp = iExp;

	tMonster.iGoldMin = iGoldMin;
	tMonster.iGoldMax = iGoldMax;

	return tMonster;
}

void SetMonster(_tagMonster* pMonsterArr)
{
	/*
	pMonsterArr[0] = CreateMonster("고블린", 20, 30, 2, 5, 100, 10, 1, 1000, 500, 1500);
	pMonsterArr[1] = CreateMonster("트롤", 80, 130, 60, 90, 2000, 100, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreateMonster("드래곤", 250, 500, 200, 400, 30000, 20000, 10, 30000, 20000, 50000);
	*/

	
		FILE* pFile = NULL;

		fopen_s(&pFile, "Monster.mst", "rb");

		if (pFile)
		{
			fread(pMonsterArr, sizeof(_tagMonster), MT_BACK - 1, pFile);

			fclose(pFile);

		}


}

bool LoadPlayer(_tagPlayer *pPlayer)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Player.ply", "rb");

	if (pFile)
	{
		//플레이어 이름을 읽어온다.
		fread(pPlayer->strName, 1, NAME_SIZE, pFile);
		//직업정보를 읽어온다.
		fread(&pPlayer->eJOB, sizeof(JOB), 1, pFile);
		fread(pPlayer->strJobName, 1, NAME_SIZE, pFile);
		//공격력을 읽어온다.
		fread(&pPlayer->iAttackMax, 4, 1, pFile);
		fread(&pPlayer->iAttackMin, 4, 1, pFile);

		//방어력을 읽어온다
		fread(&pPlayer->iArmorMax, 4, 1, pFile);
		fread(&pPlayer->iArmorMin, 4, 1, pFile);

		//체력을 읽어온다
		fread(&pPlayer->iHP, 4, 1, pFile);
		fread(&pPlayer->iHPMax, 4, 1, pFile);

		//엠피를 읽어온다.
		fread(&pPlayer->iMP, 4, 1, pFile);
		fread(&pPlayer->iMPMax, 4, 1, pFile);

		//레벨정보를 읽어온다.
		fread(&pPlayer->iLevel, 4, 1, pFile);
		fread(&pPlayer->iExp, 4, 1, pFile);

		//무기아이템 장착여부를 읽어온다
		fread(&pPlayer->bEquip[EQ_WEAPON], 1, 1, pFile);

		//저장할 때 무기를 차고있을경우 무기정보를 읽어온다
		if (pPlayer->bEquip[EQ_WEAPON])
		{
			fread(&pPlayer->tEquip[EQ_WEAPON], sizeof(_tagItem), 1, pFile);
		}

		//방어구아이템 착용 여부 확인
		fread(&pPlayer->bEquip[EQ_ARMOR], 1, 1, pFile);
		if (pPlayer->bEquip[EQ_ARMOR])
		{
			fread(&pPlayer->tEquip[EQ_ARMOR], sizeof(_tagItem), 1, pFile);
		}

		//골드를 읽어온다.
		fread(&pPlayer->tInventory.iGold, 4, 1, pFile);

		//인벤토리 아이템 수를 읽어온다.
		fread(&pPlayer->tInventory.iItemCount, 4, 1, pFile);

		//읽어온 아이템 수 만큼 인벤토리에 아이템 정보를 읽어온다.
		fread(pPlayer->tInventory.tItem, sizeof(_tagItem), pPlayer->tInventory.iItemCount, pFile);
		
		fclose(pFile);
		return true;
	}
	return false;
}

bool SavePlayer(_tagPlayer* pPlayer)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Player.ply", "wb");

	if (pFile)
	{
		//쓰는순서대로 읽으므루 쓰는순서와 읽는순서는 완전히 같아야한다.
		//플레이어 이름을 저장한다.
		fwrite(pPlayer->strName, 1, NAME_SIZE, pFile);
		//직업정보를 저장한다.
		fwrite(&pPlayer->eJOB, sizeof(JOB), 1, pFile);
		fwrite(pPlayer->strJobName, 1, NAME_SIZE, pFile);
		//공격력을 저장한다.
		fwrite(&pPlayer->iAttackMax, 4, 1, pFile);
		fwrite(&pPlayer->iAttackMin, 4, 1, pFile);

		//방어력을 저장한다
		fwrite(&pPlayer->iArmorMax, 4, 1, pFile);
		fwrite(&pPlayer->iArmorMin, 4, 1, pFile);

		//체력을 저장한다
		fwrite(&pPlayer->iHP, 4, 1, pFile);
		fwrite(&pPlayer->iHPMax, 4, 1, pFile);

		//엠피를 저장한다.
		fwrite(&pPlayer->iMP, 4, 1, pFile);
		fwrite(&pPlayer->iMPMax, 4, 1, pFile);

		//레벨정보를 저장한다.
		fwrite(&pPlayer->iLevel, 4, 1, pFile);
		fwrite(&pPlayer->iExp, 4, 1, pFile);

		//무기아이템 장착여부를 저장한다
		fwrite(&pPlayer->bEquip[EQ_WEAPON], 1, 1, pFile);

		//저장할 때 무기를 차고있을경우 무기정보를 저장한다
		if (pPlayer->bEquip[EQ_WEAPON])
		{
			fwrite(&pPlayer->tEquip[EQ_WEAPON], sizeof(_tagItem), 1, pFile);
		}

		//방어구아이템 착용 여부를 저장한다.
		fwrite(&pPlayer->bEquip[EQ_ARMOR], 1, 1, pFile);
		if (pPlayer->bEquip[EQ_ARMOR])
		{
			fwrite(&pPlayer->tEquip[EQ_ARMOR], sizeof(_tagItem), 1, pFile);
		}

		//골드를 저장한다.
		fwrite(&pPlayer->tInventory.iGold, 4, 1, pFile);

		//인벤토리 아이템 수를 저장한다.
		fwrite(&pPlayer->tInventory.iItemCount, 4, 1, pFile);

		//읽어온 아이템 수 만큼 인벤토리에 아이템 정보를 저장한다.
		fwrite(pPlayer->tInventory.tItem, sizeof(_tagItem), pPlayer->tInventory.iItemCount, pFile);

		fclose(pFile);
		return true;
	}
	return false;
}

int OutputStoreMenu()
{
	system("cls");
	cout << "*********************** 상점 ***********************" << endl;
	cout << "1. 무기상점" << endl;
	cout << "2. 방어구상점" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "상점을 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu <= SM_NONE || iMenu > SM_BACK)
		return SM_NONE;

	return iMenu;
}

int OutputStoreItemList(_tagInventory* pInventory, _tagItem* pStore, int iItemCount, int iStoreType)
{
	for (int i = 0; i < iItemCount; ++i)
	{
		cout << i + 1 << " . 이름 : " << pStore[i].strName << "\t종류 : " << pStore[i].strTypeName << endl;

		if(iStoreType == SM_WEAPON)
			cout << "공격력 : " << pStore[i].iMin << " - " << pStore[i].iMax << endl;
		else
			cout << "방어력 : " << pStore[i].iMin << " - " << pStore[i].iMax << endl;

		cout << "판매가격 : " << pStore[i].iPrice << "\t구매가격 : " << pStore[i].iSell << endl;
		cout << "아이템 설명 : " << pStore[i].strDesc << endl << endl;
	}
	cout << iItemCount + 1 << ". 뒤로가기" << endl;
	cout << "보유 골드 : " << pInventory->iGold << " Gold" << endl;
	cout << "남은 공간 : " << INVENTORY_MAX - pInventory->iItemCount << " 칸" << endl;

	int iMenu = InputInt();
	if (iMenu < 1 || iMenu > iItemCount + 1)
		return INT_MAX;

	return iMenu;
}

void BuyItem(_tagInventory* pInventory, _tagItem* pStore, int iItemCount, int iStoreType)
{
	while (true)
	{
		system("cls");
		switch (iStoreType)
		{
		case SM_WEAPON:
			cout << "*********************** 무기상점 ***********************" << endl;
			break;
		case SM_ARMOR:
			cout << "*********************** 방어구상점 ***********************" << endl;
			break;
		}
		int iInput = OutputStoreItemList(pInventory, pStore, iItemCount, iStoreType);

		if (iInput == INT_MAX)
		{
			cout << "잘못 입력하셨습니다." << endl;
			system("pause");
			continue;
		}
		else if (iInput == iItemCount + 1)
			break;

		//상점 인덱스 구해주기
		int iIndex = iInput - 1;

		if (pInventory->iItemCount == INVENTORY_MAX)
		{
			cout << "가방이 가득 찼습니다." << endl;
			system("pause");
			continue;
		}
		else if (pInventory->iGold < pStore[iIndex].iPrice)
		{
			cout << "소지금이 부족합니다." << endl;
			system("pause");
			continue;
		}

		pInventory->iGold -= pStore[iIndex].iPrice;
		pInventory->tItem[pInventory->iItemCount] = pStore[iIndex];
		++pInventory->iItemCount;

		cout << "인벤토리에 " << pInventory->tItem[pInventory->iItemCount - 1].strName << "가 추가되었습니다." << endl;
		cout << "Gold가 " << pInventory->iGold << " 만큼 남았습니다. " << endl;

		system("pause");
	}
}

void RunStore(_tagInventory* pInventory, _tagItem* pWeapon, _tagItem* pArmor)
{	
	while (true)
	{
		switch (OutputStoreMenu())
		{
		case SM_WEAPON:
			BuyItem(pInventory, pWeapon, STORE_WEAPON_MAX, SM_WEAPON);
			break;
		case SM_ARMOR:
			BuyItem(pInventory, pArmor, STORE_ARMOR_MAX, SM_ARMOR);
			break;
		case SM_BACK:
			return;
		}
	}

}

_tagItem CreateItem(char* strName, ITEM_TYPE eType, int iMin, int iMax, int iPrice, int iSell, char* strDesc)
{
	_tagItem tItem = {};

	strcpy_s(tItem.strName, strName);
	strcpy_s(tItem.strDesc, strDesc);

	tItem.eType = eType;

	switch (eType)
	{
	case IT_WEAPON:
		strcpy_s(tItem.strTypeName, "무기");
		break;
	case IT_ARMOR:
		strcpy_s(tItem.strTypeName, "방어구");
		break;
	}
	tItem.iMax = iMax;
	tItem.iMin = iMin;
	tItem.iPrice = iPrice;
	tItem.iSell = iSell;

	return tItem;
}

int OutputInventory(_tagPlayer* pPlayer)
{
	system("cls");
	cout << "*********************** 인벤토리 ***********************" << endl << endl;

	OutputPlayer(pPlayer);

	if (pPlayer->bEquip[EQ_WEAPON]) {
		cout << "장착 무기 : " << pPlayer->tEquip[EQ_WEAPON].strName;
	}
	else
		cout << "장착 무기 : 없음";

	if (pPlayer->bEquip[EQ_ARMOR]) {
		cout << "\t장착 방어구 : " << pPlayer->tEquip[EQ_ARMOR].strName << endl << endl;
	}
	else
		cout << "\t장착 방어구 : 없음" << endl << endl;

	for (int i = 0; i < pPlayer->tInventory.iItemCount; i++) {
		cout << i + 1 << ". " << pPlayer->tInventory.tItem[i].strName << endl << endl;
	}
	cout << pPlayer->tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
	cout << "장착할 아이템을 선택해주세요 : ";
	int iMenu = InputInt();

	if (iMenu < 1 || iMenu > pPlayer->tInventory.iItemCount + 1)
		return INT_MAX;
	return iMenu;
}

EQUIP ComputeEquipType(ITEM_TYPE eType)
{
	EQUIP eq;
	switch (eType) 
	{
	case IT_WEAPON:
		eq = EQ_WEAPON;
		break;
	case IT_ARMOR:
		eq = EQ_ARMOR;
		break;
	}
	return eq;
}

void RunInventory(_tagPlayer* pPlayer)
{
	while (true)
	{
		int iInput = OutputInventory(pPlayer);

		if (iInput == INT_MAX)
			continue;

		else if (iInput == pPlayer->tInventory.iItemCount + 1)
			break;

		int idx = iInput - 1;
		//제대로 선택했을 경우 해당 아이템 종류에 따라 장착
		EQUIP eq = ComputeEquipType(pPlayer->tInventory.tItem[idx].eType);

		//아이템이 장착되어있을 경우 장착된 아이템과 해당 아이템을 교체한다.
		if (pPlayer->bEquip[eq] == true) {
			_tagItem tSwap = pPlayer->tEquip[eq];
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];
			pPlayer->tInventory.tItem[idx] = tSwap;
		}

		else {
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];

			for (int i = idx; i < pPlayer->tInventory.iItemCount - 1; i++) {
				pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
			}

			pPlayer->tInventory.iItemCount--;
			pPlayer->bEquip[eq] = true;
		}

		cout << pPlayer->tEquip[eq].strName << "아이템을 장착하였습니다." << endl;
	}
}

bool LoadItem(_tagItem* pWeapon, _tagItem* pArmor)
{
	FILE* pFile = NULL;

	fopen_s(&pFile, "Store.str", "rb");

	if (pFile)
	{
		fread(pWeapon, sizeof(_tagItem), STORE_WEAPON_MAX, pFile);
		fread(pArmor, sizeof(_tagItem), STORE_ARMOR_MAX, pFile);

		fclose(pFile);
		return true;
	}
	return false;
}


int main()
{
	srand((unsigned int)time(0));

	_tagPlayer tPlayer = {};

	int iGameMode = 0;
	while (iGameMode < GM_NEW || iGameMode > GM_END)
	{
		system("cls");
		cout << "1. 새로하기" << endl;
		cout << "2. 이어하기" << endl;
		cout << "3. 종료" << endl;
		
		iGameMode = InputInt();
	}

	if (iGameMode == GM_END)
		return 0;

	switch (iGameMode)
	{
	case GM_NEW:
		SetPlayer(&tPlayer);
		break;
	case GM_LOAD:
		if (!LoadPlayer(&tPlayer))
		{
			cout << "플레이어 파일 오류!!" << endl;
		}
		break;
	}

	//몬스터를 생성한다.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};
	
	SetMonster(tMonsterArr);

	g_tLvUpTable[JOB_KNIGHT - 1] = CreateLvUpStatus(4, 10, 8, 16, 50, 100, 10, 20);
	g_tLvUpTable[JOB_ARCHER - 1] = CreateLvUpStatus(10, 15, 5, 10, 30, 60, 30, 50);
	g_tLvUpTable[JOB_WIZARD - 1] = CreateLvUpStatus(15, 20, 3, 7, 20, 40, 50, 100);

	_tagItem	tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreArmor[STORE_ARMOR_MAX] = {};
	/*
	tStoreWeapon[0] = CreateItem("목검", IT_WEAPON, 5, 10, 1000, 500, "나무로 만든 칼");
	tStoreWeapon[1] = CreateItem("장궁", IT_WEAPON, 20, 40, 7000, 3500, "짱짱한 활");
	tStoreWeapon[2] = CreateItem("지팡이", IT_WEAPON, 90, 150, 30000, 15000, "나무로 만든 지팡이");

	tStoreArmor[0] = CreateItem("천갑옷", IT_ARMOR, 2, 5, 1000, 500, "천으로 만든 허접한 갑옷");
	tStoreArmor[1] = CreateItem("가죽갑옷", IT_ARMOR, 10, 20, 7000, 3500, "동물의 가죽으로 만든 질긴 갑옷");
	tStoreArmor[2] = CreateItem("풀플레이트아머", IT_ARMOR, 70, 90, 30000, 15000, "강철로 만든 판금 갑옷");
	*/
	LoadItem(tStoreWeapon, tStoreArmor);
	bool bLoop = true;
	while (bLoop)
	{
		switch (OutputMainMenu()) {
		case MM_MAP:
			RunMap(&tPlayer, tMonsterArr);
			break;
		case MM_STORE:
			RunStore(&tPlayer.tInventory, tStoreWeapon, tStoreArmor);
			break;
		case MM_INVENTORY:
			RunInventory(&tPlayer);
			break;
		case MM_EXIT:
			bLoop = false;
			break;
		}
	}

	SavePlayer(&tPlayer);
	
	return 0;
}
