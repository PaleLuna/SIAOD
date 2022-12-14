#include "BinaryFile.h"

/*******************************************************************PUBLIC********************************************************************/

BinaryFile::BinaryFile(string binFilePath, string textFilePath) { OpenNewFile(binFilePath, textFilePath); }
BinaryFile::BinaryFile() {}
BinaryFile::~BinaryFile() {}

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

	int countLine = textFile.GetRecordsCount();
	DirectionOfStudy* dirOfStudy = nullptr;

	for (int i = 0; i < countLine; i++)
	{
		dirOfStudy = new DirectionOfStudy(textFile.GetLine(i));

		for (int j = i+1; ; j++)
		{
			string newLine = textFile.GetLine(j);
			if (!newLine._Equal("}"))
				dirOfStudy->push(CreateNewDiscipline(newLine));
			else
			{
				i = j;
				break;
			}
		}

		Record record;
		record.index = recordsCount++;
		record.key = dirOfStudy->DirCodeToInt();
		record.data = new DirectionOfStudy(*dirOfStudy);

		binFile.write((char*)&record, sizeof(Record));
	}
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
				record.index = i++;
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

DirectionOfStudy* BinaryFile::operator[](int index)
{
	DirectionOfStudy* discipline = nullptr;
	bool keyIsCorrect = (index >= 0) && (index < recordsCount);

	if (TryOpenBinaryFileForRead() && keyIsCorrect)
	{
		Record tempRecord;

		while (!binFile.eof() && discipline == nullptr)
		{
			binFile.read((char*)&tempRecord, sizeof(tempRecord));

			if (tempRecord.index == index)
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

	ss >> newDiscipline->disciplineCode;
	ss >> newDiscipline->disciplineName;
	ss >> newDiscipline->semester;

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