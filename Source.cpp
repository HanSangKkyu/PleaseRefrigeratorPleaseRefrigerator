#include "Header.h"


int main(void) {
	Management* m1 = new Management;
	Cursor::CursorView(0);
	int sel;
	m1->showTitleScreen();
	while (1) {
		if (Management::logIn(m1) == true)
			break;
		else
			continue;
	}
	while (true)
	{
		system("cls");
		Cursor::gotoxy(28, 7);
		cout << m1->getID()<<" 의 식재료를 부탁해"<<endl;
		cout << "              ──────────────────────────";
		Cursor::gotoxy(32, 10);
		cout << "1 식재료 관리";
		Cursor::gotoxy(32, 12);
		cout << "2 레시피 검색";
		Cursor::gotoxy(32, 14);
		cout << "3 나만의 레시피 등록";
		Cursor::gotoxy(32, 16);
		cout << "4 칼로리 달력" << endl;
		Cursor::gotoxy(32, 18);
		cout << "선택=> ";
		cin >> sel;
		switch (sel)
		{
		case 1:
			system("cls");
			cout << " ================식재료 관리==================" << endl;
			Inventory::showInventory(m1->inventory);
			cout << " 1 추가\n" << endl;

			cout << " 2 삭제\n" << endl;

			cout << " 3 뒤로\n" << endl;

			cout << " 선택 => ";
			cin >> sel;
			switch (sel)
			{
			case 1:
				system("cls");
				m1->inventoryIn();
				break;
			case 2:
				system("cls");
				m1->inventoryOut();
				break;
			case 3:
				//뒤로가기 기능 발동
				break;
			default:
				cout << "다시" << endl;
			}
			Inventory::fileSave(m1->inventory, m1->getID());
			break;
		case 2:
			system("cls");
			cout << " ============레시피 검색==============" << endl;
			m1->fSearch();
			break;

		case 3:
			system("cls");
			cout << " ===========나만의 레시피 등록=============" << endl;
			m1->regfood();
			break;
		case 4:
			system("cls");
			cout << " ===========12월 칼로리 달력=============\n" << endl;
			cout << " 1 일간 정보 보기\n" << endl;

			cout << " 2 주간 정보 보기\n" << endl;

			cout << " 3 월간 정보 보기\n" << endl;

			cout << " 선택 => ";
			cin >> sel;
			switch (sel)
			{
			case 1:
				m1->showCalday();
				break;
			case 2:
				m1->showCalWeek();
				break;
			case 3:
				m1->showCalMonth();
				break;
			}
		}


	}
	delete m1;
	return 0;
}
