#include "city.h"

void City::setName(string _name) 
{ 
	name = _name;
}

void City::setPopulation(uint n) 
{ 
	population = n;
}

void City::setMayor(string newMayor)
{
	mayor = newMayor;
}

void City::setCoordinates(float x, float y) 
{
	coordinates = std::make_pair(x, y);
}

string City::getMayor()
{
	return mayor;
}

string City::getName()
{
	return name;
}

pair<float, float> City::getCoordinates()
{
	return coordinates;
}

uint City::getPopulation()
{
	return population;
}

void City::addRoad(string start, string end, const uint dist)
{
	map.addRoad(start, end, dist);
}

void City::routesFromTo(string start, string end, vector<CityPath>& toReturn) const
{
	map.pathsFromTo(start, end, toReturn);
}

CityPath City::routeCrossingAllStreets()
{
	return map.EulerianPath();
}

CityPath City::shortestRoute(string start, string end)
{
	return map.shortestPath(start, end);
}

void City::open(const char* _name)
{
	::open(_name, map);
	name = _name;
}

void City::print(std::ostream& os) const
{
	os << name << "\n\n"
		<< coordinates.first << " " << coordinates.second
		<< "\nMayor: " << mayor
		<< "\nPopulation: " << population;
	os << '\n' << map << '\n';
}

std::ostream& operator<<(std::ostream& os, const City& city)
{
	city.print(os);
	return os;
}