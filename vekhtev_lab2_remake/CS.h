#pragma once
#include <string>
#include <iostream>

class cs
{
	static int max_id;
public:
	int id = 0;
	int rooms = 0;
	std::string name;
	int active_rooms = 0;
	int efficiency = 0;

	cs();
	//int GetId();
	//void SetId(int index);
	//~cs();
	friend std::ostream& operator << (std::ostream& out, const cs& new_cs);
	friend std::istream& operator >> (std::istream& in, cs& new_cs);
	static int GetMaxId();
	void SetMaxId(int new_max_id);
};

