#include "HashTest.h"

void HashTest::Test()
{
	hashTable = new HashTable(37);
	bool isRun = true;

	while (isRun)
	{
		PrintMenu();
		WriteData();
		printf("��� �����: ");
		int action;
		cin >> action;

		switch (action)
		{
			case 0:
				isRun = false;
				break;
			case 1:
				WriteData();
				break;
			case 2:
				SaveAll();
				break;
			case 3:
				PrintAll();
				break;
			case 4:
				PrintElement();
				break;
			case 5:
				DeleteElement();
				break;
		default:
			printf("�������� �� ����������!\n");
			break;
		}
		printf("\n");
		system("pause>nul");
		system("cls");

	}
}

void HashTest::PrintMenu()
{
	TextFile menuText(menuTextPath);
	printf("%s\n", menuText.Read().c_str());
}

void HashTest::WriteData()
{
	BinaryFile binFile(binFilePath, directionListPath);
	binFile.WriteAll();
}

void HashTest::SaveAll()
{
	BinaryFile binFile(binFilePath, directionListPath);
	int i = 0;
	DirectionOfStudy* dirOfStudy = binFile[i++];

	while (dirOfStudy != nullptr)
	{
		hashTable->push(dirOfStudy->DirCodeToInt(), dirOfStudy);
		dirOfStudy = binFile[i++];
	}
}

void HashTest::PrintElement()
{
	string key;
	printf("������� ��� ����������� ���������� (X.X.X): ");

	cin.ignore();
	getline(cin, key);

	DirectionOfStudy* dirOfStudy = hashTable->get(ConvertStringToInt(key));

	if (dirOfStudy != nullptr)
		printf("%s\n",dirOfStudy->getInfo().c_str());
	else
		printf("������ �� �������!\n");
}

void HashTest::PrintAll()
{
	int size = 0;
	int* keys = hashTable->getKeys(size);

	if (size > 0)
		for (int i = 0; i < size; i++)
			printf("%s\n", hashTable->get(keys[i])->getInfo().c_str());
	else
		printf("������� �����!");
	
}

void HashTest::DeleteElement()
{
	string key;
	printf("������� ��� ����������� ���������� (X.X.X): ");

	cin.ignore();
	getline(cin, key);

	if (hashTable->deleteAtKey(ConvertStringToInt(key)))
	{
		printf("������� ������� ������!\n");
		BinaryFile binFile(binFilePath, directionListPath);
		binFile.DelletAt(ConvertStringToInt(key));
	}
	else
		printf("������ �� �������!\n");
}

int HashTest::ConvertStringToInt(string key)
{
	int resultKey = 0;
	int keySize = key.size();

	for(int i = 0; i < keySize; i++)
		resultKey += (keySize-i)*(int)key[i];

	return resultKey;
}
