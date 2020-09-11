#pragma once
#include "city.h"

void testCitySetName()
{
	City c;
	c.setName("Sofia");

	assert(c.getName() == "Sofia" 
		&& "CitySetNameTest");
}

void testCitySetMayor()
{
	City c;
	c.setMayor("BB");

	assert(c.getMayor() == "BB" 
		&& "CitySetMayorTest");
}

void testCitySetPopulation()
{
	City c;
	c.setPopulation(1200);

	assert(c.getPopulation() == 1200 
		&& "CitySetPopulationTest");
}

void testCitySetCoordiantes()
{
	City c;
	c.setCoordinates(41.2, 42);

	assert(c.getCoordinates().first <= 41.21
		&& c.getCoordinates().first >= 41.19
		&& c.getCoordinates().second == 42 
		&&"CitySetMayorTest");
}

void testCityAddRoad()
{
	City c;
	c.addRoad("Popa", "Garibaldi", 240);

	vector<CityPath> routes;
	c.routesFromTo("Popa", "Garibaldi", routes);

	assert(routes[0].getDist() == 240
		&& "CityAddRoadTest");
}

void testCityRoutesFromTo()
{
	City c;
	c.addRoad("A", "B", 3);
	c.addRoad("B", "C", 3);
	c.addRoad("A", "C", 3);

	vector<CityPath> routes;
	c.routesFromTo("A", "C", routes);

	assert(routes[0].getDist() == 6
		&& routes[1].getDist() == 3
		&& "CityRoutesFromToTest");
}

void testCityAllStreetsRoute()
{
	City c;
	c.addRoad("A", "B", 2);
	c.addRoad("B", "C", 3);
	c.addRoad("C", "A", 1);

	CityPath p = c.routeCrossingAllStreets();
	assert(!p.empty()
		&& "CityEulerCycleTest1");
}

void testCityAllStreetsRouteEmpty()
{
	City c;
	c.addRoad("A", "B", 2);
	c.addRoad("B", "C", 3);
	c.addRoad("C", "B", 1);
	c.addRoad("C", "D", 4);

	CityPath p = c.routeCrossingAllStreets();
	assert(p.empty()
		&& "CityEulerCycleTest2");
}

void testCityShorestRoute()
{
	City c;
	c.addRoad("A", "D", 4);
	c.addRoad("A", "B", 1);
	c.addRoad("B", "C", 1);
	c.addRoad("C", "D", 1);

	CityPath p = c.shortestRoute("A", "D");
	assert(p.getDist() == 3
		&& "ShortestRouteTest");
}

void testCityOpen()
{
	std::ofstream file("testFile", std::ios::trunc);
	file << "A B 3 C 5\n" << "B C 1\n" << std::endl;
	file.close();
	City c;
	c.open("testFile");

	CityPath p = c.shortestRoute("A", "C");
	assert(p.getDist() == 4
		&& "ShortestRouteTest");
}

void runCityTests()
{
	testCitySetName();
	testCitySetCoordiantes();
	testCitySetMayor();
	testCitySetPopulation();
	testCityAddRoad();
	testCityRoutesFromTo();
	testCityAllStreetsRoute();
	testCityAllStreetsRouteEmpty();
	testCityShorestRoute();
	testCityOpen();
}