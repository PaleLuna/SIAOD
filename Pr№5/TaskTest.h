#pragma once

#include <string>

#include "BinaryFile.h"
#include "BinaryTree.h"
#include "SplayTree.h"

using namespace std;

class TaskTest
{
	public:
		TaskTest();
		void Test();

	private:
		string binFileName = "binFile.dat";
		string textFileName = "Disciplines.txt";

		string textFileWithMenu = "MainMenu.txt";
		string textFileWithSelectMenu = "TreeSelectMenu.txt";

		string mainMenuText;
		string selectMenuText;

		BinaryFile* binFile;

		int SelectTree();
		void MainActions();

		int GetAction();

		void WriteToFile();
		void FindRecord();
		void PrintAllRecord();

		void PrintAllRecordAsTree();

		void DeleteRecord();

		void SetMainMenu();
		void SetSelectMenu();
};

