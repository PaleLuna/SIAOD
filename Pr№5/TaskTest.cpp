#include "TaskTest.h"

TaskTest::TaskTest()
{
	SetMainMenu();
	SetSelectMenu();

	Test();
}

void TaskTest::Test()
{
	while (SelectTree())
	{
		MainActions();
	}
}

int TaskTest::SelectTree()
{
	if (binFile) delete binFile;

	printf("%s\n\n\n", selectMenuText.c_str());
	int action = GetAction();

	switch (action)
	{
		case 0:
			break;
		case 1:
			binFile = new BinaryFile(binFileName, textFileName, new BinaryTree);
			break;
		case 2:
			binFile = new BinaryFile(binFileName, textFileName, new SplayTree);
		default:
			break;
	}

	system("cls");
	return action;
}

void TaskTest::MainActions()
{
	bool run = true;

	while (run)
	{
		printf("%s\n\n\n", mainMenuText.c_str());

		switch (GetAction())
		{
			case 0:
				run = false;
				break;
			case 1:
				WriteToFile();
				break;
			case 2:
				FindRecord();
				break;
			case 3:
				PrintAllRecord();
				break;
			case 4:
				PrintAllRecordAsTree();
				break;
			case 5:
				DeleteRecord();

			default:
				break;
		}

		system("pause > nul");
		system("cls");
	}


}

int TaskTest::GetAction()
{
	int action;
	printf("Ваш выбор: ");
	cin >> action;

	return action;
}

void TaskTest::WriteToFile()
{
	binFile->WriteAll();
}

void TaskTest::FindRecord()
{
	int disciplineCode;
	printf("Введите код диспциплины: ");
	cin >> disciplineCode;

	printf("%s\n", binFile->FindByCode(disciplineCode)->c_str());
}

void TaskTest::PrintAllRecord()
{
	for(int i = 0; i < binFile->GetRecordsCount(); i++)
		printf("%s\n", binFile->operator[](i)->c_str());
}

void TaskTest::PrintAllRecordAsTree()
{
	binFile->ShowTree();
}

void TaskTest::DeleteRecord()
{
	int disciplineCode;
	printf("Введите код диспциплины: ");
	cin >> disciplineCode;

	if (binFile->DeleteRecordByCode(disciplineCode))
		printf("Запись успешно удалена!\n");
	else
		printf("Что-то пошло не так...");
}

void TaskTest::SetMainMenu()
{
	TextFile textFile(textFileWithMenu);
	mainMenuText = textFile.Read();
}

void TaskTest::SetSelectMenu()
{
	TextFile textFile(textFileWithSelectMenu);
	selectMenuText = textFile.Read();
}
