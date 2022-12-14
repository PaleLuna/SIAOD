#include "TextFileTest.h"'

void TextFileTest::Test()
{
	UITEXT.SetDirectory("UIText.txt");
	PrintUI();

	unsigned short userInput;
	bool isRun = true;



	while (isRun)
	{
		printf("���� ��������: ");
		cin >> userInput;

		switch (userInput)
		{
		case 0:
			printf("�������...\n");
			isRun = false;
			break;

		case 1:
			SetFilePath();
			break;
		case 2:
			WriteToEnd();
			break;
		case 3:
			ReadFileContent();
			break;
		case 4:
			cout << taskFile.GetRecordsCount() << endl;
			break;
		case 5:
			printf("���������� ��������� (����): %i", taskFile.GetWordCount());
			break;
		case 6:
			SearchByIndexInText();
			break;
		case 7:
			CopyFile::Copy(taskFile);
			break;
		case 8:
			taskFile.ClearRecords();
			break;

		default:
			printf("�������� �� ����������!\n");
			break;
		}
		cout << endl;
	}
}

string TextFileTest::GetName()
{
	return name;
}

void TextFileTest::SetFilePath()
{
	string path;
	printf("������� ���� � �����: ");
	cin >> path;
	taskFile.SetDirectory(path);
}

void TextFileTest::WriteToEnd()
{
	string str;
	printf("������� ����� ��� ������:\n");
	cin.ignore();
	getline(cin, str, '\n');

	taskFile.Write(str);
}

void TextFileTest::ReadFileContent()
{
	string str = taskFile.Read();
	if (str.empty())
		printf("���� ���� ��� �� ����������!\n");
	else
		printf("%s\n", str.c_str());
}

void TextFileTest::SearchByIndexInText()
{
	printf("������� ������ �������� ��������: ");
	int index;
	cin >> index;

	string searchString = taskFile[index];

	if (!searchString.empty())
		printf("������� �������: %s", searchString.c_str());
	else
		printf("� ���������, ������ �� �������!");
}

void TextFileTest::PrintUI()
{
	string text = UITEXT.Read();
	if (!text.empty())
		printf("%s", text.c_str());
	else
		printf("������ ������ �����!\n");
}