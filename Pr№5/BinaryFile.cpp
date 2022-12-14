#include "BinaryFile.h"

/*******************************************************************PUBLIC********************************************************************/

BinaryFile::BinaryFile(string binFilePath, string textFilePath) { OpenNewFile(binFilePath, textFilePath); }
BinaryFile::BinaryFile(string binFilePath, string textFilePath, Tree* treeSearch)
{
	this->treeSearch = treeSearch;
	OpenNewFile(binFilePath, textFilePath);
}
BinaryFile::BinaryFile() {}
BinaryFile::~BinaryFile() { if (treeSearch) delete treeSearch; }

void BinaryFile::OpenNewFile(string binFilePath, string textFilePath)
{
	this->binFilePath = binFilePath;
	textFile.SetDirectory(textFilePath);

	AnalizingFile();
}

/*---------------------------------------------------------------------------*/

void BinaryFile::WriteAll()
{
	Clear();
	OpenBinaryFileForWrite();

	int countLine = textFile.GetRecordsCount();
	Discipline* discipline = nullptr;

	int i = 0;
	for (; i < countLine; i++)
	{
		discipline = new Discipline(textFile[i]);
		Record newRecord(discipline->GetDisciplineCode(), i, discipline);

		binFile.write((char*)&newRecord, sizeof(Record));
		if(treeSearch)
			treeSearch->Add(discipline->GetDisciplineCode(), i);
	}

	recordsCount = i;
	if (treeSearch)
		treeSearch->Print();
}

bool BinaryFile::DeleteRecordByCode(int code)
{
	bool result = false;
	string tempName = "temp.dat";
	fstream temp(tempName, ios::out | ios::binary);

	if (TryOpenBinaryFileForRead())
	{
		int i = 0;
		Record record;
		binFile.read((char*)&record, sizeof(record));

		while (!binFile.eof())
		{
			binFile.read((char*)&record, sizeof(record));

			if (record.code != code)
			{
				record.line = i++;
				if (treeSearch)
					treeSearch->Add(record.data->GetDisciplineCode(), record.line);
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

		if (treeSearch)
		{
			treeSearch->DeleteItem(code);
			treeSearch->Print();
		}
		recordsCount--;

		result = true;
	}

	if (treeSearch)
		treeSearch->Print();
	return result;
}

int BinaryFile::GetRecordsCount()
{
	return recordsCount;
}

void BinaryFile::ShowTree()
{
	if (treeSearch)
		treeSearch->Print();
}

string* BinaryFile::FindByCode(int code)
{
	if (treeSearch)
	{
		string* result = operator[](treeSearch->Find(code));
		treeSearch->Print();

		return result;
	}

	return new string();
}

string* BinaryFile::operator[](int code)
{
	string* disciplineDiscription;
	Record* record = new Record();

	if (TryOpenBinaryFileForRead())
	{
		binFile.seekg((sizeof(Record) * code), ios::beg);
		binFile.read((char*)&*record, sizeof(Record));
	}

	disciplineDiscription = (record != nullptr ? record->data->GetDescription() : new string());

	return disciplineDiscription;
}

/*******************************************************************PRIVATE******************************************************************/

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

		recordsCount = record.code + 1;
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
void BinaryFile::Clear()
{
	CloseFile();

	binFile.open(binFilePath, ios::out | ios::binary);
	recordsCount = 0;

	CloseFile();
}

void BinaryFile::CloseFile()
{
	if (binFile.is_open())
		binFile.close();
}