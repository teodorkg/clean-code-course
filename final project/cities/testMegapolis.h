#pragma once
#include "megapolis.h"

void testMegapolisVirtualPrint()
{
	Megapolis saopaulo;
	saopaulo.setEconomicInd(350, 700);

	std::ofstream outFile("testFile", std::ios::trunc);
	outFile << saopaulo;
	outFile.close();

	int gdp, salary;
	std::ifstream inFile("testFile");
	inFile.seekg(-25, inFile.end);
	inFile >> gdp;
	inFile.seekg(-5, inFile.end);
	inFile >> salary;
	inFile.close();

	assert(gdp == 350
		&& salary == 700
		&& "MegapolisVirtualPrintTest");
}

void runMegapolisTests()
{
	testMegapolisVirtualPrint();
}