#pragma once
#include <iostream>
#include <list>
#include <fstream>
#include <cmath>

#define PI 3.14159265358979323846
#define MAX_TG 1000

const char FILENAME[] = "data.txt";
struct Unit
{
	float x;
	float y;
	float direction_x;
	float direction_y;
};
