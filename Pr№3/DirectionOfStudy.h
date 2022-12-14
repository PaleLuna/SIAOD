#pragma once

#include <vector>
#include <string>

using namespace std;

class Discipline
{
	public:
		string disciplineName;
		string disciplineCode;
		unsigned short semester;

		Discipline(){
			semester = 0;
			disciplineCode = string();
			disciplineName = string();
		}
		Discipline(string disciplineName, string disciplineCode, unsigned short semester)
		{
			this->disciplineName = disciplineName;
			this->disciplineCode = disciplineCode;
			this->semester = semester;
		}
		Discipline(const Discipline& otherObj)
		{
			operator=(otherObj);
		}

		void operator=(const Discipline& otherObj)
		{
			this->disciplineName = otherObj.disciplineName;
			this->disciplineCode = otherObj.disciplineCode;
			this->semester = otherObj.semester;
		}
};

class DirectionOfStudy
{
	public:
		DirectionOfStudy();
		DirectionOfStudy(string directionCode);
		DirectionOfStudy(const DirectionOfStudy& otherObj);
		~DirectionOfStudy();

		void push(Discipline* newDiscp);

		void setDirectionCode(string directionCode);
		string getDirectionCode();
		int DirCodeToInt();

		string getInfo();

		Discipline* operator[](int index);

	private:
		vector<Discipline> disciplines;
		string directionCode;
		
};
