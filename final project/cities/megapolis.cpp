#include "megapolis.h"

void Megapolis::setEconomicInd(uint _gdp, uint _salary)
{
	econInd.GDP = _gdp;
	econInd.avgNetSalary = _salary;
}

void Megapolis::print(std::ostream& os) const
{
	City::print(os);
	os << "Economic indicators:\n"
		<< "\tnominal GDP: " << econInd.GDP
		<< "\tAvg net salary: " << econInd.avgNetSalary
		<< '\n';
}