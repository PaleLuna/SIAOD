#include <iostream>

#include "ITest.h"
#include "TextFileTest.h"
#include "AcademicLoad.h"

using namespace std;

ITest* task = new TextFileTest();

void ChoiseTask();

//------------------------------------------------------------------------------------------------------------------------

int main()
{
	setlocale(LC_ALL, "ru");
	

	bool isRun = true;

	while (isRun)
	{
		printf("0: Завершить программу.\n");
		printf("1: Запустить тестирование.\n");
		printf("2: Выбор задания.\n");

		short action;
		printf("Текущее задание: %s\n\n", task->GetName().c_str());
		printf("Ваш выбор: ");
		cin >> action;

		switch (action)
		{
			case 0:
				printf("Выходим...");
				isRun = false;
				break;
			case 1:
				system("cls");
				task->Test();
				break;
			case 2:
				ChoiseTask();
				break;
		default:
			break;
		}
		
		system("cls");
	}
}

void ChoiseTask()
{
	printf("1: TextFile.\n");
	printf("2: Academic load.\n");

	bool isRun = true;

	short action;
	printf("Ваш выбор: ");
	cin >> action;

	switch (action)
	{
		case 1:
			task = new TextFileTest();
			break;
		case 2:
			task = new AcademicLoad();
			break;
		default:
			break;
	}
}