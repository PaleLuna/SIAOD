#pragma once

#include "TextFile.h"
#include "BinaryFile.h"
#include "HashTable.h"

using namespace std;

class HashTest
{
	public:
		void Test();

	private:
		HashTable* hashTable;

		string directionListPath = "Education.txt";
		string binFilePath = "binFile.dat";
		string menuTextPath = "Menu.txt";

		void PrintMenu();
		
		void WriteData();
		void SaveAll();

		void PrintElement();
		void PrintAll();

		void DeleteElement();

		int ConvertStringToInt(string key);
};

