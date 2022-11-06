#pragma once
#include <string>
#include <iostream>
#include "utils.h"

class tube
{
public:
	int id = 0;
	std::string name;
	static int max_id;
	double length = 0;
	double diameter = 0;
	int condition = 0;

	tube();
	friend std::ostream& operator << (std::ostream& out, const tube& new_tube);
	friend std::istream& operator >> (std::istream& in, tube& new_tube);
};

