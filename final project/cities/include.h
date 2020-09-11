#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <queue>
#include <assert.h>
#define uint unsigned int

using std::string;
using std::vector;
using std::pair;

template <typename T>
int contains(const vector<T>& v, const T& el)	//returns index or -1 if not found
{
	int size = v.size();
	for (int i = 0; i < size; i++)
		if (v[i] == el)
			return i;
	return -1;
}