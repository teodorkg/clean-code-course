#pragma once
#include "city.h"

enum TownType
{
	rural,
	civic,
	industrial
};

class Town : public City
{
public:
	void setType(TownType);
	TownType getType();

protected:
	virtual void print(std::ostream&) const;

private:
	TownType type;
};