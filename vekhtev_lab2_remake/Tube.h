#pragma once
#include <string>
#include <iostream>
#include "utils.h"

class tube
{
	int id = 0;
	static int max_id;
public:
	std::string name;
	double length = 0;
	double diameter = 0;
	int condition = 0;

	tube();
	friend std::ostream& operator << (std::ostream& out, const tube& new_tube);
	friend std::istream& operator >> (std::istream& in, tube& new_tube);

	int GetId();
	void SetId(int new_id);
	int GetMaxId();
	void SetMaxId(int new_id);
};

