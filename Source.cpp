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
		cout << m1->getID()<<" �� ����Ḧ ��Ź��"<<endl;
		cout << "              ����������������������������������������������������";
		Cursor::gotoxy(32, 10);
		cout << "1 ����� ����";
		Cursor::gotoxy(32, 12);
		cout << "2 ������ �˻�";
		Cursor::gotoxy(32, 14);
		cout << "3 ������ ������ ���";
		Cursor::gotoxy(32, 16);
		cout << "4 Į�θ� �޷�" << endl;
		Cursor::gotoxy(32, 18);
		cout << "����=> ";
		cin >> sel;
		switch (sel)
		{
		case 1:
			system("cls");
			cout << " ================����� ����==================" << endl;
			Inventory::showInventory(m1->inventory);
			cout << " 1 �߰�\n" << endl;

			cout << " 2 ����\n" << endl;

			cout << " 3 �ڷ�\n" << endl;

			cout << " ���� => ";
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
				//�ڷΰ��� ��� �ߵ�
				break;
			default:
				cout << "�ٽ�" << endl;
			}
			Inventory::fileSave(m1->inventory, m1->getID());
			break;
		case 2:
			system("cls");
			cout << " ============������ �˻�==============" << endl;
			m1->fSearch();
			break;

		case 3:
			system("cls");
			cout << " ===========������ ������ ���=============" << endl;
			m1->regfood();
			break;
		case 4:
			system("cls");
			cout << " ===========12�� Į�θ� �޷�=============\n" << endl;
			cout << " 1 �ϰ� ���� ����\n" << endl;

			cout << " 2 �ְ� ���� ����\n" << endl;

			cout << " 3 ���� ���� ����\n" << endl;

			cout << " ���� => ";
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
