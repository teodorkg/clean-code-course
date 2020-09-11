#pragma once
#include "cityGraph.h"

class City
{
public:
	void setName(string);
	void setMayor(string);
	void setPopulation(uint);
	void setCoordinates(float, float);

	string getName();
	string getMayor();
	pair<float, float> getCoordinates();
	uint getPopulation();

	//Related to CityGraph
	void addRoad(string, string, const uint);				//oneway road
	void routesFromTo(string, string, vector<CityPath>&) const;			//return value is stored in the third argument
	CityPath routeCrossingAllStreets();
	CityPath shortestRoute(string, string);
	void open(const char*);
	friend std::ostream& operator<<(std::ostream&, const City&);

protected:
	virtual void print(std::ostream&) const;

private:
	string name;
	string mayor;
	int population;
	pair<float, float> coordinates;
	CityGraph map;

};


