#include "CS.h"
#include "utils.h"

using namespace std;

int cs::max_id = 1;

ostream& operator << (ostream& out, const cs& new_cs)
{
	out << "ID: " << new_cs.id << endl
		<< "��������: " << new_cs.name << endl
		<< "����� �����: " << new_cs.rooms << endl
		<< "���� � ������: " << new_cs.active_rooms << endl
		<< "�������������: " << new_cs.efficiency << "\n\n";
	return out;
}

std::istream& operator << (std::istream& in, cs& new_cs)
{
	cout << "������� ��������: ";
	getline(in >> ws, new_cs.name);
	cout << "������� ���������� �����: ";
	new_cs.rooms = GetCorrectNumber<int>(1, 10000);
	cout << "������� ���������� ���������� �����: ";
	new_cs.active_rooms = GetCorrectNumber<int>(0, new_cs.rooms);
	cout << "������� �������� ������������� (�� 1 �� 5): ";
	new_cs.efficiency = GetCorrectNumber<int>(1, 5);
	return in;
}

cs::cs()
{
	id = max_id++;
}

int cs::GetMaxId()
{
	return max_id;
}

void cs::SetMaxId(int new_max_id)
{
	max_id = new_max_id;
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
