#pragma once
#include "city.h"

class Capital : public City
{
public:
	static Capital& getInstance();
	bool addInstitution(string);
	bool removeInstitution(string);

protected:
	virtual void print(std::ostream&) const;

private:
	vector<string> institutions;

	Capital() {}
	Capital(const Capital&);
	void operator=(const Capital&);
};
