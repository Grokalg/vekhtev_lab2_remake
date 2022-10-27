#pragma once
#include <iostream>

class tube
{
public:
	int id = 0;
	static int max_id;
	double length = 0;
	double diameter = 0;
	int condition = 0;

	tube();
	friend std::ostream& operator << (std::ostream& out, const tube& new_tube);
};

