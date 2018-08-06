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
	char m_name[NAME_BYTE];//�丮�̸�
	char m_recipe[NAME_BYTE][RECIPE_BYTE];//�丮����
	int m_calorie;//�丮����
	char m_ingredient[10][NAME_BYTE];//������
	int re_fill;//�丮������ �󸶳� �Ǵ��� �����Ѵ�.
	int in_fill;//�����ᰡ ��� �Ǵ��� �����Ѵ�.
public:
	Food() :re_fill(0), in_fill(0){
		strcpy_s(m_name, NAME_BYTE, "--");
	}
	virtual void setID(char *ID) {}
	void setname(char name[]);//�丮�̸��� �����Ѵ�.
	void setrecipe(char *recipe);//�丮������ �����Ѵ�.
	void setcalorie(int calorie);//�丮������ �����Ѵ�.
	void setingredient(char *ingredient);//�����Ḧ �����Ѵ�.
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
	char m_name[5][20];//���� �丮���� �̸����� ����Ǵ� �迭
	int totalcalorie;//���� ���� �� Į�θ���
	int fillname;//���� �丮���� �󸶳� �Ǵ��� Ȯ���ϱ� ���� ����
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
	Food *fo[10];//������ ������ ����.
	Food *m_fo[100];//������ ������ ������ ����.
	int m_fofill;//������ �����Ǹ� ��� ���������
	int m_recipeNum;
	//static int m_memberNum; //ȸ������ ��� �� �α��� �� ���̵� ���°����
	char m_ID[15];
	Calendar calendar[31];
public:
	Management();
	Management(char* ID);
	~Management();
	char* getID() { return m_ID; }
	Management* mem[MAX_MEM]; //ȸ���� ��
	static bool logIn(Management* m1);
	char* iSearch();		//��Ḧ ��ġ�� �Լ�, ��з�->�Һз�->���� ������ �˻�����(����˻�)
	void fSearch();		//�丮�� ��ġ�� �Լ�, �丮������ �˻�
	void inventoryIn();
	void inventoryOut();
	void eat();			//�Ա��Լ�, �ַ� �޷� Ŭ������ ������ ����
	Inventory** inventory;
	Ingredients ingredients[KIND][LIST];
	void showfood();//�����ǵ��� ����Ѵ�.
	void regfood();//������ �����Ǹ� ����Ѵ�.



	void addfoodName(char*name);
	void addfoodCal(int cal);
	void calendarIn(char ID[15]);//txt���Ͽ� ����Ǿ��ִ� Ķ���� ������ �ҷ��´� 
	void calendarOut(char ID[15]);//txt���Ͽ� Ķ���� ������ �����Ѵ�.
	void showCalday();
	void showCalWeek();
	void showCalMonth();
	
	void showTitleScreen()const;
};

class Cursor{
public:
	static void gotoxy(int x, int y);
	static void CursorView(char show);//Ŀ�������
	static void textcolor(int color_number);
};
