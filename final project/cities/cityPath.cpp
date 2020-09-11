#include "cityPath.h"
#include "cityGraph.h"

CityPath::CityPath(const CityGraph* _city) : city(_city), distance(0) {}

CityPath::CityPath(const CityGraph* _city, uint crossrInd) : city(_city), distance(0)
{
	push_back(crossrInd);
}

CityPath::CityPath(const CityGraph* _city, string crossroad) : city(_city), distance(0)
{
	push_back(crossroad);
}

uint CityPath::getDist() const
{
	return distance;
}

string CityPath::operator[](uint ind)
{
	if (ind >= size())
		return "Index out of range";
	return crossrInPath[ind];
}

uint CityPath::size() const
{
	return crossrInPath.size();
}

uint CityPath::length() const
{
	if (size() == 0)
		return 0;
	return crossrInPath.size() - 1;
}

void CityPath::push_back(uint crossrInd)
{
	if (crossrInd >= city->crossroads.size())
	{
		std::cerr << "Bad indexation\n";
		return;
	}
	if (size() != 0)
	{
		distance += city->transitions[crossrInPathAsInts.back()][crossrInd];
	}
	crossrInPath.push_back(city->crossroads[crossrInd]);
	crossrInPathAsInts.push_back(crossrInd);
}

void CityPath::push_back(const string& crossroad)
{
	int crossrInd = city->getCrossrInd(crossroad);
	if (crossrInd == -1)
	{
		std::cerr << "No such crossroad\n";
		return;
	}
	push_back(crossrInd);
}

void CityPath::pop_back()
{
	if (size() < 0)
		return;
	uint end = crossrInPathAsInts.back();
	crossrInPath.pop_back();
	crossrInPathAsInts.pop_back();

	if (size() > 0)
	{
		uint start = crossrInPathAsInts.back();
		distance -= city->transitions[start][end];
	}
}

string CityPath::back() const
{
	return crossrInPath.back();
}

bool CityPath::empty()
{
	return crossrInPath.empty();
}

bool CityPath::contains(uint crossrInd) const
{
	return ::contains(crossrInPathAsInts, crossrInd) != -1;
}

bool CityPath::contains(string crossroad) const
{
	return ::contains(crossrInPath, crossroad) != -1;
}

std::ostream& operator<<(std::ostream& os, const CityPath& path)
{
	os << "Path dist: " << path.distance << '\n';
	for (string crossroad : path.crossrInPath)
		os << crossroad << ' ';
	os << '\n';
	return os;
}