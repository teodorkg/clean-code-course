#include "town.h"

void Town::setType(TownType t)
{
	type = t;
}

TownType Town::getType()
{
	return type;
}

void Town::print(std::ostream& os) const
{
	switch (type)
	{
	case rural: os << "Rural ";
		break;
	case civic: os << "Civic ";
		break;
	case industrial: os << "Industrial ";
		break;
	}
	os << "town\n";
	City::print(os);
}