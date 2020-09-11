#include "cityGraph.h"
#include <cmath>

int getMaxStrLen(const vector<string>& v)
{
	int max = 0;
	int vSize = v.size();
	for (size_t i = 0; i < vSize; i++)
		if (v[i].length() > max)
			max = v[i].length();
	return max;
}

int getMaxNumLen(const vector<vector<uint>>& transitions)
{
	int size = transitions.size();
	int max = 1;
	int numLen;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			numLen = 1;
			if (transitions[i][j] != 0)
				numLen = std::log10(transitions[i][j]) + 1;
			if (numLen > max)
				max = numLen;
		}
	}
	return max;
}

void printPaths(vector<CityPath> paths)
{
	for (uint i = 0; i < paths.size(); i++)
	{
		std::cout << " Path: ";
		for (uint j = 0; j < paths[i].size(); j++)
			std::cout << std::setw(12) << paths[i][j] << " ";
		std::cout << "    Length: " << paths[i].getDist() << "\n";
	}
}

void CityGraph::enlarge()
{
	int oldSize = transitions.size();
	transitions.push_back(vector<uint>(oldSize + 1, 0));	//adds new row with 0
	for (int i = 0; i < oldSize; i++)						//adds new col with 0
		transitions[i].push_back(0);
}

void CityGraph::addRoad(string crossr1, string crossr2, uint distance)
{
	int ind1 = getCrossrInd(crossr1);
	if (ind1 == -1)
	{
		crossroads.push_back(crossr1);
		enlarge();
		ind1 = crossroads.size() - 1;
	}
	int ind2 = getCrossrInd(crossr2);
	if (ind2 == -1)
	{
		crossroads.push_back(crossr2);
		enlarge();
		ind2 = crossroads.size() - 1;
	}
	transitions[ind1][ind2] = distance;
}

void open(const char* file, CityGraph& city)
{
	string crossrFrom, crossrTo;
	int distance;
	std::ifstream fileStream(file);
	if (!fileStream.is_open())
	{
		std::cerr << "Could not open file\n";
		return;
	}
	while (!fileStream.eof())
	{
		fileStream >> crossrFrom;
		city.addRoad(crossrFrom, crossrFrom, 0);
		while (!fileStream.eof() && fileStream.peek() != '\n')
		{
			fileStream >> crossrTo;
			fileStream.ignore();
			fileStream >> distance;
			city.addRoad(crossrFrom, crossrTo, distance);
		}
		if (fileStream.peek() == '\n')
			fileStream.ignore();
	}
	fileStream.close();
}

std::ostream& operator<<(std::ostream& os, const CityGraph& city)
{
	int crossrsSize = city.crossroads.size();
	int maxNameLen = getMaxStrLen(city.crossroads);
	int maxDistLen = getMaxNumLen(city.transitions);
	int width = std::max(maxDistLen, maxNameLen);
	string emptySpace(width + 1, ' ');
	os << emptySpace;
	for (int i = 0; i < crossrsSize; i++)
		os << std::setw(width + 1) << city.crossroads[i];
	os << '\n';
	for (int i = 0; i < crossrsSize; i++)
	{
		os << std::setw(width + 1) << city.crossroads[i];
		for (int j = 0; j < crossrsSize; j++)
		{
			os << std::setw(width + 1) << city.transitions[i][j];
		}
		os << '\n';
	}
	return os;
}

//private method	
void CityGraph::pathsFromTo(uint start, uint end, CityPath& crrPath, vector<CityPath>& paths) const
{								  
	if (start == end && crrPath.size() > 1)								//Note that:									  
	{																	//1. crrPath is {start} in the first call
		paths.push_back(crrPath);										//2. Gives paths without crossroad repetition
		return;
	}
	uint size = transitions.size();
	for (uint i = 0; i < size; i++)
	{
		if (transitions[start][i] != 0 && !crrPath.contains(i))
		{
			crrPath.push_back(i);
			pathsFromTo(i, end, crrPath, paths);	
			crrPath.pop_back();
		}
	}
}

//Gives all paths from A to B without crossroad repetition
void CityGraph::pathsFromTo(string str1, string str2, vector<CityPath>& paths) const
{
	int start = getCrossrInd(str1);
	int end	  = getCrossrInd(str2);
	if (start == -1 || end == -1)
		return;
	CityPath crrPath(this, start);
	pathsFromTo(start, end, crrPath, paths);
}  

void CityGraph::inOutDegree(vector<pair<uint, uint>>& IOdegs) const
{
	uint size = transitions.size();
	IOdegs.assign(size, pair<uint,uint>(0,0));
	for (uint i = 0; i < size; i++)
	{
		for (uint j = 0; j < size; j++)
		{
			if (transitions[i][j] != 0)
			{
				IOdegs[i].first++;
				IOdegs[j].second++;
			}
		}
	}
}

pair<int, int> CityGraph::getOddDegCrossrsInd(bool& moreThan2OddDeg) const
{
	pair<int, int> oddDegCrossrsInd(-1, -1);
	vector<pair<uint, uint>> IOdegs;
	inOutDegree(IOdegs);
	int size = IOdegs.size();
	pair<uint, uint> IOdeg;
	for (int i = 0; i < size; i++)
	{
		IOdeg = IOdegs[i];
		if (IOdeg.first != IOdeg.second)
		{
			if (IOdeg.first + 1 == IOdeg.second && oddDegCrossrsInd.first == -1) //one more IN && still not met such with more IN
				oddDegCrossrsInd.first = i;
			else if (IOdeg.first == IOdeg.second + 1 && oddDegCrossrsInd.second == -1) //one more OUT && still not met such
				oddDegCrossrsInd.second = i;
			else
			{
				moreThan2OddDeg = true;
				return oddDegCrossrsInd;
			}
		}
	}
	return oddDegCrossrsInd;
}

//Eulerian path exists iff all nodes have equal In and Out degree or 
//one node has (In deg + 1 = Out deg) and another one has (In deg = Out deg + 1) 
//=> they are the start and the end point of such path
CityPath CityGraph::EulerianPath() const
{
	CityPath EulerPath(this);
	bool moreThan2OddDeg = false;
	pair<int, int> oddDegCrossrs = getOddDegCrossrsInd(moreThan2OddDeg);

	if (moreThan2OddDeg)
		return EulerPath;

	uint size = transitions.size();
	bool** walkedOver = new bool*[size]; //to be used in trailGraph
	for (int i = 0; i < size; i++)
	{
		walkedOver[i] = new bool[size];
		for (int j = 0; j < size; j++)
		{
			if (transitions[i][j])
				walkedOver[i][j] = false;
			else
				walkedOver[i][j] = true;
		}
	}

	CityPath crrPath(this);
	if (oddDegCrossrs.first == -1 && oddDegCrossrs.second == -1)
	{
		crrPath.push_back(0);		//Each node will work fine as a start node
		trailGraph(0, crrPath, EulerPath, walkedOver);
		return EulerPath;
	}
	if (oddDegCrossrs.first == -1 || oddDegCrossrs.second == -1)	//Note: T||T enters the previous if => only T||F and F||T enter here
		return EulerPath;

	crrPath.push_back(oddDegCrossrs.second);	//On this line we know both oddDegCrossr have index values (!= -1)
	trailGraph(oddDegCrossrs.second, crrPath, EulerPath, walkedOver);	//=> we start with the one with more OUT (oddDegCrossr2)

	for (int i = 0; i < size; i++)
		delete walkedOver[i];
	delete walkedOver;

	return EulerPath;
}

void CityGraph::trailGraph(uint start, CityPath& crrPath, CityPath& EulerPath, bool** walkedEdges) const
{
	uint size = transitions.size();
	if (walkedEveryEdge(walkedEdges))
	{
		EulerPath = crrPath;
		return;
	}
	for (uint i = 0; i < size; i++)
	{
		if (transitions[start][i] != 0 && !walkedEdges[start][i])
		{			
			crrPath.push_back(crossroads[i]);
			walkedEdges[start][i] = true;
			trailGraph(i, crrPath, EulerPath, walkedEdges);
			if (EulerPath.size() > 0) //== found Euler path
			{
				return;
			}
			walkedEdges[start][i] = false;
			crrPath.pop_back();
		}
	}
}

bool CityGraph::walkedEveryEdge(bool** walkedEdges) const
 {
	 int size = transitions.size();
	 for (int i = 0; i < size; i++)
		 for (int j = 0; j < size; j++)
			 if (!walkedEdges[i][j])
				 return false;
	 return true;
 }

void CityGraph::addNextBFSLevel(vector<CityPath>& paths, uint& pathInd) const
{
	CityPath crrPath(this);
	string lastCrossr;
	uint size = transitions.size();
	uint lastCrossrInd;
	uint lastPathInd = paths.size() - 1;
	while (pathInd <= lastPathInd)
	{
		crrPath = paths[pathInd];
		lastCrossr = crrPath.back();
		lastCrossrInd = getCrossrInd(lastCrossr);
		for (uint i = 0; i < size; i++)
		{
			if (transitions[lastCrossrInd][i] != 0)
			{
				crrPath.push_back(i);
				paths.push_back(crrPath);
				crrPath.pop_back();
			}
		}
		pathInd++;
	}
}

void CityGraph::BFStoLevel(uint start, uint level, vector<CityPath>& paths) const
{
	uint pathInd = 0;
	CityPath trivialPath(this, start);
	paths.push_back(trivialPath);
	while (paths.back().length() != level)
	{
		addNextBFSLevel(paths, pathInd);
	}
}

CityPath CityGraph::shortestPath(string start, string end) const
{
	uint startInd = getCrossrInd(start);
	uint endInd = getCrossrInd(end);
	uint maxLevel = transitions.size() - 1;
	vector<CityPath> bfsPaths;
	CityPath minPath(this);
	
	BFStoLevel(startInd, maxLevel, bfsPaths);
	uint size = bfsPaths.size();
	
	for (CityPath path : bfsPaths)
	{
		if (path.back() == end)
		{
			if (minPath.empty())
				minPath = path;
			else if(path.getDist() < minPath.getDist())
				minPath = path;
		}
	}
	return minPath;
}

bool nullRow(vector<uint> v)
{
	int size = v.size();
	for (int i = 0; i < size; i++)
		if (v[i] != 0)
			return false;
	return true;
}

int CityGraph::getCrossrInd(string crossroad) const
{
	return contains(crossroads, crossroad);
}