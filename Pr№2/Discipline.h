#pragma once

#include <sstream>

using namespace std;

struct Discipline
{
	static const int MAX_STRING_SIZE = 100;
	static const int SEMESTERS_CAPACITY = 2;

	char codeEducationalDirection[MAX_STRING_SIZE];
	char disciplineCode[MAX_STRING_SIZE];
	char name[MAX_STRING_SIZE];

	int semesters[SEMESTERS_CAPACITY];
	int semestersCount;

	Discipline();
	Discipline(const Discipline& otherObj);

	void operator=(const Discipline& otherObj);
};

inline Discipline::Discipline(const Discipline& otherObj)
{
	operator=(otherObj);
}

inline Discipline::Discipline()
{
	codeEducationalDirection[0] = '\0';
	disciplineCode[0] = 0;
	name[0] = '\0';

	semestersCount = 2;
	for (int i = 0; i < semestersCount; i++)
		semesters[i] = 0;
}


inline void Discipline::operator=(const Discipline& otherObj)
{

	stringstream ss;
	ss << otherObj.codeEducationalDirection;
	ss >> this->codeEducationalDirection;

	ss.clear();
	ss << otherObj.disciplineCode;
	ss >> this->disciplineCode;

	ss.clear();
	ss << otherObj.name;
	ss >> this->name;

	this->semestersCount = otherObj.semestersCount;
	for (int i = 0; i < semestersCount; i++)
		this->semesters[i] = otherObj.semesters[i];
}