#include "Header.h"

char* Ingredients::returnName() {
	return m_name;
}

//===========ㅡCalendar=클래스=함수들===========================

void Calendar::addfoodName(char*name){
	if (fillname < 5){
		strcpy(m_name[fillname++], name);
	}
	else{
		cout << "더이상 먹을 수 없습니다." << endl;
	}
}
void Calendar::addfoodCal(int cal)
{
	if (fillname < 5){
		totalcalorie += cal;
	}
}
void Calendar::showInfo(int day)
{
	cout << "┌───────────────┐" << endl;
	cout << "│             <" <<setw(2)<< day + 1 << " 일>          │" << endl;
	cout << "└───────────────┘" << endl;
	cout << "│            먹은 음식         │" << endl;
	cout << "└───────────────┘" << endl;
	for (int i = 0; i < fillname; i++)
	{
		cout << "│ " << i + 1 << ") " << setw(13) << m_name[i] << "             │" << endl;
	}
	cout << "┌───────────────┐" << endl;
	cout << "│섭취한 칼로리량 : " << setw(5) << totalcalorie << setw(9) << "│" << endl;
	cout << "└───────────────┘" << endl;
	cout << "\n" << endl;
}






//===========ㅡManagement=클래스=함수들===========================
Management::Management()
	: m_fofill(0)
{
	strcpy_s(m_ID, 15, " ");
	Inventory::inventoryLoad(inventory, m_ID);
	Ingredients::ingredientsLoad(ingredients);
	ifstream recipefile;
	recipefile.open("food.txt");
	char name[NAME_BYTE];
	char recipe[RECIPE_BYTE];
	int calorie;
	char ingredient[20];
	for (int i = 0; i < 10; i++)
	{
		fo[i] = new Food();
		if (recipefile.is_open())
		{
			recipefile >> name;
			fo[i]->setname(name);
			while (1)
			{
				recipefile >> recipe;
				if (!strcmp(recipe, "-"))
				{
					break;
				}
				else{
					fo[i]->setrecipe(recipe);
				}
			}
			recipefile >> calorie;
			fo[i]->setcalorie(calorie);
			while (1)
			{
				recipefile >> ingredient;
				if (!strcmp(ingredient, "-"))
				{
					break;
				}
				else{
					fo[i]->setingredient(ingredient);
				}
			}
		}
		else
		{
			cout << "파일없다" << endl;
		}
	}
	char checkStar[3];
	char id[15];
	int i = 0;
	recipefile.close();
	recipefile.open("myRecipe.txt");
	while (!recipefile.eof()) {
		recipefile >> checkStar;
		if (strcmp(checkStar, "*"))
			break;
		m_fo[i] = new mFood();
		recipefile >> id; //사용자 아이디
		m_fo[i]->setID(id);
		recipefile >> name; //요리 이름
		m_fo[i]->setname(name);
		recipefile >> recipe; //요리 순서
		while (strcmp(recipe, "-"))
		{
			m_fo[i]->setrecipe(recipe);
			recipefile >> recipe; //요리 순서
		}
		recipefile >> calorie; //요리 열량
		m_fo[i]->setcalorie(calorie);
		recipefile >> ingredient; //요리 재료
		while (strcmp(ingredient, "-"))
		{
			m_fo[i]->setingredient(ingredient);
			recipefile >> ingredient; //요리 재료
		}
		i++;
		m_fofill++;
	}
	recipefile.close();
}
Management::Management(char* ID)
	:m_fofill(0)
{
	strcpy_s(m_ID, 15, ID);
	calendarIn(m_ID);//캘린더 정보를 불러온다
	Inventory::inventoryLoad(inventory, m_ID);
	Ingredients::ingredientsLoad(ingredients);
	ifstream recipefile;
	recipefile.open("food.txt");
	char name[NAME_BYTE];
	char recipe[RECIPE_BYTE];
	int calorie;
	char ingredient[20];
	for (int i = 0; i < 10; i++)
	{
		fo[i] = new Food();
		if (recipefile.is_open())
		{
			recipefile >> name;
			fo[i]->setname(name);
			while (1)
			{
				recipefile >> recipe;
				if (!strcmp(recipe, "-"))
				{
					break;
				}
				else {
					fo[i]->setrecipe(recipe);
				}
			}
			recipefile >> calorie;
			fo[i]->setcalorie(calorie);
			while (1)
			{
				recipefile >> ingredient;
				if (!strcmp(ingredient, "-"))
				{
					break;
				}
				else {
					fo[i]->setingredient(ingredient);
				}
			}
		}
		else
		{
			cout << "파일없다" << endl;
		}
	}
	char checkStar[3];
	char id[15];
	int i = 0;
	recipefile.close();
	recipefile.open("myRecipe.txt");
	while (!recipefile.eof()) {
		recipefile >> checkStar;
		if (strcmp(checkStar, "*"))
			break;
		m_fo[i] = new mFood();
		recipefile >> id; //사용자 아이디
		m_fo[i]->setID(id);
		recipefile >> name; //요리 이름
		m_fo[i]->setname(name);
		recipefile >> recipe; //요리 순서
		while (strcmp(recipe, "-"))
		{
			m_fo[i]->setrecipe(recipe);
			recipefile >> recipe; //요리 순서
		}
		recipefile >> calorie; //요리 열량
		m_fo[i]->setcalorie(calorie);
		recipefile >> ingredient; //요리 재료
		while (strcmp(ingredient, "-"))
		{
			m_fo[i]->setingredient(ingredient);
			recipefile >> ingredient; //요리 재료
		}
		i++;
		m_fofill++;
	}
	recipefile.close();
}
Management::~Management() {
	for (int i = 0; i < _msize(inventory) / 4; i++)
	{
		delete inventory[i];
	}
	delete inventory;
	for (int i = 0; i < 10; i++)
		delete fo[i];
	for (int i = 0; i < m_fofill; i++)
		delete m_fo[i];

}
bool Management::logIn(Management* m1) {
	char inputID[30];
	char inputPW[15];
	char id[15];
	char pw[15];
	char checkStar[100];

	while (1) {
		Cursor::gotoxy(20, 6);
		cout << "──────────────────";
		Cursor::gotoxy(26, 7);
		cout << "♧ 식재료을 부탁해 ♧";
		Cursor::gotoxy(20, 8);
		cout << "──────────────────";
		Cursor::gotoxy(32, 10);
		cout << "1)회원가입 ";
		Cursor::gotoxy(32, 12);
		cout << "2)로그인 ";
		Cursor::gotoxy(32, 14);
		cout << "선택 : ";
		int sel;
		cin >> sel;
		if (sel == 1) {
			system("cls");
			Cursor::gotoxy(30, 7);
			cout << "*** 회원가입 ***" << endl;
			Cursor::gotoxy(32, 10);
			cout << "ID : ";
			cin >> inputID;
			Cursor::gotoxy(32, 12);
			cout << "PW : ";
			cin >> inputPW;
			ofstream of;
			of.open("회원가입.txt", ios_base::app);
			of << "*" << endl;
			of << inputID << endl;
			of << inputPW << endl;

			of.close();
			system("cls");

		}
		if (sel == 2) {
			system("cls");
			Cursor::gotoxy(30, 7);
			cout << "*** 로그인 ***" << endl;
			Cursor::gotoxy(32, 10);
			cout << "ID : ";
			cin >> id;
			Cursor::gotoxy(32, 12);
			cout << "PW : ";
			cin >> pw;

			ifstream fin("회원가입.txt", ios::in | ios::out);
			fin.is_open();
			while (!fin.eof()) {
				fin >> checkStar;
				if (!strcmp("*", checkStar)) {
					//m_memberNum++;  //로그인 한 아이디가 몇번쨰 아이디인지 확인
				}

				for (int i = 0; i < 10; i++) {
					if (i == 0) {
						fin >> inputID;
						fin >> inputPW;
					}
					if (i >= 1) {
						fin >> checkStar;
						fin >> inputID;
						fin >> inputPW;
					}
					if (strcmp(id, inputID) == 0 && strcmp(pw, inputPW) == 0) {


						delete m1;
						m1 = new Management(inputID);
						system("cls");
						Cursor::gotoxy(32, 10);
						cout << m1->m_ID << "님 환영합니다." << endl;
						Sleep(2000);
						system("cls");
						return true;
					}
					else {
						if (i == 10) {
							Cursor::gotoxy(32, 10);
							cout << "로그인 실패" << endl;
							Sleep(2000);
							system("cls");
							return false;
						}
					}
				}
			}
		}
	}
}
void Management::inventoryIn() {
	char name[NAME_BYTE];
	if (Inventory::inventoryExistanceCheck(inventory) == -1) {
		Cursor::gotoxy(20, 12);
		cout << " 인벤토리가 가득 찼습니다. 재료를 추가하려면 프로그램을 종료하고 다시 접속해주세요." << endl;
	}
	else {

		Inventory::showInventory(inventory);
		strcpy_s(name, NAME_BYTE, iSearch());
		system("cls");
		Inventory::showInventory(inventory);
		cout << " 추가할 " << name << "의 ";
		inventory[Inventory::inventoryExistanceCheck(inventory)]->inventoryIn(name);
		Inventory::inventorySet(inventory);
		system("cls");
		Inventory::showInventory(inventory);
		cout << " " << name << "(이/가) 추가 되었습니다." << endl;
		_getch();
	}
}
void Management::inventoryOut() {
	int sel;
	char ynsel;
	int num;
	if (Inventory::inventoryExistanceCheck(inventory) == -1) {
		cout << " 무엇을 삭제하겠습니까?" << endl;
		cout << " ";
		cin >> sel;
		system("cls");
		Inventory::showInventory(inventory);
		if (sel > 0 && sel <= _msize(inventory) / 4) {
			cout << " 모두 버리겠습니까? (y/n)" << endl;
			cout << " ";
			cin >> ynsel;

			if (ynsel == 'y') {
				inventory[sel - 1]->inventoryOut();
				system("cls");
				Inventory::showInventory(inventory);
				cout << " 삭제되었습니다." << endl;

			}
			else {
				cout << " 얼마나 삭제하겠습니까?" << endl;
				cout << " ";
				cin >> num;
				inventory[sel - 1]->inventoryOut(num);
				system("cls");
				Inventory::inventorySet(inventory);
			}

		}
		else {
			system("cls");
			Inventory::showInventory(inventory);
			cout << " 존재하지 않습니다." << endl;
		}
	}
	else {
		Inventory::showInventory(inventory);
		cout << " 무엇을 삭제하겠습니까?" << endl;
		cout << " ";
		cin >> sel;
		system("cls");
		Inventory::showInventory(inventory);
		if (sel > 0 && sel <= Inventory::inventoryExistanceCheck(inventory)) {
			cout << " 전체 삭제하겠습니까? (y/n)" << endl;
			cout << " ";
			cin >> ynsel;

			if (ynsel == 'y') {
				inventory[sel - 1]->inventoryOut();
				system("cls");
				Inventory::showInventory(inventory);
				cout << " 삭제되었습니다." << endl;
			}
			else {
				system("cls");
				Inventory::showInventory(inventory);
				cout << " 얼마나 삭제하겠습니까?" << endl;
				cout << " ";
				cin >> num;
				inventory[sel - 1]->inventoryOut(num);
				system("cls");
				Inventory::inventorySet(inventory);
				Inventory::showInventory(inventory);
				cout << " 삭제되었습니다." << endl;
			}


		}
		else {
			cout << " 존재하지 않습니다." << endl;
		}
	}
	_getch();
}

void Management::showfood()
{
	for (int i = 0; i < 10; i++)
	{
		fo[i]->showfood();
	}
	for (int i = 0; i < 100/*MAX_MEM*/; i++)  //i<m_fofill
	{
		m_fo[i]->showfood();
	}
}
void Management::regfood()
{


	char name[NAME_BYTE];
	char recipe[RECIPE_BYTE];
	int calorie;
	char ingredient[NAME_BYTE];

	ofstream of;
	of.open("myRecipe.txt", ios_base::app);


	m_fo[m_fofill] = new Food();
	cout << "요리이름: ";
	cin >> name;
	of << "*" << endl;
	of << getID() << endl;   ///
	of << name << endl;
	m_fo[m_fofill]->setname(name);
	cout << "요리순서: "<<endl;
	while (1)
	{
		cin >> recipe;
		of << recipe << endl;
		if (!strcmp(recipe, "-"))
			break;
		m_fo[m_fofill]->setrecipe(recipe);
	}
	cout << "요리열량: ";
	cin >> calorie;
	of << calorie << endl;
	m_fo[m_fofill]->setcalorie(calorie);

	cout << "사용재료: ";
	char select;
	while (1)
	{
		strcpy_s(ingredient, NAME_BYTE, iSearch());
		of << ingredient << endl;
		m_fo[m_fofill]->setingredient(ingredient);
		while (true)
		{
			cout << " 계속 추가하겠습니까?(y/n)" << endl;
			cin >> select;
			if (select == 'n') {
				break;
			}
			else if (select == 'y') {
				break;
			}
			else {
				cout << "y, n 중 하나를 입력하세요." << endl;
			}
		}
		if (select == 'n') {
			of << "-" << endl;
			break;
		}
	}

	m_fofill++;

	of.close();
}


char* Management::iSearch() {

	int num;
	while (1)
	{
		system("cls");
		Inventory::showInventory(inventory);
		cout << " 원하는 재료의 분류를 선택하세요." << endl;
		cout << " 1 채소" << endl;
		cout << " 2 밥/떡/소면" << endl;
		cout << " 3 육류/유제품" << endl;
		cout << " 4 해산물/장류" << endl;
		cout << " 5 가루/소스" << endl;
		cout << " 선택 : ";
		cin >> num;
		if (num == 1) {
			system("cls");
			Inventory::showInventory(inventory);
			cout << " 원하는 '1 채소'를 선택하세요(뒤로가기: ESC)" << endl;
			for (int i = 0; i < LIST; i++)
			{
				cout << " " << i + 1 << "	" << ingredients[0][i].returnName() << endl;
				if (!strcmp(ingredients[0][i + 1].returnName(), "-"))
					break;
			}

			num = _getch();
			if (num == 27)
				continue;
			else
				num -= 48;


			return ingredients[0][num - 1].returnName();
		}
		else if (num == 2) {
			system("cls");
			Inventory::showInventory(inventory);
			cout << " 원하는 '2 밥/떡/소면'를 선택하세요(뒤로가기: ESC)" << endl;
			for (int i = 0; i < LIST; i++)
			{
				cout << " " << i + 1 << "	" << ingredients[1][i].returnName() << endl;
				if (!strcmp(ingredients[1][i + 1].returnName(), "-"))
					break;
			}
			num = _getch();
			if (num == 27)
				continue;
			else
				num -= 48;
			return ingredients[1][num - 1].returnName();
		}
		else if (num == 3) {
			system("cls");
			Inventory::showInventory(inventory);
			cout << " 원하는 '3 육류/유제품'를 선택하세요(뒤로가기: ESC)" << endl;
			for (int i = 0; i < LIST; i++)
			{
				cout << " " << i + 1 << "	" << ingredients[2][i].returnName() << endl;
				if (!strcmp(ingredients[2][i + 1].returnName(), "-"))
					break;
			}
			num = _getch();
			if (num == 27)
				continue;
			else
				num -= 48;
			return ingredients[2][num - 1].returnName();
		}
		else if (num == 4) {
			system("cls");
			Inventory::showInventory(inventory);
			cout << " 원하는 '4 해산물'를 선택하세요(뒤로가기: ESC)" << endl;
			for (int i = 0; i < LIST; i++)
			{
				cout << " " << i + 1 << "	" << ingredients[3][i].returnName() << endl;
				if (!strcmp(ingredients[3][i + 1].returnName(), "-"))
					break;
			}
			num = _getch();
			if (num == 27)
				continue;
			else
				num -= 48;
			return ingredients[3][num - 1].returnName();
		}
		else if (num == 5) {
			system("cls");
			Inventory::showInventory(inventory);
			cout << " 원하는 '5 가루/소스'를 선택하세요(뒤로가기: ESC)" << endl;
			for (int i = 0; i < LIST; i++)
			{
				cout << " " << i + 1 << "	" << ingredients[4][i].returnName() << endl;
				if (!strcmp(ingredients[4][i + 1].returnName(), "-"))
					break;
			}
			num = _getch();
			if (num == 27)
				continue;
			else
				num -= 48;
			return ingredients[4][num - 1].returnName();
		}
	}
}

void Management::fSearch() {
	cout << "┌──────────────────┐" << endl;
	cout << "│           가능한 요리 목록         │" << endl;
	for (int i = 0; i < 10; i++) {
		fo[i]->fSearch(i, inventory);
	}
	for (int i = 0; i < m_fofill; i++) {
		m_fo[i]->fSearch(i + 10, inventory);
	}
	cout << "└──────────────────┘" << endl;
	cout << " 1 레시피 보기 \n" << endl;
	cout << " 2 뒤로\n" << endl;
	int sel;
	cout << " 선택 : ";
	cin >> sel;
	if (sel == 1)
	{
		system("cls");
		cout << "┌──────────────────┐" << endl;
		cout << "│           가능한 요리 목록         │" << endl;
		for (int i = 0; i < 10; i++) {
			fo[i]->fSearch(i, inventory);
		}
		for (int i = 0; i < m_fofill; i++) {
			m_fo[i]->fSearch(i + 10, inventory);
		}
		cout << "└──────────────────┘" << endl;
		cout << " 확인할 레시피 번호를 입력하세요" << endl;
		cout << " ";
		cin >> sel;
		system("cls");
		cout << "         레시피 정보" << endl;
		cout << "───────────────────────" << endl;
		fo[sel]->showfood();
		cout << endl;
		cout << "───────────────────────" << endl;
		cout << " 먹겠습니까?(y/n) : ";
		char c;
		cin >> c;
		if (c == 'y')
		{

			addfoodName(fo[sel]->returnName());
			addfoodCal(fo[sel]->returnCalorie());
			calendarOut(m_ID);
			char in_name[NAME_BYTE];
			for (int i = 0; i < 10; i++) {
				strcpy_s(in_name, NAME_BYTE, fo[sel]->returnIngredient(i));
				for (int j = 0; j < _msize(inventory)/4;j++)
				{
					if (!strcmp(in_name, inventory[j]->returnName())) {
						inventory[j]->inventoryOut(1);
						break;
					}
				}
			}
		}
		else
		{

		}
	}
	else if (sel == 2)
	{
		return;
	}



}

void Management::addfoodName(char*name){
	time_t curr_time;
	struct tm *curr_tm;
	curr_time = time(NULL);
	curr_tm = localtime(&curr_time);
	calendar[(int)(curr_tm->tm_mday) - 1].addfoodName(name);
}
void Management::addfoodCal(int cal){
	time_t curr_time;
	struct tm *curr_tm;
	curr_time = time(NULL);
	curr_tm = localtime(&curr_time);
	calendar[(int)(curr_tm->tm_mday) - 1].addfoodCal(cal);
}
void Management::calendarIn(char ID[15])//txt파일에 저장되어있는 캘린더 정보를 불러온다 
{
	char filename[30];
	strcpy_s(filename, 30, ID);
	strcat_s(filename, 30, "calendar.txt");
	ifstream File;
	File.open(filename);
	if (File.is_open()) {
		while (1)
		{
			int day;
			int cal;//txt에서 칼로리 정보를 임시로 저장하는 변수
			char name[20];

			File >> day;
			File >> cal;
			calendar[day - 1].addfoodCal(cal);
			while (1)
			{
				File >> name;
				if (!strcmp(name, "-"))
					break;
				calendar[day - 1].addfoodName(name);
			}

			if (File.eof())
				break;
		}
	}
	else {
		ofstream f(filename);
		for (int i = 1; i < 32; i++)
		{
			f << '\n' << i << '\n' << 0 << '\n' << "-";
		}
		f.close();
		File.open(filename);
		while (1)
		{
			int day;
			int cal;//txt에서 칼로리 정보를 임시로 저장하는 변수
			char name[20];

			File >> day;
			File >> cal;
			calendar[day - 1].addfoodCal(cal);
			while (1)
			{
				File >> name;
				if (!strcmp(name, "-"))
					break;
				calendar[day - 1].addfoodName(name);
			}

			if (File.eof())
				break;
		}
	}
	File.close();
}
void Management::calendarOut(char ID[15])//txt파일에 캘린더 정보를 저장한다.
{
	char filename[40];
	strcpy_s(filename, 40, ID);
	strcat_s(filename, 40, "calendar.txt");
	ofstream File;
	File.open(filename);
	for (int i = 0; i < 31; i++)
	{
		File << '\n';
		File << i + 1;
		File << '\n';
		File << calendar[i].returnTotalcalorie();
		File << '\n';
		for (int j = 0; j < calendar[i].returnFillname(); j++)
		{
			File << calendar[i].returnM_name(j);
			File << '\n';
		}
		File << "-";

	}
	File.close();
}
void Management::showCalday()
{
	system("cls");
	int day;
	cout << "12월 며칟날 정보를 확인하시겠습니까? : ";
	cin >> day;
	calendar[day - 1].showInfo(day - 1);
	_getch();
}
void Management::showCalWeek()
{
	system("cls");
	int week;
	int calorie = 0;
	cout << "12월 몇번째주 정보를 확인하시겠습니까?(1~5) : ";

	cin >> week;
	switch (week)
	{
	case 1:
		for (int i = 0; i < 3; i++)
		{
			calendar[i].showInfo(i);
			calorie += calendar[i].returnTotalcalorie();
		}
		break;
	case 2:
		for (int i = 3; i < 10; i++)
		{
			calendar[i].showInfo(i);
			calorie += calendar[i].returnTotalcalorie();
		}
		break;
	case 3:
		for (int i = 10; i < 17; i++)
		{
			calendar[i].showInfo(i);
			calorie += calendar[i].returnTotalcalorie();
		}
		break;
	case 4:
		for (int i = 17; i < 24; i++)
		{
			calendar[i].showInfo(i);
			calorie += calendar[i].returnTotalcalorie();
		}
		break;
	case 5:
		for (int i = 24; i < 31; i++)
		{
			calendar[i].showInfo(i);
			calorie += calendar[i].returnTotalcalorie();
		}
		break;
	default:
		cout << "잘못된 입력값입니다.";
	}
	cout << week << " 번째주에 섭취한 총 칼로리량 : " << calorie << endl;
	_getch();
}
void Management::showCalMonth()
{
	system("cls");
	int calorie = 0;
	for (int i = 0; i < 31; i++)
	{
		calorie += calendar[i].returnTotalcalorie();
	}
	cout << "12월에 섭취한 총 칼로리량 : " << calorie << endl;
	_getch();
}
void Management::showTitleScreen() const
{
	Cursor::gotoxy(9, 0);
	cout << "┌─────────────┐";
	Cursor::gotoxy(9, 1);
	cout << "│";
	Cursor::gotoxy(9, 2);
	cout << "│";
	Cursor::gotoxy(9, 3);
	cout << "│";
	Cursor::gotoxy(9, 4);
	cout << "│";
	Cursor::gotoxy(9, 5);
	cout << "│";
	Cursor::gotoxy(9, 6);
	cout << "│";
	Cursor::gotoxy(9, 7);
	cout << "│";
	Cursor::gotoxy(9, 8);
	cout << "│";
	Cursor::gotoxy(9, 9);
	cout << "│";
	Cursor::gotoxy(9, 10);
	cout << "│";
	Cursor::gotoxy(9, 11);
	cout << "│";
	Cursor::gotoxy(9, 12);
	cout << "│";
	Cursor::gotoxy(9, 13);
	cout << "│";
	Cursor::gotoxy(9, 14);
	cout << "│";
	Cursor::gotoxy(9, 15);
	cout << "│";
	Cursor::gotoxy(9, 16);
	cout << "│";
	Cursor::gotoxy(9, 17);
	cout << "│";
	Cursor::gotoxy(9, 18);
	cout << "│";
	Cursor::gotoxy(9, 19);
	cout << "│";
	Cursor::gotoxy(9, 20);
	cout << "│";
	Cursor::gotoxy(9, 21);
	cout << "│";
	Cursor::gotoxy(9, 22);
	cout << "│";
	Cursor::gotoxy(9, 23);
	cout << "│";
	Cursor::gotoxy(37, 1);
	cout << "│";
	Cursor::gotoxy(37, 2);
	cout << "│";
	Cursor::gotoxy(37, 3);
	cout << "│";
	Cursor::gotoxy(37, 4);
	cout << "│";
	Cursor::gotoxy(37, 5);
	cout << "│";
	Cursor::gotoxy(37, 6);
	cout << "│";
	Cursor::gotoxy(37, 7);
	cout << "│";
	Cursor::gotoxy(37, 8);
	cout << "│";
	Cursor::gotoxy(37, 9);
	cout << "│";
	Cursor::gotoxy(37, 10);
	cout << "│";
	Cursor::gotoxy(37, 11);
	cout << "│";
	Cursor::gotoxy(37, 12);
	cout << "│";
	Cursor::gotoxy(37, 13);
	cout << "│";
	Cursor::gotoxy(37, 14);
	cout << "│";
	Cursor::gotoxy(37, 15);
	cout << "│";
	Cursor::gotoxy(37, 16);
	cout << "│";
	Cursor::gotoxy(37, 17);
	cout << "│";
	Cursor::gotoxy(37, 18);
	cout << "│";
	Cursor::gotoxy(37, 19);
	cout << "│";
	Cursor::gotoxy(37, 20);
	cout << "│";
	Cursor::gotoxy(37, 21);
	cout << "│";
	Cursor::gotoxy(37, 22);
	cout << "│";
	Cursor::gotoxy(37, 23);
	cout << "│";
	Cursor::gotoxy(9, 23);
	cout << "└─────────────┘";
	Cursor::gotoxy(11, 2);
	cout << "┌────────────┐";
	Cursor::gotoxy(11, 3);
	cout << "│";
	Cursor::gotoxy(11, 4);
	cout << "│";
	Cursor::gotoxy(11, 5);
	cout << "│";
	Cursor::gotoxy(11, 6);
	cout << "│";
	Cursor::gotoxy(11, 7);
	cout << "│";
	Cursor::gotoxy(11, 8);
	cout << "└────────────┘";
	Cursor::gotoxy(8, 1);
	cout << "/";
	Cursor::gotoxy(8, 2);
	cout << "/";
	Cursor::gotoxy(8, 3);
	cout << "/";
	Cursor::gotoxy(8, 4);
	cout << "/";
	Cursor::gotoxy(8, 5);
	cout << "/";
	Cursor::gotoxy(8, 6);
	cout << "/";
	Cursor::gotoxy(8, 7);
	cout << "/";
	Cursor::gotoxy(8, 8);
	cout << "/";
	Cursor::gotoxy(8, 9);
	cout << "/";
	Cursor::gotoxy(8, 10);
	cout << "/";
	Cursor::gotoxy(8, 11);
	cout << "/";
	Cursor::gotoxy(8, 12);
	cout << "/";
	Cursor::gotoxy(8, 13);
	cout << "/";
	Cursor::gotoxy(8, 14);
	cout << "/";
	Cursor::gotoxy(8, 15);
	cout << "/";
	Cursor::gotoxy(8, 16);
	cout << "/";
	Cursor::gotoxy(8, 17);
	cout << "/";
	Cursor::gotoxy(8, 18);
	cout << "/";
	Cursor::gotoxy(8, 19);
	cout << "/";
	Cursor::gotoxy(8, 20);
	cout << "/";
	Cursor::gotoxy(8, 21);
	cout << "/";
	Cursor::gotoxy(8, 22);
	cout << "/";
	Cursor::gotoxy(8, 23);
	cout << "/";
	Cursor::gotoxy(38, 2);
	cout << "┌────────────┐";
	Cursor::gotoxy(38, 3);
	cout << "│";
	Cursor::gotoxy(38, 4);
	cout << "│";
	Cursor::gotoxy(38, 5);
	cout << "│";
	Cursor::gotoxy(38, 6);
	cout << "│";
	Cursor::gotoxy(38, 7);
	cout << "│";
	Cursor::gotoxy(38, 8);
	cout << "│";
	Cursor::gotoxy(38, 8);
	cout << "└────────────┘";
	Cursor::gotoxy(64, 3);
	cout << "│";
	Cursor::gotoxy(64, 4);
	cout << "│";
	Cursor::gotoxy(64, 5);
	cout << "│";
	Cursor::gotoxy(64, 6);
	cout << "│";
	Cursor::gotoxy(64, 7);
	cout << "│";
	Cursor::gotoxy(11, 11);
	cout << "┌────────────┐";
	Cursor::gotoxy(11, 12);
	cout << "│";
	Cursor::gotoxy(11, 13);
	cout << "│";
	Cursor::gotoxy(11, 14);
	cout << "│";
	Cursor::gotoxy(11, 15);
	cout << "│";
	Cursor::gotoxy(11, 16);
	cout << "│";
	Cursor::gotoxy(11, 17);
	cout << "│";
	Cursor::gotoxy(11, 18);
	cout << "│";
	Cursor::gotoxy(11, 19);
	cout << "│";
	Cursor::gotoxy(11, 20);
	cout << "│";
	Cursor::gotoxy(11, 21);
	cout << "└────────────┘";
	Cursor::gotoxy(38, 11);
	cout << "┌────────────┐";
	Cursor::gotoxy(38, 21);
	cout << "└────────────┘";
	Cursor::gotoxy(64, 12);
	cout << "│";
	Cursor::gotoxy(64, 13);
	cout << "│";
	Cursor::gotoxy(64, 14);
	cout << "│";
	Cursor::gotoxy(64, 15);
	cout << "│";
	Cursor::gotoxy(64, 16);
	cout << "│";
	Cursor::gotoxy(64, 17);
	cout << "│";
	Cursor::gotoxy(64, 18);
	cout << "│";
	Cursor::gotoxy(64, 19);
	cout << "│";
	Cursor::gotoxy(64, 20);
	cout << "│";
	Cursor::textcolor(10);
	Cursor::gotoxy(18, 5);
	cout << "식재료를 부탁해";

	Cursor::gotoxy(25, 13);
	cout << "/";
	Cursor::gotoxy(22, 14);
	cout << "*****";
	Cursor::gotoxy(21, 15);
	cout << "*";
	Cursor::gotoxy(23, 15);
	cout << "---";
	Cursor::gotoxy(21, 16);
	cout << "*";
	Cursor::gotoxy(21, 17);
	cout << "*";
	Cursor::gotoxy(21, 16);
	cout << "*";
	Cursor::gotoxy(21, 17);
	cout << "*";
	Cursor::gotoxy(22, 18);
	cout << "*****";
	Cursor::gotoxy(27, 15);
	cout << "*";
	Cursor::gotoxy(27, 16);
	cout << "*";
	Cursor::gotoxy(27, 17);
	cout << "*";
	Cursor::textcolor(7);
	_getch();
	fflush(stdin);
	system("cls");
}

//==============Invetory=클래스=함수들============================
void Inventory::inventoryLoad(Inventory** &inventory, char ID[15]) {			//파일에서 인벤토리 정보를 받아온다.
	char name[NAME_BYTE];
	int quantity;
	int period;
	char for_check_char[NAME_BYTE];
	int for_check_int = 0;
	char filename[30];
	strcpy_s(filename, 15, ID);
	strcat_s(filename, 30, "inventory.txt");
	ifstream inventoryFile(filename);
	if (inventoryFile.is_open()) {
		while (!inventoryFile.eof())
		{
			inventoryFile >> for_check_char;
			for_check_int++;
		}
		inventoryFile.close();
		inventory = new Inventory*[for_check_int / 3 + 20];		//현재 가지고 있는 재료 목록 +20만큼 동적할당 해 여분을 만들어둔다.

		inventoryFile.open(filename);
		for (int i = 0; i < _msize(inventory) / 4; i++)
		{
			if (!inventoryFile.eof()) {
				inventoryFile >> name;
				inventoryFile >> quantity;
				inventoryFile >> period;
				inventory[i] = new Inventory(name, quantity, period);
			}
			else {
				inventory[i] = new Inventory("-", 0, 0);		//빈칸은 이렇게 저장된다.
			}
		}
		inventoryFile.close();
	}
	else {
		ofstream out(filename);
		out << "-";
		out << '\n';
		out << 0;
		out << '\n';
		out << 0;
		out.close();
		inventoryFile.open(filename);
		while (!inventoryFile.eof())
		{
			inventoryFile >> for_check_char;
			for_check_int++;
		}
		inventoryFile.close();
		inventory = new Inventory*[for_check_int / 3 + 20];		//현재 가지고 있는 재료 목록 +20만큼 동적할당 해 여분을 만들어둔다.

		inventoryFile.open(filename);
		for (int i = 0; i < _msize(inventory) / 4; i++)
		{
			if (!inventoryFile.eof()) {
				inventoryFile >> name;
				inventoryFile >> quantity;
				inventoryFile >> period;
				inventory[i] = new Inventory(name, quantity, period);
			}
			else {
				inventory[i] = new Inventory("-", 0, 0);		//빈칸은 이렇게 저장된다.
			}
		}
		inventoryFile.close();
	}
}
void Inventory::showInventory(Inventory** &inventory) {			//빈칸은 보여주지 않는다.

	cout << "┌─────────────────────────┐" << endl;

	for (int i = 0; i < _msize(inventory) / 4; i++)
	{
		if (strcmp(inventory[i]->m_name, "-") && inventory[i]->checkPeriod()) {
			cout << "│" << "이름: " << setw(8) << inventory[i]->m_name << " 수량: " << setw(8) << inventory[i]->m_quantity << " 유통기한: " << setw(8) << inventory[i]->m_period << setw(4) << "│" << endl;

		}
		else if (strcmp(inventory[i]->m_name, "-")) {
			cout << "│" << "이름: " << setw(8) << inventory[i]->m_name << " 수량: " << setw(8) << inventory[i]->m_quantity << " 유통기한: " << setw(8) << "지났음" << setw(4) << "│" << endl;
		}

	}
	cout << "└─────────────────────────┘" << endl;
}
void Inventory::inventorySet(Inventory** &inventory) {		//인벤토리를 정리하는 함수
	for (int i = 0; i < _msize(inventory) / 4; i++)						//재료의 이름과 유통기한이 같을 시, 두 목록의 수량을 합치고 뒤에 있는 쪽을 비움.
	{
		for (int j = 0; j < _msize(inventory) / 4; j++)
		{
			if (i != j && strcmp(inventory[i]->m_name, "-") != 0
				&& !strcmp(inventory[i]->m_name, inventory[j]->m_name)
				&& inventory[i]->m_period == inventory[j]->m_period) {
				inventory[i]->m_quantity += inventory[j]->m_quantity;
				strcpy_s(inventory[j]->m_name, NAME_BYTE, "-");
				inventory[j]->m_quantity = 0;
				inventory[j]->m_period = 0;
			}
		}
	}
	for (int i = 0; i < _msize(inventory) / 4 - 1; i++)					//비어있는 목록을 아래로 정렬시킴.
	{
		if (!strcmp(inventory[i]->m_name, "-")) {
			for (int j = i; j < _msize(inventory) / 4 - 1; j++) {
				strcpy_s(inventory[j]->m_name, NAME_BYTE, inventory[j + 1]->m_name);
				inventory[j]->m_quantity = inventory[j + 1]->m_quantity;
				inventory[j]->m_period = inventory[j + 1]->m_period;
			}
			inventory[_msize(inventory) / 4 - 1]->inventoryOut();
		}
	}

}
int Inventory::inventoryExistanceCheck(Inventory** &inventory) {		//인벤토리의 빈칸이 있는지 검사해 제일 먼저 나타나는 빈칸의 숫자를 반환, 빈칸이 없을 시 -1 반환
	for (int i = 0; i < _msize(inventory) / 4; i++)
	{
		if (!strcmp(inventory[i]->m_name, "-")) {
			return i;
		}
	}
	cout << " 남아있는 공간이 없습니다." << endl;
	return -1;
}
void Inventory::inventoryIn(char* name) {			//해당 자리에 재료를 추가
	strcpy_s(m_name, NAME_BYTE, name);
	cout << " 수량을 입력하세요: ";
	cin >> m_quantity;
	while (true)
	{
		cout << " 유통기한을 입력하세요(yyyymmdd): ";
		cin >> m_period;
		if (correctPeriodCheck()) {
			break;
		}
	}
}
void Inventory::inventoryOut() {					//해당 재료를 삭제
	strcpy_s(m_name, NAME_BYTE, "-");
	m_quantity = 0;
	m_period = 0;
}
void Inventory::inventoryOut(int num) {				//해당 재료를 해당 수량만큼 삭제
	if (num < m_quantity) {
		m_quantity = m_quantity - num;
	}
	else if (num = m_quantity) {
		strcpy_s(m_name, NAME_BYTE, "-");
		m_quantity = 0;
		m_period = 0;
	}
	else {
		cout << " 현재 가지고 있는 수량보다 많습니다." << endl;
	}
}
void Inventory::fileSave(Inventory** &inventory, char ID[15]) {		//빈칸을 제외하고 현재 목록을 파일 형태로 저장
	char filename[30];
	strcpy_s(filename, 15, ID);
	strcat_s(filename, 30, "inventory.txt");
	ofstream inventoryFile(filename);
	if (inventoryFile.is_open()) {
		inventoryFile << inventory[0]->m_name;
		inventoryFile << '\n';
		inventoryFile << inventory[0]->m_quantity;
		inventoryFile << '\n';
		inventoryFile << inventory[0]->m_period;
		for (int i = 1; i < Inventory::inventoryExistanceCheck(inventory); i++)
		{
			inventoryFile << '\n';
			inventoryFile << inventory[i]->m_name;
			inventoryFile << '\n';
			inventoryFile << inventory[i]->m_quantity;
			inventoryFile << '\n';
			inventoryFile << inventory[i]->m_period;
		}
		inventoryFile.close();
	}
	else {
		cout << "파일을 찾지 못했습니다.";
	}
}
bool Inventory::checkPeriod() {		//유통기한 검사.
	tm t;
	time_t present_time;

	present_time = time(NULL);
	localtime_s(&t, &present_time);
	if (m_period < (t.tm_year + 1900) * 10000 + (t.tm_mon + 1) * 100 + t.tm_mday) {
		return false;
	}
	else {
		return true;
	}
}
bool Inventory::correctPeriodCheck() {
	int count = 0;
	int num = m_period % 10000;
	if (num < 101 || num > 131) {
		count++;
	}
	if (num < 201 || num > 229) {
		count++;
	}
	if (!(num == 229 && (m_period / 10000) % 4 == 0)) {
		count++;
	}
	if (num < 301 || num > 331) {
		count++;
	}
	if (num < 401 || num > 430) {
		count++;
	}
	if (num < 501 || num > 531) {
		count++;
	}
	if (num < 601 || num > 630) {
		count++;
	}
	if (num < 701 || num > 731) {
		count++;
	}
	if (num < 801 || num > 831) {
		count++;
	}
	if (num < 901 || num > 930) {
		count++;
	}
	if (num < 1001 || num > 1031) {
		count++;
	}
	if (num < 1101 || num > 1130) {
		count++;
	}
	if (num < 1201 || num > 1231) {
		count++;
	}

	if (count == 13) {
		cout << " 올바른 날짜 입력이 아닙니다." << endl;
		return false;
	}
	return true;
}

//===============Food====클래스=함수들==========================
void mFood::setID(char ID[15]) {
	strcpy_s(m_ID, 15, ID);
}
void Food::setname(char name[])
{
	strcpy_s(m_name, NAME_BYTE, name);
}
void Food::setrecipe(char *recipe)
{
	strcpy_s(m_recipe[re_fill], RECIPE_BYTE, recipe);
	re_fill++;
}
void Food::setcalorie(int calorie)
{
	m_calorie = calorie;
}
void Food::setingredient(char *ingredient)
{
	strcpy_s(m_ingredient[in_fill], NAME_BYTE, ingredient);
	in_fill++;
}
void Food::showfood()
{
	cout << " 요리이름: " << m_name << endl;
	cout << " 요리순서: " << endl;
	for (int i = 0; i < re_fill; i++)
		cout << " " << m_recipe[i] << endl;
	cout << " 요리열량: " << m_calorie << endl;
	cout << " 사용재료: ";
	for (int i = 0; i < in_fill; i++)
		cout << m_ingredient[i] << " ";
	cout << endl;
}
void mFood::showfood()
{
	cout << m_ID << " 님의 요리" << endl;
	Food::showfood();
}
void Food::fSearch(int i, Inventory** inventory) {
	int count = 0;
	int listCount = 0;
	for (int j = 0; j < in_fill; j++)
	{
		for (int k = 0; k < _msize(inventory) / 4; k++) {
			if (!strcmp(m_ingredient[j], inventory[k]->returnName())) {
				count = 0;
				break;
			}
			else {
				count++;
			}
		}
		if (count == 0) {
			listCount++;
		}
	}
	if (listCount == in_fill) {
		cout << "│" << setw(2) << i << " ";
		cout << setw(10) << m_name << setw(25) << "│" << endl;		//##뭘 표현할 건지 적으세요.
	}
};

char* Food::returnIngredient(const int &i) {
	if (i < in_fill) {
		return m_ingredient[i];
	}
	else {
		return "--";
	}
}

void Cursor::gotoxy(int x, int y)
{
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}
void Cursor::CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

