#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>    // std::find
#include "Tube.h"
#include "CS.h"

using namespace std;

template <typename T>
void OutputArray(T mas)
{
	for (auto& element : mas)
	{
		cout << element.first << endl << element.second << endl;
	}
}

//template <typename T>
//int FindMaxId(T mas)
//{
//	int current_id;
//	int max_id = 1;
//	for (auto& element : mas)
//	{
//		current_id = element.first;
//		if (current_id > max_id)
//		{
//			max_id = current_id;
//		}
//	}
//	return max_id;
//}

//double UserInputParameter()
//{
//	double parameter;
//	cin >> parameter;
//	while (cin.fail() || cin.peek() != '\n' || parameter <= 0)
//	{
//		cout << "��������� ������ �� ���������\n";
//		cin.clear();
//		cin.ignore(1000, '\n');
//		cin >> parameter;
//	}
//	return parameter;
//}

//int UserInputIndex()
//{
//	int id;
//	cout << "������� ����� �����, ������� ������ �������: ";
//	cin >> id;
//	while (cin.fail() || cin.peek() != '\n' || id < 0)
//	{
//		cout << "��������� ������ �� ���������\n";
//		cin.clear();
//		cin.ignore(1000, '\n');
//		cin >> id;
//	}
//	return id;
//}

//int InputRooms()
//{
//	int rooms;
//	cin >> rooms;
//	while (cin.fail() || cin.peek() != '\n' || rooms <= 0)
//	{
//		cout << "��������� ������ �� ���������\n";
//		cin.clear();
//		cin.ignore(1000, '\n');
//		cin >> rooms;
//	}
//	return rooms;
//}

//string InputName()
//{
//	string name;
//	cin >> name;
//	while (cin.fail() || cin.peek() != '\n')
//	{
//		cout << "��������� ������ �� ���������\n";
//		cin.clear();
//		cin.ignore(1000, '\n');
//		cin >> name;
//	}
//	return name;
//}

//int InputActiveRooms(cs& new_cs)
//{
//	int active_rooms;
//	cin >> active_rooms;
//	while (cin.fail() || cin.peek() != '\n' || active_rooms > new_cs.rooms || active_rooms < 0)
//	{
//		cout << "��������� ������ �� ���������\n";
//		cin.clear();
//		cin.ignore(1000, '\n');
//		cin >> active_rooms;
//	}
//	return active_rooms;
//}

//int InputEfficiency()
//{
//	int efficiency;
//	cin >> efficiency;
//	while (cin.fail() || cin.peek() != '\n' || efficiency <= 0 || efficiency > 5)
//	{
//		cout << "��������� ������ �� ���������\n";
//		cin.clear();
//		cin.ignore(1000, '\n');
//		cin >> efficiency;
//	}
//	return efficiency;
//}

//int CorrectChoice()
//{
//	int user_choice;
//	do
//	{
//		cin.clear();
//		cin.ignore(1000, '\n');
//		cin >> user_choice;
//	} while (cin.fail() || user_choice < 0 || user_choice > 1);
//	return user_choice;
//}

bool IsCorrectMenuChoice(int user_choice)
{
	if (cin.fail() || cin.peek() != '\n' || user_choice < 0 || user_choice > 12)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "������ �� ���������" << endl;
		return false;
	}
	return true;
}

bool IsPosibleTransformationAdd(cs& new_cs)
{
	if (new_cs.active_rooms > new_cs.rooms)
	{
		cout << "���������� ���������� ����� �� ����� ��������� ����������� ����� ����� �� ��.\n";
		return false;
	}
	if (new_cs.active_rooms < 0)
	{
		cout << "���������� ���������� ����� �� ����� ���� �������������.\n";
		return false;
	}
}

bool IsPosibleTransformationSub(cs& new_cs)
{
	if (new_cs.active_rooms > new_cs.rooms)
	{
		cout << "���������� ���������� ����� �� ����� ��������� ����������� ����� ����� �� ��.\n";
		return false;
	}
	if (new_cs.active_rooms <= 0)
	{
		cout << "���������� ���������� ����� �� ����� ���� �������������.\n";
		return false;
	}
}

//double ReadValue(ifstream& in)
//{
//	double parameter = 0;
//	if (in.fail() || in.peek() != '\n')
//	{
//		in >> parameter;
//	}
//	return parameter;
//}

//string ReadName(ifstream& in)
//{
//	string name;
//	if (in.fail() || in.peek() != '\n')
//	{
//		in >> name;
//	}
//	return name;
//}

template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((cin >> x).fail() || x > max || x < min)
	{
		cout << "��������� ������ �� ���������\n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return x;
}

tube& SelectTube(unordered_map <int, tube>& tubes)
{
	cout << "������� ����� �����:" << endl;
	int id = GetCorrectNumber<int>(1, tubes.size());
	return tubes[id];
}

cs& SelectCS(unordered_map <int, cs>& stations)
{
	cout << "������� ����� �����:" << endl;
	int id = GetCorrectNumber<int>(1, stations.size());
	return stations[id];
}

template <typename T>
using Filter1 = bool(*)(cs new_cs, T param);

template <typename T>
bool CheckByName(T object, string param)
{
	return object.name == param;
}

bool CheckByRooms(cs new_cs, double percent)
{
	return (1 - new_cs.active_rooms/new_cs.rooms)*100 >= percent;
}

template <typename T>
vector<int> FindCsByFilter(unordered_map <int, cs> stations, Filter1<T> f, T param)
{
	vector <int> result;
	for (auto& element : stations)
	{
		if (f(element.second, param))
		{
			result.push_back(element.first);
		}
	}
	return result;
}

template <typename T>
using Filter2 = bool(*)(tube new_tube, T param);

bool CheckByStatus(tube new_tube, int status)
{
	return new_tube.condition == status;
}

template <typename T>
vector<int> FindTubesByFilter(unordered_map <int, tube> tubes, Filter2<T> f, T param)
{
	vector <int> result;
	for (auto& element : tubes)
	{
		if (f(element.second, param))
		{
			result.push_back(element.first);
		}
	}
	return result;
}

template <typename T>
void OutputObjects(vector<int> v, unordered_map <int, T> mas)
{
	for (int element : v)
	{
		cout << mas[element] << endl;
	}
}

tube Change(tube t, int status)
{
	t.condition = status;
	return t;
}

void CreateTube(unordered_map <int, tube>& tubes)
{
	tube new_tube;
	cout << "������� ��������: ";
	getline(cin >> ws, new_tube.name);
	cout << "������� ����� � ������ (����������� <.>): ";
	/*new_tube.length = UserInputParameter();*/
	new_tube.length = GetCorrectNumber<double>(1, 100000);
	cout << "������� ������� � ������ (����������� <.>): ";
	new_tube.diameter = GetCorrectNumber<double>(1, 100000);;
	cout << "����� ��������\n\n";
	new_tube.condition = 1;
	tubes.emplace(new_tube.id, new_tube);
}

void CreateStation(unordered_map <int, cs>& stations)
{
	cs new_cs;
	cout << "������� ��������: ";
	getline(cin >> ws, new_cs.name);
	cout << "������� ���������� �����: ";
	/*new_cs.rooms = InputRooms();*/
	new_cs.rooms = GetCorrectNumber<int>(1, 10000);
	cout << "������� ���������� ���������� �����: ";
	//new_cs.active_rooms = InputActiveRooms(new_cs);
	new_cs.active_rooms = GetCorrectNumber<int>(0, new_cs.rooms);
	cout << "������� �������� ������������� (�� 1 �� 5): ";
	/*new_cs.efficiency = InputEfficiency();*/
	new_cs.efficiency = GetCorrectNumber<int>(1, 5);
	stations.emplace(new_cs.id, new_cs);
}

void ViewAllObjects(unordered_map <int, tube> tubes, unordered_map <int, cs> stations)
{
	if (tubes.empty())
	{
		cout << "����� ��� �� �������\n";
	}
	else
	{
		cout << "------------------�����------------------" << endl;
		OutputArray(tubes);
	}
	if (stations.empty())
	{
		cout << "�� ��� �� �������\n";
	}
	else
	{
		cout << "--------------------��-------------------" << endl;
		OutputArray(stations);
	}
}

void EditTube(tube& new_tube)
{
	if (new_tube.length == 0)
	{
		cout << "����� ��� �� �������\n";
	}
	else
	{
		cout << "------------ �������������� ����� ------------\n";
		cout << "������� �������� ���������:\n";
		cout << "<1> - ����� ��������  <0> - ����� � �������\n";
		switch (GetCorrectNumber<int>(0,1))
		{
		case 1:
			new_tube.condition = 1;
			break;
		case 0:
			new_tube.condition = 0;
			break;
		default:
			cout << "��������� ������ �� ���������.\n";
			break;
		}
	}
}

void EditTubes(unordered_map <int, tube>& tubes)
{
	int id;
	int status = 0;
	vector<int> id_of_tubes;
	cout << "------------ �������������� ���� ------------\n";
	while (true)
	{
		cout << "������� ����� �����, ������� �� ������ �������� � ��������������: " << endl
			<< "��� ����������� �����, ������� 0" << endl;
		cin >> id;
		if (id == 0)
		{
			break;
		}
		if (tubes.find(id) != tubes.end() and find(id_of_tubes.begin(), id_of_tubes.end(), id) == id_of_tubes.end())
		{
			id_of_tubes.push_back(id);
			continue;
		}
	}
	cout << "������� �������� ���������, ������� ����� ��������� ��� ��������� ����:\n";
	cout << "<1> - ����� ��������  <0> - ����� � �������\n";
	switch (GetCorrectNumber<int>(0, 1))
	{
	case 1:
		status = 1;
		break;
	case 0:
		status = 0;
		break;
	default:
		cout << "��������� ������ �� ���������.\n";
		break;
	}
	for (int i : id_of_tubes)
	{
		tubes[i] = Change(tubes[i], status);
	}
}

void EditStation(cs& new_cs)
{
	if (new_cs.rooms == 0)
	{
		cout << "�� ��� �� �������\n";
	}
	else
	{
		cout << "------------ �������������� �� ------------\n";
		cout << "���������� ���������� ����� �� ������ ������: " << new_cs.active_rooms << endl;
		cout << "<0> - ������ �������� ���, <1> - �������� �������� ���\n";
		switch (GetCorrectNumber<int>(0, 1))
		{
		case 1:
			if (IsPosibleTransformationAdd(new_cs))
			{
				new_cs.active_rooms++;
				cout << "���-�� ���������� �����: " << new_cs.active_rooms << endl;
			}
			break;
		case 0:
			if (IsPosibleTransformationSub(new_cs))
			{
				new_cs.active_rooms--;
				cout << "���-�� ���������� �����: " << new_cs.active_rooms << endl;
			}
			break;
		default:
			break;
		}
	}
}

void Save(unordered_map <int, tube>& tubes, unordered_map <int, cs>& stations)
{
	tube new_tube; 
	cs new_cs;
	ofstream out("Data.txt");
	new_tube.max_id = new_tube.max_id - 1;
	new_cs.max_id = new_cs.max_id - 1;
	if (out.is_open())
	{
		out << tubes.size() << endl;
		out << new_tube.max_id << endl;
		out << stations.size() << endl;
		out << new_cs.max_id << endl;
		if (tubes.empty())
		{
			cout << "����� ��� �� �������\n";
		}
		else
		{
			for (auto& element : tubes)
			{
				out << element.second.id << endl;
				out << element.second.name << endl;
				out << element.second.length << endl;
				out << element.second.diameter << endl;
				out << element.second.condition << endl;
			}
			cout << "������ �� ������ ���������\n\n";
		}
		if (stations.empty())
		{
			cout << "�� ��� �� �������\n";
		}
		else
		{
			for (auto& element : stations)
			{
				out << element.second.id << endl;
				out << element.second.name << endl;
				out << element.second.rooms << endl;
				out << element.second.active_rooms << endl;
				out << element.second.efficiency << endl;
			}
			cout << "������ �� �� ���������\n\n";
		}
	}
	out.close();
}

void Download(unordered_map <int, tube>& tubes, unordered_map <int, cs>& stations)
{
	int number_of_tubes, number_of_cs, cs_max_id, tube_max_id;
	ifstream in("Data.txt");
	if (in.is_open())
	{
		in >> number_of_tubes;
		in >> tube_max_id;
		in >> number_of_cs;
		in >> cs_max_id;
		while (number_of_tubes--)
		{
			tube new_tube;
			new_tube.max_id = tube_max_id;
			in >> new_tube.id;
			getline(in >> ws, new_tube.name);
			in >> new_tube.length;
			in >> new_tube.diameter;
			in >> new_tube.condition;
			tubes.emplace(new_tube.id, new_tube);
		}
		while (number_of_cs--)
		{
			cs new_cs;
			new_cs.max_id = cs_max_id;
			in >> new_cs.id;
			getline(in >> ws, new_cs.name);
			in >> new_cs.rooms;
			in >> new_cs.active_rooms;
			in >> new_cs.efficiency;
			stations.emplace(new_cs.id, new_cs);
		}
	}
	in.close();
	cout << "������ ���������\n";
}

void ShowMenu()
{
	cout << "1. �������� �����\n";
	cout << "2. �������� ��\n";
	cout << "3. ������� �����\n";
	cout << "4. �������� ���� ��������\n";
	cout << "5. ������������� �����\n";
	cout << "6. ������������� ��\n";
	cout << "7. ����� �� �� ��������\n";
	cout << "8. ����� �� �� �������� ����������������� �����\n";
	cout << "9. ����� ���� �� ��������\n"; 
	cout << "10. ����� ���� �� �������� '� �������'\n";
	cout << "11. ���������\n";
	cout << "12. ���������\n";
	cout << "0. �����\n";
}

int Menu(unordered_map <int, tube>& tubes, unordered_map <int, cs>& stations, vector<int>& indexes_of_stations, vector<int>& indexes_of_tubes)
{
	string name_of_object;
	int user_choice;
	do { cin >> user_choice; } while (IsCorrectMenuChoice(user_choice) == false);
	switch (user_choice)
	{
	case 1:
		CreateTube(tubes);
		return 1;
	case 2:
		CreateStation(stations);
		return 1;
	case 3:
		cout << "������� ����� �����, ������� ������ �������: ";
		/*tubes.erase(UserInputIndex());*/
		tubes.erase(GetCorrectNumber<int>(0, 100000));
		return 1;
	case 4:
		ViewAllObjects(tubes, stations);
		return 1;
	case 5:
		/*EditTube(SelectTube(tubes));*/
		EditTubes(tubes);
		return 1;
	case 6:
		EditStation(SelectCS(stations));
		return 1;
	case 7:
		cout << "������� ��������: ";
		getline(cin >> ws, name_of_object);
		indexes_of_stations = FindCsByFilter(stations, CheckByName, name_of_object);
		OutputObjects(indexes_of_stations, stations);
		return 1;
	case 8:
		double percent;
		cout << "������� �������: ";
		percent = GetCorrectNumber<double>(0, 100);
		indexes_of_stations = FindCsByFilter(stations, CheckByRooms, percent);
		OutputObjects(indexes_of_stations, stations);
		return 1;
	case 9:
		cout << "������� ��������: ";
		getline(cin >> ws, name_of_object);
		indexes_of_tubes = FindTubesByFilter(tubes, CheckByName, name_of_object);
		OutputObjects(indexes_of_tubes, tubes);
		return 1;
	case 10:
		int status;
		cout << "<0> - ������� �����, ������� � �������" << endl
			<< "<1> - ������� ��������� �����" << endl;
		status = GetCorrectNumber<int>(0, 1);
		indexes_of_tubes = FindTubesByFilter(tubes, CheckByStatus, status);
		OutputObjects(indexes_of_tubes, tubes);
		return 1;
	case 11:
		Save(tubes, stations);
		return 1;
	case 12:
		Download(tubes, stations);
		return 1;
	case 0:
		return 0;
	default:
		cout << "��������� ������ �� ���������. ����������, ������� ����� ������������� ��� ������.\n\n";
		return 1;
	}
}

int main()
{
	setlocale(0, "");
	vector<int> indexes_of_stations;
	vector<int> indexes_of_tubes;
	unordered_map <int, tube> tubes;
	unordered_map <int, cs> stations;
	do { ShowMenu(); } while (Menu(tubes, stations, indexes_of_stations, indexes_of_tubes) != 0);
}