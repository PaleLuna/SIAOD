#pragma once

#include "ITest.h"
#include "BinaryFile.h"


class AcademicLoad : public ITest
{
public:
	/*--------------------------------------------–≈¿À»«¿÷»ﬂ »Õ“≈–‘≈…—¿-------------------------------------------*/
	void Test() override;
	string GetName() override;

private:
	/*----------------------------------------------------œŒÀﬂ----------------------------------------------------*/
	string name = "Academic load";
	TextFile textMenu;
	string textMenuPath = "BinTableTest.txt";

	string binPath;
	string textPath;

	BinaryFile binTable;

	/*----------------------------------------------------Ã≈“Œƒ€--------------------------------------------------*/

	void SetPaths();

	void PrintDescipline(Discipline* discipline);
	void PrintEducationDirectionWithDiscipline();
	void PrintAll();


	void SwapRecord();

	void GetDiscipline();

	void DeleteAt();


	void DisplayMenu();
};

