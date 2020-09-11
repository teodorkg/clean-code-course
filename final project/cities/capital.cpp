#include "capital.h"

Capital& Capital::getInstance()
{
	static Capital instance;
	return instance;
}

bool Capital::addInstitution(string newInst)
{
	if (contains(institutions, newInst) == -1)
	{
		institutions.push_back(newInst);
		return true;
	}
	else
	{
		std::cerr << "Institution already exists\n";
		return false;
	}
}

bool Capital::removeInstitution(string oldInst)
{
	int instIndex = contains(institutions, oldInst);
	if (instIndex != -1)
	{
		institutions.erase(institutions.begin() + instIndex);
		return true;
	}
	else
	{
		std::cerr << "No such institution\n";
		return false;
	}
}

void Capital::print(std::ostream& os) const
{
	os << "Capital city\n";

	City::print(os);

	os << "Institutions:\n";
	uint size = institutions.size();
	for (int i = 0; i < size; i++)
		os << '\t' << institutions[i] << '\n';
}