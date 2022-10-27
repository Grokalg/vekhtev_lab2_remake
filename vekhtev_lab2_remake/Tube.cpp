#include "Tube.h"

using namespace std;

int tube::max_id = 1;

std::ostream& operator << (std::ostream& out, const tube& new_tube)
{
	out << "����� �����: " << new_tube.length << endl
		<< "������� �����: " << new_tube.diameter << endl
		<< "���������: " << new_tube.condition << "\n\n";
	return out;
}

tube::tube()
{
	id = max_id++;
}


