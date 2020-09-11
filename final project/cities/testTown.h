#pragma once
#include "town.h"

void testTownSetType()
{
	Town t;
	t.setType(TownType::rural);

	assert(t.getType() == TownType::rural
		&& "SetTypeTest");
}

void testTownVirtualPrint()
{
	Town t;
	t.setType(TownType::civic);
	std::ofstream outFile("testFile", std::ios::trunc);
	outFile << t;
	outFile.close();

	std::ifstream inFile("testFile");
	string start;
	inFile >> start;
	inFile.close();

	assert(start == "Civic"
		&& "VirtualPrintTest");
}

void runTownTests()
{
	testTownSetType();
	testTownVirtualPrint();
}