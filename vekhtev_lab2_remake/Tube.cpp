#include "Tube.h"

using namespace std;

int tube::max_id = 1;

std::ostream& operator << (std::ostream& out, const tube& new_tube)
{
	out << "ID: " << new_tube.id << endl
		<< "��������: " << new_tube.name << endl
		<< "����� �����: " << new_tube.length << endl
		<< "������� �����: " << new_tube.diameter << endl
		<< "���������: " << new_tube.condition << "\n\n";
	return out;
}

std::istream& operator >> (std::istream& in, tube& new_tube)
{
	cout << "������� ��������: ";
	getline(in >> ws, new_tube.name);
	cout << "������� ����� � ������ (����������� <.>): ";
	new_tube.length = GetCorrectNumber<double>(1, 100000);
	cout << "������� ������� � ������ (����������� <.>): ";
	new_tube.diameter = GetCorrectNumber<double>(1, 100000);;
	cout << "����� ��������\n\n";
	new_tube.condition = 1;
	return in;
}

tube::tube()
{
	id = max_id++;
}

int tube::GetId()
{
	return id;
}

void tube::SetId(int new_id)
{
	id = new_id;
}

int tube::GetMaxId()
{
	return max_id;
}

void tube::SetMaxId(int new_max_id)
{
	max_id = new_max_id;
}


