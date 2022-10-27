#pragma once
#include <string>
#include <iostream>

class cs
{
public:
	static int max_id;
	int id = 0;
	int rooms = 0;
	std::string name;
	int active_rooms = 0;
	int efficiency = 0;

	cs();
	friend std::ostream& operator << (std::ostream& out, const cs& new_cs);
};

