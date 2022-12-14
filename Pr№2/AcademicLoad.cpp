#include "AcademicLoad.h"

void AcademicLoad::Test()
{
	textMenu.SetDirectory(textMenuPath);
	SetPaths();

	bool isRun = true;

	while (isRun)
	{
		DisplayMenu();
		printf("���� ��������: ");
		short numOfAction;
		cin >> numOfAction;

		switch (numOfAction)
		{
		case 0:
			isRun = false;
			break;
		case 1:
			SetPaths();
			break;
		case 2:
			binTable.WriteAll();
			break;
		case 3:
			GetDiscipline();
			break;
		case 4:
			PrintAll();
			break;
		case 5:
			DeleteAt();
			break;
		case 6:
			SwapRecord();
			break;
		case 7:
			PrintEducationDirectionWithDiscipline();
			break;
		case 8:
			binTable.Clear();
			break;
		default:
			printf("�������� �� ����������!\n");
			break;
		}
		system("pause > null");
		system("cls");
	}

}
string AcademicLoad::GetName() { return name; }

void AcademicLoad::SetPaths()
{
	printf("������� ���� ��� ��������� �����: ");
	cin >> binPath;
	printf("������� ���� ��� ���������� ����� � �������: ");
	cin >> textPath;

	binTable.OpenNewFile(binPath, textPath);
}

void AcademicLoad::PrintDescipline(Discipline* discipline)
{
	printf("Discipline code: %s\n", discipline->disciplineCode);
	printf("\tCode of educational direction: %s\n", discipline->codeEducationalDirection);
	printf("\tName: %s\n", discipline->name);
	printf("\tSemesters: [%i;%i]\n", discipline->semesters[0], discipline->semesters[1]);
	printf("--------------------------------------------------------------\n\n\n");

}
void AcademicLoad::PrintEducationDirectionWithDiscipline()
{
	string disciplineName;
	Discipline* discipline = binTable[0];

	int countEdDir = 0;;

	printf("������� ������������ ������� ����������: ");
	cin >> disciplineName;

	for (int i = 1; discipline != nullptr; i++)
	{
		if (string(discipline->name)._Equal(disciplineName) && discipline->semestersCount == 2)
			printf("%i: %s\n", ++countEdDir, discipline->codeEducationalDirection);

		discipline = binTable[i];
	}
	
	if (countEdDir == 0)
		printf("���������� �� �������!");
}
void AcademicLoad::PrintAll()
{
	int key = 0;
	Discipline* discipline = binTable[key++];

	while (discipline != nullptr)
	{
		PrintDescipline(discipline);
		discipline = binTable[key++];
	}
}

void AcademicLoad::GetDiscipline()
{
	int key;
	printf("������� ���������� ����� ����������: ");
	cin >> key;

	Discipline* discipline = binTable[key];

	if (discipline != nullptr)
		PrintDescipline(discipline);
	else
		printf("������ �� �������!\n");

	delete discipline;
}

void AcademicLoad::DeleteAt()
{
	printf("������� ���� ��������� ������: ");
	int key;
	cin >> key;

	binTable.DelletAt(key);
}

void AcademicLoad::SwapRecord()
{
	int firstKey, secondKey;
	printf("������� ������ �������, ������� ������� �������� �������: ");

	cin >> firstKey;
	cin >> secondKey;

	binTable.Swap(firstKey, secondKey);
}


void AcademicLoad::DisplayMenu(){ printf("%s", textMenu.Read().c_str()); }