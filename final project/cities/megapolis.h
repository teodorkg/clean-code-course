#pragma once
#include "city.h"

struct EconomicIndicators
{
	uint GDP;
	uint avgNetSalary;

	EconomicIndicators() : GDP(0), avgNetSalary(0) {}
};

class Megapolis : public City
{
public:
	void setEconomicInd(uint, uint);

protected:
	virtual void print(std::ostream&) const;

private:
	EconomicIndicators econInd;
};