#include <iostream>
#include <ctime>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include <conio.h>
using namespace std;

#define KIND 10
#define LIST 40
#define RECIPE_BYTE 100
#define NAME_BYTE 20
#define MAX_MEM 10

class Ingredients {
private:
	char m_name[NAME_BYTE];
public:
	static void ingredientsLoad(Ingredients ingredients[KIND][LIST]) {
		char name[NAME_BYTE];
		int i = 0;
		int j = 0;
		ifstream ingredientFile("ingredients.txt");
		while (!ingredientFile.eof())
		{
			ingredientFile >> name;
			if (strcmp(name, "-") != 0) {
				strcpy_s(ingredients[i][j].m_name, NAME_BYTE, name);
				j++;
			}
			else {
				for (int k = j; k < LIST; k++)
				{
					strcpy_s(ingredients[i][k].m_name, NAME_BYTE, "-");
				}
				i++;
				j = 0;
			}
		}
		for (int n = i; n < KIND; n++)
		{
			for (int k = 0; k < LIST; k++)
			{
				strcpy_s(ingredients[n][k].m_name, NAME_BYTE, "-");
			}
		}		ingredientFile.close();
	}
	char* returnName();
};

class Inventory {
private:
	char m_name[NAME_BYTE];
	int m_quantity;
	int m_period;
public:
	Inventory() {}
	Inventory(char name[NAME_BYTE], int quantity, int period)
		: m_quantity(quantity), m_period(period) {
		strcpy_s(m_name, NAME_BYTE, name);
	}
	~Inventory() {}
	static void inventoryLoad(Inventory** &inventory, char ID[15]);
	static void showInventory(Inventory** &inventory);
	static void inventorySet(Inventory** &inventory);
	static int inventoryExistanceCheck(Inventory** &inventory);
	void inventoryIn(char* name);
	void inventoryOut();
	void inventoryOut(int num);
	static void fileSave(Inventory** &inventory, char ID[15]);
	char* returnName() { return m_name; }
	bool checkPeriod();
	bool correctPeriodCheck();
};

class Food {
protected:
	char m_name[NAME_BYTE];//요리이름
	char m_recipe[NAME_BYTE][RECIPE_BYTE];//요리순서
	int m_calorie;//요리열량
	char m_ingredient[10][NAME_BYTE];//사용재료
	int re_fill;//요리순서가 얼마나 되는지 저장한다.
	int in_fill;//사용재료가 몇개나 되는지 저장한다.
public:
	Food() :re_fill(0), in_fill(0){
		strcpy_s(m_name, NAME_BYTE, "--");
	}
	virtual void setID(char *ID) {}
	void setname(char name[]);//요리이름을 세팅한다.
	void setrecipe(char *recipe);//요리순서를 세팅한다.
	void setcalorie(int calorie);//요리열량을 세팅한다.
	void setingredient(char *ingredient);//사용재료를 세팅한다.
	virtual void showfood();
	char* returnIngredient(const int &i);

	~Food() {};
	void Food::fSearch(int i, Inventory** inventory);

	char* returnName(){ return m_name; };
	int returnCalorie(){ return m_calorie; }
};

class mFood : public Food {
private:
	char m_ID[15];
public:
	mFood() :Food() {
	}
	void setID(char ID[15]);
	void showfood();
};

class Calendar {
	char m_name[5][20];//만든 요리들의 이름들이 저장되는 배열
	int totalcalorie;//오늘 먹은 총 칼로리량
	int fillname;//만든 요리들이 얼마나 되는지 확인하기 위한 변수
public:
	Calendar() :fillname(0), totalcalorie(0){}
	void addfoodName(char*name);
	void addfoodCal(int cal);
	int returnFillname(){ return fillname; }
	int returnTotalcalorie(){ return totalcalorie; }
	char* returnM_name(int i){ return m_name[i]; }
	void showInfo(int day);
};

class Management {
private:
	Food *fo[10];//레시피 정보가 들어간다.
	Food *m_fo[100];//나만의 레시피 정보가 들어간다.
	int m_fofill;//나만의 레시피를 몇개나 만들었는지
	int m_recipeNum;
	//static int m_memberNum; //회원가입 사람 중 로그인 한 아이디가 몇번째인지
	char m_ID[15];
	Calendar calendar[31];
public:
	Management();
	Management(char* ID);
	~Management();
	char* getID() { return m_ID; }
	Management* mem[MAX_MEM]; //회원의 수
	static bool logIn(Management* m1);
	char* iSearch();		//재료를 서치할 함수, 대분류->소분류->재료명 형태의 검색구조(유사검색)
	void fSearch();		//요리를 서치할 함수, 요리명으로 검색
	void inventoryIn();
	void inventoryOut();
	void eat();			//먹기함수, 주로 달력 클래스에 정보를 전달
	Inventory** inventory;
	Ingredients ingredients[KIND][LIST];
	void showfood();//레시피들을 출력한다.
	void regfood();//나만의 레시피를 등록한다.



	void addfoodName(char*name);
	void addfoodCal(int cal);
	void calendarIn(char ID[15]);//txt파일에 저장되어있는 캘린더 정보를 불러온다 
	void calendarOut(char ID[15]);//txt파일에 캘린더 정보를 저장한다.
	void showCalday();
	void showCalWeek();
	void showCalMonth();
	
	void showTitleScreen()const;
};

class Cursor{
public:
	static void gotoxy(int x, int y);
	static void CursorView(char show);//커서숨기기
	static void textcolor(int color_number);
};
