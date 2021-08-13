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
	int AngleChecking(list<Unit>::iterator cur_unit, list<Unit>::iterator unit);

public:
	Cartographer();
	~Cartographer() {};
};

