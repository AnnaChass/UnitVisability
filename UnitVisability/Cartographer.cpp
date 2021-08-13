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

// б "checking if cur_unit looks the other way" опнохяюрэ нрдекэмсч опнбепйс мскъ
// опнбепйю мю пюяярнъмхе нр CUR_UNIT дн UNIT 
// опнбепйю мю 360 цпюдсянб нагнпю
int Cartographer::Count()
{
	squared_distance = distance * distance;
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

			if (!AngleChecking(cur_unit, unit))
			{
				// unit is unvisible for cur_unit
				cout << "(" << cur_unit->x << "," << cur_unit->y << ") does not see (" << unit->x << "," << unit->y << ")" << endl;
				continue;
			}

			// checking distance between unit and cur_unit
			if (!DistanceChecking(cur_unit, unit))
			{
				// unit is unvisible for cur_unit
				cout << "(" << cur_unit->x << "," << cur_unit->y << ") does not see (" << unit->x << "," << unit->y << ")" << endl;
				continue;
			}

			// unit is seen by cur_unit
			cout << "(" << cur_unit->x << "," << cur_unit->y << ") sees (" << unit->x << "," << unit->y << ")" << endl;
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
					if (!AngleChecking(cur_unit, unit))
					{
						// unit is unvisible for cur_unit
						cout << "(" << cur_unit->x << "," << cur_unit->y << ") does not see (" << unit->x << "," << unit->y << ")" << endl;
						continue;
					}

					// checking distance between unit and cur_unit
					if (!DistanceChecking(cur_unit, unit))
					{
						// unit is unvisible for cur_unit
						cout << "(" << cur_unit->x << "," << cur_unit->y << ") does not see (" << unit->x << "," << unit->y << ")" << endl;
						continue;
					}

					// unit is seen by cur_unit
					cout << "(" << cur_unit->x << "," << cur_unit->y << ") sees (" << unit->x << "," << unit->y << ")" << endl;
				}

				if (unit == unitList.begin())
					break;
			}
		}
	}
	
	return 1;
}

int Cartographer::AngleChecking(list<Unit>::iterator cur_unit, list<Unit>::iterator unit)
{
	// checking if unit comes into cur_unit's view
	float tgA = cur_unit->direction_x == 0 ? MAX_TG : (cur_unit->direction_y / cur_unit->direction_x),
		tgB = sector / 2,
	    tgG = (unit->x - cur_unit->y == 0) ? MAX_TG : (unit->y - cur_unit->y) / (unit->x - cur_unit->y),
		tgAminG = (tgA * tgG == -1) ? 0 : (tgA - tgG) / (1 + tgA * tgG);

	if (tgAminG > tgB)
	{
		// unit is unvisible for cur_unit
		return 0;
	}

	// checking if cur_unit looks the other way
	if (!(cur_unit->direction_x * (unit->x - cur_unit->x) > 0 &&
		cur_unit->direction_y * (unit->y - cur_unit->y) > 0))
	{
		// unit is unvisible for cur_unit
		return 0;
	}
	return 1;
}

int Cartographer::DistanceChecking(list<Unit>::iterator cur_unit, list<Unit>::iterator unit)
{
	// checking distance between unit and cur_unit
	if ((cur_unit->x - unit->x) * (cur_unit->x - unit->x) + (cur_unit->y - unit->y) * (cur_unit->y - unit->y) > squared_distance)
		return 0;
	return 1;
}

