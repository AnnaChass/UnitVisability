#pragma once
#include "Header.h"
using namespace std;

class Cartographer
{
private:
	list<struct Unit> unitList;
	float distance;
	int unit_number;
	float sector;

	int ReadFile();
	int Count();
	//bool Sort(list<Unit>::iterator it1, list<Unit>::iterator it2);

public:
	Cartographer();
	~Cartographer() {};
};

