#include "DirectionOfStudy.h"

DirectionOfStudy::DirectionOfStudy(){}
DirectionOfStudy::~DirectionOfStudy(){}

void DirectionOfStudy::push(Discipline* newDiscp)
{
	disciplines.push_back(*newDiscp);
}

DirectionOfStudy::DirectionOfStudy(string directionCode) {setDirectionCode(directionCode);}

DirectionOfStudy::DirectionOfStudy(const DirectionOfStudy& otherObj)
{
	setDirectionCode(otherObj.directionCode);
	disciplines = otherObj.disciplines;
}


void DirectionOfStudy::setDirectionCode(string directionCode){ this->directionCode = directionCode; }

string DirectionOfStudy::getDirectionCode(){ return directionCode; }

int DirectionOfStudy::DirCodeToInt()
{
	int resultKey = 0;
	int keySize = directionCode.size();

	for (int i = 0; i < keySize; i++)
		resultKey +=  (keySize-i)*(int)directionCode[i];

	return resultKey;
}

string DirectionOfStudy::getInfo()
{
	string result = directionCode + "\n";

	int numOfDiscipline = disciplines.size();
	for(int i = 0; i < numOfDiscipline; i++)
	{
		string tempString = disciplines[i].disciplineCode;
		tempString += " " + disciplines[i].disciplineName;
		tempString += " " + to_string(disciplines[i].semester);

		result += tempString + "\n";
	}

	return result;
}

Discipline* DirectionOfStudy::operator[](int index)
{ 
	return (( (index >= 0) && (index < disciplines.size()) ) ? &disciplines.at(index) : nullptr); 
}
