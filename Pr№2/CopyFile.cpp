#include "CopyFile.h"

void CopyFile::Copy(TextFile& originFile)
{
	string path = "Copy";
	path.append(originFile.GetName());

	int totalWords = originFile.GetWordCount();
	int numWordsRecorded = 0;
	srand(time(NULL));

	TextFile copyFile(path);
	copyFile.ClearRecords();

	while (totalWords > 0)
	{
		string line; 
		int numWordsPerLine = 1 + rand() % totalWords;
		int numWordsToCopy = numWordsRecorded + numWordsPerLine;

		for (int i = numWordsRecorded; i < (numWordsToCopy-1); i++)
			line.append(originFile[i].append(" "));
		line.append(originFile[numWordsToCopy - 1]);

		copyFile.Write(line);

		numWordsRecorded += numWordsPerLine;
		totalWords -= numWordsPerLine;
	}
}
