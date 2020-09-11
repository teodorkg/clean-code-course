#pragma once
#include "capital.h"

void testCapitalAddInstitution()
{
	Capital& t = Capital::getInstance();
	bool newInst = t.addInstitution("Court house");
	assert(newInst
		&& "AddNewInstitutionTest");
}

void testCapitalAddInstitutionFail()
{
	Capital& t = Capital::getInstance();
	bool newInst = t.addInstitution("Court house");
	assert(!newInst
		&& "AddNewInstitutionTest already existing");
}

void testCapitalRemoveInstitution()
{
	Capital& t = Capital::getInstance();
	bool newInst = t.removeInstitution("Court house");
	assert(newInst
		&& "RemoveNewInstitutionTest");
}

void testCapitalRemoveInstitutionFail()
{
	Capital& t = Capital::getInstance();
	bool newInst = t.removeInstitution("Court house");
	assert(!newInst
		&& "RemoveNewInstitutionTest not existing");
}

void runCapitalTests()
{
	testCapitalAddInstitution();
	testCapitalAddInstitutionFail();
	testCapitalRemoveInstitution();
	testCapitalRemoveInstitutionFail();
}