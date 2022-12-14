#pragma once

#include <ios>
#include <fstream>
#include <string>

#include "TextFile.h"
#include "Discipline.h"

#include "Tree.h";
#include "BinaryTree.h"

using namespace std;

class BinaryFile
{
	/*----------------------------------------------------—“–” “”–¿----------------------------------------------------*/
	struct Record
	{
		int code;
		int line;
		Discipline* data;

		Record()
		{
			code = -1;
			line = -1;
			data = nullptr;
		}
		Record(int code, int line, Discipline* data)
		{
			this->code = code;
			this->line = line;
			this->data = data;
		}

		Record(const Record& otherRecord)
		{
			this->code = otherRecord.code;
			this->data = otherRecord.data;
		}
	};

	public:
		/*---------------------------------------------------- ŒÕ—“–” “Œ–€---------------------------------------------*/

		BinaryFile(string binFilePath, string textFilePath);
		BinaryFile(string binFilePath, string textFilePath, Tree* treeSearch);
		BinaryFile();
		~BinaryFile();

		/*----------------------------------------------------»Õ“≈–‘≈…—-----------------------------------------------*/

		void OpenNewFile(string binFilePath, string textFilePath);

		void WriteAll();
		bool DeleteRecordByCode(int code);

		int GetRecordsCount();

		void ShowTree();
		

		/*----------------------------------------------------œ≈–≈√–”« »----------------------------------------------------*/

		string* FindByCode(int code);
		string* operator[](int key);


	private:
	

		/*----------------------------------------------------œŒÀﬂ----------------------------------------------------*/
		fstream binFile;
		TextFile textFile;

		string binFilePath;

		int recordsCount;

		Tree* treeSearch;

		/*----------------------------------------------------Ã≈“Œƒ€----------------------------------------------------*/


		void AnalizingFile();
		void CountingRecords();

		void OpenBinaryFileForWrite();
		bool TryOpenBinaryFileForRead();
		void Clear();

		void CloseFile();
};