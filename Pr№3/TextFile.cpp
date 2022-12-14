#include "TextFile.h"

//***************************************PUBLIC**********************************************

TextFile::TextFile(string fileDirectory) { SetDirectory(fileDirectory); }
TextFile::TextFile() {}
TextFile::~TextFile() { file.close(); }

void TextFile::SetDirectory(string fileDirectory)
{
	this->fileDirectory = fileDirectory;
	AnalyzingNewFile();
}

string TextFile::GetName() { return nameFile; }
int TextFile::GetRecordsCount() { return records; }
int TextFile::GetWordCount() { return words; }

string TextFile::Read()
{
	string text = string();

	if (TryOpenFileAsRead())
		getline(file, text, '\0');

	return text;
}

void TextFile::Write(string newRecord)
{
	OpenFileAsWrite();

	if (records > 1)
		newRecord.insert(0, "\n");

	file << newRecord;

	records++;
	CountingWordsInNewRecords(newRecord);
}
void TextFile::ClearRecords()
{
	if (file.is_open())
		file.close();

	file.open(fileDirectory, ios::out);
	records = 0;
	words = 0;
	file.close();
}

string TextFile::GetLine(int lineInd)
{
	string searchLine;
	if (TryOpenFileAsRead() && (lineInd < records))
	{
		while (lineInd >= 0 && getline(file, searchLine))
			lineInd -= ((searchLine.compare("") != 0) ? 1 : 0);
	}
	return((lineInd == -1) ? searchLine : string());
}

string TextFile::operator[](int index)
{
	string searchString;

	if (TryOpenFileAsRead() && (index < words))
	{
		string line;
		while ((index >= 0) && getline(file, line))
		{
			stringstream ss(line);
			while ((index >= 0) && getline(ss, searchString, ' '))
				index -= ((searchString.compare("") != 0) ? 1 : 0);
		}
	}

	return ((index == -1) ? searchString : string());
}

//***************************************PRIVATE*********************************************

void TextFile::OpenFileAsWrite()
{
	if (file.is_open())
		file.close();

	file.open(fileDirectory, ios::app);
}
bool TextFile::TryOpenFileAsRead()
{
	if (file.is_open())
		file.close();

	bool isOpen = false;
	file.open(fileDirectory, ios::in);

	if (file.is_open())
		isOpen = true;

	return isOpen;
}


void TextFile::AnalyzingNewFile()
{
	records = 0;
	words = 0;

	GenerateName();
	CountingRecordsAndWordsInNewFile();
}
void TextFile::GenerateName()
{
	nameFile = string();
	int strSize = fileDirectory.size();

	for (int i = strSize - 1; i > 0 && nameFile.empty(); i--)
		if (fileDirectory[i] == '/')
		{
			nameFile = fileDirectory.substr(i);
		}

	if (nameFile.empty())
		nameFile = fileDirectory;
}
void TextFile::CountingRecordsAndWordsInNewFile()
{
	records = 0;
	string record;

	if (TryOpenFileAsRead())
		while (getline(file, record, '\n'))
			if (!record.empty())
			{
				records++;
				CountingWordsInNewRecords(record);
			}
}
void TextFile::CountingWordsInNewRecords(string record)
{
	stringstream ss(record);
	string word;

	while (getline(ss, word, ' '))
		words += ((word.compare("") != 0) ? 1 : 0);
}