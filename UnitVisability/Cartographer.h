#pragma once
#include "Header.h"
using namespace std;

class Cartographer
{
private:
	list<struct Unit> unitList;
	float distance;
	float squared_distance;
	int unit_number;
	float sector;

	int ReadFile();
	int Count();
	int AngleChecking(list<Unit>::iterator cur_unit, list<Unit>::iterator unit);
	int DistanceChecking(list<Unit>::iterator cur_unit, list<Unit>::iterator unit);

public:
	Cartographer();
	~Cartographer() {};
};

