#include "CS.h"

using namespace std;

int cs::max_id = 1;

ostream& operator << (ostream& out, const cs& new_cs)
{
	out << "��������: " << new_cs.name << endl
		<< "����� �����: " << new_cs.rooms << endl
		<< "���� � ������: " << new_cs.active_rooms << endl
		<< "�������������: " << new_cs.efficiency << "\n\n";
	return out;
}

cs::cs()
{
	id = max_id++;
}

//int cs::GetId()
//{
//	return id;
//}

//void cs::SetId(int index)
//{
//	id = index;
//}
//cs::~cs()
//{
//	cout << "cs::~cs()";
//	max_id = 1;
//}
