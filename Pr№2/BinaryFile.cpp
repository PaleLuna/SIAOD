#include "BinaryFile.h"

/*******************************************************************PUBLIC********************************************************************/

BinaryFile::BinaryFile(string binFilePath, string textFilePath) { OpenNewFile(binFilePath, textFilePath); }
BinaryFile::BinaryFile(){}
BinaryFile::~BinaryFile() { Clear(); }

void BinaryFile::OpenNewFile(string binFilePath, string textFilePath)
{
	this->binFilePath = binFilePath;
	textFile.SetDirectory(textFilePath);

	//WriteAll();
	AnalizingFile();
}

/*---------------------------------------------------------------------------*/

void BinaryFile::WriteAll()
{
	Clear();
	OpenBinaryFileForWrite();

	int lineCount = textFile.GetRecordsCount();
	for (int i = 0; i < lineCount; i++)
	{
		Discipline* discipline = CreateNewDiscipline(textFile.GetLine(i));

		Record record;
		record.key = i;

		record.data = discipline;

		binFile.write((char*)&record, sizeof(record));
	}
	recordsCount = lineCount;
}

void BinaryFile::DelletAt(int key)
{
	string tempName = "temp.dat";
	fstream temp(tempName, ios::out | ios::binary);
	if (TryOpenBinaryFileForRead())
	{
		int i = 0;
		while (!binFile.eof())
		{
			Record record;
			binFile.read((char*)&record, sizeof(record));
			
			if (record.key != key)
			{
				record.key = i++;
				temp.write((char*)&record, sizeof(record));
			}
		}

		CloseFile();
		temp.close();

		if (remove(binFilePath.c_str()) != 0)
			printf("Ошибка удаления\n");

		if (rename(tempName.c_str(), binFilePath.c_str()))
		{
			printf("Файл не был переименован!\n");
			binFilePath = tempName;
		}
		
		recordsCount--;
	}
}
void BinaryFile::Clear()
{
	CloseFile();

	binFile.open(binFilePath, ios::out | ios::binary);
	recordsCount = 0;

	CloseFile();
}

void BinaryFile::Swap(int firstKey, int secondKey)
{
	Record* firstRecord = GetRecord(firstKey);
	Record* secondRecord = GetRecord(secondKey);

	string tempName = "temp.dat";
	fstream temp(tempName, ios::out | ios::binary);
	if (TryOpenBinaryFileForRead())
	{
		int i = 0;
		while (!binFile.eof())
		{
			Record record;
			binFile.read((char*)&record, sizeof(record));

			if (record.key == firstKey)
			{
				secondRecord->key = firstKey;
				temp.write((char*)secondRecord, sizeof(*secondRecord));
			}
			else if (record.key == secondKey)
			{
				firstRecord->key = secondKey;
				temp.write((char*)firstRecord, sizeof(*firstRecord));
			}
			else
				temp.write((char*)&record, sizeof(record));
		}

		CloseFile();
		temp.close();

		if (remove(binFilePath.c_str()) != 0)
			printf("Ошибка удаления\n");

		if (rename(tempName.c_str(), binFilePath.c_str()))
		{
			printf("Файл не был переименован!\n");
			binFilePath = tempName;
		}
	}
}

Discipline* BinaryFile::operator[](int key)
{
	Discipline* discipline = nullptr;
	bool keyIsCorrect = (key >= 0) && (key < recordsCount);

	if (TryOpenBinaryFileForRead() && keyIsCorrect)
	{
		Record tempRecord;

		while (!binFile.eof() && discipline == nullptr)
		{
			binFile.read((char*)&tempRecord, sizeof(tempRecord));

			if (tempRecord.key == key)
				discipline = tempRecord.data;
		}
	}
	return discipline;
}

/*******************************************************************PRIVATE******************************************************************/

/*---------------------------------------------------------------------------*/

Discipline* BinaryFile::CreateNewDiscipline(string lineWithData)
{
	stringstream ss(lineWithData);
	Discipline* newDiscipline = new Discipline();

	ss.get(newDiscipline->codeEducationalDirection, newDiscipline->MAX_STRING_SIZE, ' ');
	ss.get();

	ss.get(newDiscipline->disciplineCode, newDiscipline->MAX_STRING_SIZE, ' ');
	ss.get();

	ss.get(newDiscipline->name, newDiscipline->MAX_STRING_SIZE, ' ');
	ss.get();

	int i = 0;
	while (!ss.eof() && (i < newDiscipline->SEMESTERS_CAPACITY))
	{
		ss >> newDiscipline->semesters[i];
		ss.get();
		i++;
	}

	newDiscipline->semestersCount = i;

	return newDiscipline;
}

BinaryFile::Record* BinaryFile::GetRecord(int key)
{
	Record* record = nullptr;
	bool keyIsCorrect = (key >= 0) && (key < recordsCount);

	if (TryOpenBinaryFileForRead() && keyIsCorrect)
	{
		Record tempRecord;

		while (!binFile.eof() && record == nullptr)
		{
			binFile.read((char*)&tempRecord, sizeof(tempRecord));

			if (tempRecord.key == key)
				record = new Record(tempRecord);
		}
	}
	return record;
}

/*---------------------------------------------------------------------------*/

void BinaryFile::AnalizingFile()
{
	recordsCount = 0;
	CountingRecords();
}
void BinaryFile::CountingRecords()
{
	if (TryOpenBinaryFileForRead())
	{
		Record record;
		while (!binFile.eof())
			binFile.read((char*)&record, sizeof(record));

		recordsCount = record.key + 1;
	}
}

/*---------------------------------------------------------------------------*/

void BinaryFile::OpenBinaryFileForWrite()
{
	CloseFile();

	binFile.open(binFilePath, ios::app | ios::binary);
}
bool BinaryFile::TryOpenBinaryFileForRead()
{
	CloseFile();

	binFile.open(binFilePath, ios::in | ios::binary);

	return binFile.is_open();
}
void BinaryFile::CloseFile()
{
	if (binFile.is_open())
		binFile.close();
}