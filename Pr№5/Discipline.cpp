#include "Discipline.h"

Discipline::Discipline(const string& stringDiscription) { FormationStructure(stringDiscription); }
Discipline::Discipline(const Discipline& otherDiscipline) { operator=(otherDiscipline); }


Discipline::Discipline()
{
	this->disciplineName = string();
	this->disciplineCode = 0;
	this->educationDirCode = string();
	this->semesterNumber = 0;
}

Discipline::Discipline(const string& disciplineName, const int& disciplineCode, const string& educationDirCode, const int& semesterNumber)
{
	this->disciplineName = disciplineName;
	this->disciplineCode = disciplineCode;
	this->educationDirCode = educationDirCode;
	this->semesterNumber = semesterNumber;
}
void Discipline::operator=(const Discipline& otherDiscipline)
{
	this->disciplineName = otherDiscipline.disciplineName;
	this->disciplineCode = otherDiscipline.disciplineCode;
	this->educationDirCode = otherDiscipline.educationDirCode;
	this->semesterNumber = otherDiscipline.semesterNumber;
}

string* Discipline::GetDescription()
{
	stringstream discription;
	char disciplineCodeBuff[4];
	snprintf(disciplineCodeBuff, sizeof(disciplineCodeBuff), "%03d", disciplineCode);

	discription << "Наименование дисциплины: " << disciplineName << endl;
	discription << "Код дисциплины: " << string(disciplineCodeBuff) << endl;
	discription << "Код направления: " << educationDirCode << endl;
	discription << "Номер семестра: " << semesterNumber << endl;

	return new string(discription.str());
}

string Discipline::GetDisciplineName()
{
	return disciplineName;
}
string Discipline::GetEducationDirCode()
{
	return educationDirCode;
}
int Discipline::GetDisciplineCode()
{
	return disciplineCode;
}
int Discipline::GetSemesterNumber()
{
	return semesterNumber;
}

void Discipline::FormationStructure(const string& stringDiscipline)
{
	stringstream discription(stringDiscipline);

	discription >> disciplineName;
	discription >> disciplineCode;
	discription >> educationDirCode;

	discription >> semesterNumber;
}
