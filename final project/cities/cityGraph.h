#pragma once
#include "cityPath.h"

class CityGraph
{
public:
	void addRoad(string, string, uint);				//oneway road
	void pathsFromTo(string, string, vector<CityPath>&) const;					//return value is stored in the third argument
	CityPath EulerianPath() const;
	CityPath shortestPath(string, string) const;
	friend std::ostream& operator<<(std::ostream&, const CityGraph&);
	friend void open(const char*, CityGraph&);

private:
	vector<vector<uint>> transitions;
	vector<string> crossroads;

	void BFStoLevel(uint, uint, vector<CityPath>&) const;
	void addNextBFSLevel(vector<CityPath>&, uint&) const;
	bool walkedEveryEdge(bool**) const;
	int getCrossrInd(string) const;
	pair<int, int> getOddDegCrossrsInd(bool&) const;
	void enlarge();
	void pathsFromTo(uint, uint, CityPath&, vector<CityPath>&) const;
	void inOutDegree(vector<pair<uint, uint>>&) const;
	void trailGraph(uint, CityPath&, CityPath&, bool**) const;

	friend class CityPath;
};