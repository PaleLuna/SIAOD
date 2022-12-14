#pragma once

#include <string>
#include <sstream>

using namespace std;

class Discipline
{
	public:
		Discipline();
		Discipline(const string& disciplineName, const int& disciplineCode, const string& educationDirCode, const int& semesterNumber);
		Discipline(const string& stringDiscription);
		Discipline(const Discipline& otherDiscipline);

		void operator=(const Discipline& otherDiscipline);

		string* GetDescription();

		string GetDisciplineName();
		string GetEducationDirCode();
		int GetDisciplineCode();
		int GetSemesterNumber();

	private:
		string disciplineName;
		string educationDirCode;

		int disciplineCode;
		int semesterNumber;

		void FormationStructure(const string& stringDiscipline);
};

