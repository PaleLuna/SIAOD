#pragma once

#include "ITest.h"
#include "TextFile.h"
#include "CopyFile.h"

class TextFileTest: public ITest
{
	public:
		void Test();
		string GetName();

	private:
		string name = "TextFile";

		TextFile UITEXT;
		TextFile taskFile;

		void SetFilePath();
		void WriteToEnd();
		void ReadFileContent();
		void SearchByIndexInText();

		void PrintUI();
};

