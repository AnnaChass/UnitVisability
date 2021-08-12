#include "Cartographer.h"


bool Sort(Unit unit1, Unit unit2)
{
	return (unit1.x < unit2.x);
}

Cartographer::Cartographer()
{
	// reading data.txt
	if (!ReadFile())
	{
		cout << "Incorrect program termination." << endl;
		return;
	}
	// sorting units by x coordinate to increase the efficiency of cutting off obviously unsuitable options
	unitList.sort(Sort);
	// final calculations
	Count();
}

int Cartographer::ReadFile()
{
	ifstream file(FILENAME);

	if (!file)
	{
		cout << "File could not be opened." << endl;
		return 0;
	}

	file >> unit_number >> sector >> distance;
	for (int i = 0; i < unit_number; ++i)
	{
		if (file.eof()) 
		{
			cout << "File is incorrect." << endl;
			return 0;
		}

		Unit temp;
		file >> temp.x >> temp.y >> temp.direction_x >> temp.direction_y;
		unitList.push_back(temp);
	}

	return 1;
}

int Cartographer::Count()
{
	// pairwise comparison of units
	for (list<Unit>::iterator cur_unit = unitList.begin(); cur_unit != unitList.end(); ++cur_unit)
	{
		int x_left = cur_unit->x - distance,
			x_right = cur_unit->x + distance,
			y_low = cur_unit->y - distance,
			y_high = cur_unit->y + distance;

		// cutting off obviously unsuitable options: \
            checking if a (un)visible unit is included in a surrounding square with sides of 2 distance
 
		// checking unit to the right from cur_unit
		list<Unit>::iterator unit = cur_unit;
		for (unit++; unit != unitList.end(); unit++)
		{
			// checking if unit (and all the following units) is too far from cur_unit
			if (unit->x > x_right) 
				break;

			// checking if unit is unsuitable by y coordinate
			if (unit->y < y_low ||
				unit->y > y_high)
			{
				// unit is unvisible for cur_unit
				cout << "(" << cur_unit->x << "," << cur_unit->y << ") does not see (" << unit->x << "," << unit->y << ")" << endl;
				continue;
			}

			// continue checking
			cout << "(" << cur_unit->x << "," << cur_unit->y << ") probably sees (" << unit->x << "," << unit->y << ")" << endl;

		}

		// checking unit to the left from cur_unit
		unit = cur_unit;
		if (unit != unitList.begin())
		{
			for (unit--; ; unit--)
			{
				// checking if unit (and all the previous units) is too far from cur_unit
				if (unit->x < x_left)
					break;

				// checking if unit is unsuitable by y coordinate
				if (unit->y < y_low ||
					unit->y > y_high)
				{
					// unit is unvisible for cur_unit
					cout << "(" << cur_unit->x << "," << cur_unit->y << ") does not see (" << unit->x << "," << unit->y << ")" << endl;
				}
				
				// continue checking
				else
				{					
					cout << "(" << cur_unit->x << "," << cur_unit->y << ") probably sees (" << unit->x << "," << unit->y << ")" << endl;
				}

				if (unit == unitList.begin())
					break;
			}
		}
	}
	
	
	
	return 1;
}

