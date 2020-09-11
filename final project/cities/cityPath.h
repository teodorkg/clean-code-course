#pragma once
#include "include.h"

class CityGraph;

class CityPath
{
public:
	CityPath(const CityGraph*);
	CityPath(const CityGraph*, uint);
	CityPath(const CityGraph*, string);
	uint getDist() const;
	string operator[](uint);
	friend std::ostream& operator<<(std::ostream&, const CityPath&);
	uint size() const;
	uint length() const;	//number of edges
	void push_back(uint);				//Note that both push_back's push string and uint
	void push_back(const string&);		//=> no need to exec both every time we add
	void pop_back();
	string back() const;
	bool empty();
	bool contains(string) const;
	bool contains(uint) const;
private:
	const CityGraph* city;
	uint distance;
	vector<string> crossrInPath;
	vector<uint> crossrInPathAsInts;
};