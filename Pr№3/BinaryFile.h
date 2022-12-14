#pragma once

#include <fstream>
#include <string>

#include "TextFile.h"
#include "DirectionOfStudy.h"

using namespace std;

class BinaryFile
{
	public:
		/*---------------------------------------------------- ŒÕ—“–” “Œ–€---------------------------------------------*/

		BinaryFile(string binFilePath, string textFilePath);
		BinaryFile();
		~BinaryFile();

		/*----------------------------------------------------»Õ“≈–‘≈…—-----------------------------------------------*/

		void OpenNewFile(string binFilePath, string textFilePath);

		void WriteAll();
		void DelletAt(int key);
		void Clear();

		void Swap(int firstKey, int secondKey);

		/*----------------------------------------------------œ≈–≈√–”« »----------------------------------------------------*/

		DirectionOfStudy* operator[](int key);

	private:
		/*----------------------------------------------------—“–” “”–¿----------------------------------------------------*/
		struct Record
		{
			int index;
			int key;
			DirectionOfStudy* data;

			Record()
			{
				key = -1;
				data = nullptr;
			}

			Record(const Record& otherRecord)
			{
				this->key = otherRecord.key;
				this->data = otherRecord.data;
			}
		};

		/*----------------------------------------------------œŒÀﬂ----------------------------------------------------*/
		fstream binFile;
		TextFile textFile;

		string binFilePath;

		int recordsCount;

		/*----------------------------------------------------Ã≈“Œƒ€----------------------------------------------------*/

		Discipline* CreateNewDiscipline(string lineWithData);
		Record* GetRecord(int key);

		void AnalizingFile();
		void CountingRecords();

		void OpenBinaryFileForWrite();
		bool TryOpenBinaryFileForRead();

		void CloseFile();
};