#include <iostream>

#include "Tree.h"

using namespace std;

char* WordInput();
void ResizeWord(char*& buff);

int main()
{
	setlocale(LC_ALL, "ru");

	Tree tree(WordInput());
	tree.Print();
	tree.Rotate();
	printf("\n\n\nПоворот дерева\n");
	tree.Print();

	printf("\nЗначение самого левого узла: %c\n", tree.getLeft());

	char userChar;
	printf("Введите символ, путь до которого необходимо найти: ");
	cin >> userChar;

	printf("\nПуть до узла со значением %c: %i\n", userChar, tree.Find(userChar));

	int res = tree.FindMax();
	printf("\nМаксимальное значение среди всех листьев дерева: %i - %c\n", res, (char)res);

	return 0;
}

char* WordInput()
{
	int len = 50;
	char* buff = new char[len];

	printf("Введите слово: ");
	cin >> buff;

	if (strlen(buff) + 1 < len)
		ResizeWord(buff);

	return buff;
}

void ResizeWord(char*& buff)
{
	int newLen = strlen(buff) + 1;
	char* temp = new char[newLen];

	for (int i = 0; i < newLen - 1; i++)
		temp[i] = buff[i];
	temp[newLen - 1] = '\0';

	delete[] buff;
	buff = temp;
}
