#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class TextFile
{
public:
	TextFile(string fileDirectory);
	TextFile();
	~TextFile();

	void SetDirectory(string fileDirectory);

	string GetName();
	int GetRecordsCount();
	int GetWordCount();

	string Read();

	void Write(string text);
	void ClearRecords();

	string operator[](int code);

private:
	string fileDirectory;
	string nameFile;
	fstream file;

	int records = 0;
	int words = 0;

	void AnalyzingNewFile();

	bool TryOpenFileAsRead();
	void OpenFileAsWrite();

	void GenerateName();
	void CountingRecordsAndWordsInNewFile();
	void CountingWordsInNewRecords(string record);
};

