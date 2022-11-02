#pragma once
#include <string>
#include <iostream>

class cs
{
public:
	int id = 0;
	static int max_id;
	int rooms = 0;
	std::string name;
	int active_rooms = 0;
	int efficiency = 0;

	cs();
	//int GetId();
	//void SetId(int index);
	//~cs();
	friend std::ostream& operator << (std::ostream& out, const cs& new_cs);
};

