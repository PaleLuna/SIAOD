#include <iostream>
#include <fstream>
#include <bitset>

//Вариант №5 (23 номер в списке)

using namespace std;

void ShowMenu();
void PrintResult(unsigned value, unsigned mask);
void PrintResult(unsigned value);
void ClearConsole();

unsigned MaskForStaticVariable(unsigned& mask); //Первое задание
unsigned MaskForDynamicVariable(unsigned& mask); //Второе задание
unsigned BitwiseMultiplication(); //Третье задание
unsigned BitDivision(); //Четвертое задание
unsigned SettingBitToOne(unsigned& mask); //Пятое задание
void SortByBits();


int main()
{
	setlocale(LC_ALL, "ru");

	ShowMenu();

	unsigned short task;
	unsigned mask = 0;
	bool isRun = true;

	while (isRun)
	{
		printf("Введите номер задания: ");
		cin >> task;
		cout << endl;

		switch (task)
		{
		case 0:
			cout << "Выходим..." << endl;
			isRun = !isRun;
			break;
		case 1:
			PrintResult(MaskForStaticVariable(mask), mask);
			break;
		case 2:
			PrintResult(MaskForDynamicVariable(mask), mask);
			break;
		case 3:
			PrintResult(BitwiseMultiplication());
			break;
		case 4:
			PrintResult(BitDivision());
			break;
		case 5:
			PrintResult(SettingBitToOne(mask), mask);
			break;
		case 6:
			SortByBits();
			break;
		case 7:
			ClearConsole();
			break;
		default:
			printf("Ошибка! Команды не существует\n");
			break;
		}
		cout << endl;
	}
}


unsigned MaskForStaticVariable(unsigned& mask)
{
	const unsigned variable = 0x2E; // 2E -> 46 в десятичной;
	mask = 0x28002; // 00...0010100...00;

	printf("Значение заданной переменной в десятичной СС: %i\n", variable);
	printf("Значение заданной переменной в шестнадцатеричной СС: %02X\n", variable);
	printf("Значение заданной переменной в двоичной СС: %s\n", bitset<32>(variable).to_string().c_str());

	return variable | mask;
}

unsigned MaskForDynamicVariable(unsigned& mask)
{
	unsigned variable;
	mask = 0b1111 << 2; //Побитово сдвигаем число 7 в двоичной СС вправо, получаем 11100

	printf("Введите целое число: ");
	cin >> variable;

	printf("Значение заданной переменной в двоичной СС: %s\n", bitset<32>(variable).to_string().c_str());

	return variable & (~mask);
}

unsigned BitwiseMultiplication()
{
	unsigned variable;
	const unsigned multiplier = 6; //В задании указан множитель 64, но нам нужна степень двойки для выполнения задания. В данном случае 64 = 2^6.

	printf("Введите умножаемое число: ");
	cin >> variable;

	printf("Значение заданной переменной в двоичной СС: %s\n", bitset<32>(variable).to_string().c_str());

	return variable << multiplier;
}

unsigned BitDivision()
{
	unsigned variable;
	const unsigned divider = 6; ////В задании указан делитель 64, но нам нужна степень двойки для выполнения задания. В данном случае 64 = 2^6.

	printf("Введите делимое число: ");
	cin >> variable;

	printf("Значение заданной переменной в двоичной СС: %s\n", bitset<32>(variable).to_string().c_str());

	return variable >> divider;
}

unsigned SettingBitToOne(unsigned& mask)
{
	unsigned variable;
	unsigned short bitNum;
	mask = 1 << 31;

	printf("Введите целочисленное значение в десятичной СС: ");
	cin >> variable;

	while (true)
	{
		printf("Введите номер бита, который следует установить в единицу. Диапазон от 0 до 32\n");
		printf("Бит №");
		cin >> bitNum;

		if ((bitNum <= 0) || (bitNum >= 32))
			printf("Ошибка! Номер бита не входит в обозначенный диапазон! Повторите попытку\n");
		else
			break;
	}

	mask = mask >> (31 - bitNum);

	printf("Значение заданной переменной в двоичной СС: %s\n", bitset<32>(variable).to_string().c_str());

	return variable & (~mask);
}

void SortByBits()
{
	int* array;
	bool* bits;

	int size;
	int maxNum;

	printf("Введите количество вводимых данных: ");
	cin >> size;
	printf("Введите размерность \"алфавита\": ");
	cin >> maxNum;

	array = new int[size];
	bits = new bool[maxNum];

	for (int i = 0; i < maxNum; i++)
		bits[i] = false;

	printf("Заполните массив уникальными целочисленными значениями\n");
	for (int i = 0; i < size; i++)
	{
		printf("array[%i] = ", i + 1);
		cin >> array[i];
		if (array[i] >= maxNum)
		{
			printf("Ошибка! Значение выходит за заданный диапазон. Повторите ввод\n");
			i--;
			continue;
		}
	}

	for (int i = 0; i < size; i++)
	{
		bits[array[i]] = true;
	}

	printf("Отсортированный массив:\n");
	for (int i = 0; i < maxNum; i++)
		if (bits[i])
			printf("%i ", i);

}

//----------------------------------------------------------------------------------------------------------------

void ShowMenu()
{
	ifstream menuText("Menu.txt");

	if (menuText.is_open())
	{
		char text[512];
		menuText.getline(text, 512, '\0');

		printf("%s\n\n", text);
	}
}

void PrintResult(unsigned value, unsigned mask)
{
	printf("Маска: %s\n", bitset<32>(mask).to_string().c_str());
	printf("Результат операции в двоичной СС: %s\n", bitset<32>(value).to_string().c_str());
	printf("Результат операции в десятичной СС: %i\n", value);
}

void PrintResult(unsigned value)
{
	printf("Результат операции в двоичной СС: %s\n", bitset<32>(value).to_string().c_str());
	printf("Результат операции в десятичной СС: %i\n", value);
}

void ClearConsole()
{
	system("cls");
	ShowMenu();
}