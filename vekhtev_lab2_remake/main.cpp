#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>    // std::find
#include "Tube.h"
#include "CS.h"
#include "utils.h"

using namespace std;

template <typename T>
void OutputArray(T mas)
{
	for (auto& element : mas)
	{
		cout << element.second << endl;
	}
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
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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

void SetStatus(unordered_map <int, tube>& tubes, vector<int> v)
{
	int status = 0;
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
	}
	for (int i : v)
	{
		tubes[i] = Change(tubes[i], status);
	}
}

cs AddRoom(cs c)
{
	c.active_rooms++;
	return c;
}

cs SubRoom(cs c)
{
	c.active_rooms--;
	return c;
}

void ChangeCsParameter(vector<int> v, unordered_map <int, cs>& stations)
{
	int error_flag = 1;
	cout << "�������� �������, ������� ���������� ���������: " << endl;
	cout << "<0> - ������ �������� ���, <1> - �������� �������� ���\n";
	if (GetCorrectNumber<int>(0, 1) == 0)
	{
		for (int i : v)
		{
			if (IsPosibleTransformationSub(stations[i]))
			{
				error_flag = 1;
			}
			else
			{
				error_flag = 0;
			}
		}
		if (error_flag == 1)
		{
			for (int i : v)
			{
				stations[i] = SubRoom(stations[i]);
			}
		}
		else
		{
			cout << "�������� �� ����� ���� ���������" << endl;
		}
	}
	else
	{
		for (int i : v)
		{
			if (IsPosibleTransformationAdd(stations[i]))
			{
				error_flag = 1;
			}
			else
			{
				error_flag = 0;
			}
		}
		if (error_flag == 1)
		{
			for (int i : v)
			{
				stations[i] = AddRoom(stations[i]);
			}
		}
		else
		{
			cout << "�������� �� ����� ���� ���������" << endl;
		}
	}
}

void CreateTube(unordered_map <int, tube>& tubes)
{
	tube new_tube;
	cin >> new_tube;
	tubes.emplace(new_tube.GetId(), new_tube);
}

void CreateStation(unordered_map <int, cs>& stations)
{
	cs new_cs;
	cin << new_cs;
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

void EditTubes(unordered_map <int, tube>& tubes, vector<int> id_of_tubes)
{
	if (tubes.empty())
	{
		cout << "����� ��� �� �������\n";
	}
	else
	{
		cout << "------------ �������������� ���� ------------\n";
		cout << "�������� 1, ���� ������ ������������� ����� �� �������" << endl
			<< "          2, ���� ������ ������������� ����� ����� ���� ���������" << endl;
		if (GetCorrectNumber(1, 2) == 1)
		{
			SetStatus(tubes, id_of_tubes);
		}
		else
		{
			int id;
			vector<int> indexes_of_tubes;
			while (true)
			{
				cout << "������� ����� �����, ������� �� ������ �������� � ��������������: " << endl
					<< "��� ����������� �����, ������� 0" << endl;
				cin >> id;
				if (id == 0)
				{
					break;
				}
				if (tubes.find(id) != tubes.end() and find(indexes_of_tubes.begin(), indexes_of_tubes.end(), id) == indexes_of_tubes.end())
				{
					indexes_of_tubes.push_back(id);
					continue;
				}
			}
			SetStatus(tubes, indexes_of_tubes);
		}
	}
}

void EditStations(unordered_map <int, cs>& stations, vector<int> id_of_stations)
{
	if (stations.empty())
	{
		cout << "�� ��� �� �������\n";
	}
	else
	{
		cout << "------------ �������������� �� ------------\n";
		cout << "�������� 1, ���� ������ ������������� �� �� �������" << endl
			<< "          2, ���� ������ ������������� �� ����� ���� ���������" << endl;
		if (GetCorrectNumber(1, 2) == 1)
		{
			ChangeCsParameter(id_of_stations, stations);
		}
		else
		{
			int id;
			vector<int> indexes_of_stations;
			while (true)
			{
				cout << "������� ����� ��, ������� �� ������ �������� � ��������������: " << endl
					<< "��� ����������� �����, ������� 0" << endl;
				cin >> id;
				if (id == 0)
				{
					break;
				}
				if (stations.find(id) != stations.end() and find(indexes_of_stations.begin(), indexes_of_stations.end(), id) == indexes_of_stations.end())
				{
					indexes_of_stations.push_back(id);
					continue;
				}
			}
			ChangeCsParameter(indexes_of_stations, stations);
		}
	}
}

void FindTubesByName(unordered_map <int, tube>& tubes, vector<int>& id_of_tubes)
{
	string name_of_object;
	if (tubes.empty())
	{
		cout << "����� ��� �� �������\n";
	}
	else
	{
		cout << "������� ��������: ";
		getline(cin >> ws, name_of_object);
		id_of_tubes = FindTubesByFilter(tubes, CheckByName, name_of_object);
		OutputObjects(id_of_tubes, tubes);
	}
}

void FindTubesByStatus(unordered_map <int, tube>& tubes, vector<int>& id_of_tubes)
{
	if (tubes.empty())
	{
		cout << "����� ��� �� �������\n";
	}
	else
	{
		cout << "<0> - ������� �����, ������� � �������" << endl
			<< "<1> - ������� ��������� �����" << endl;
		id_of_tubes = FindTubesByFilter(tubes, CheckByStatus, GetCorrectNumber<int>(0, 1));
		OutputObjects(id_of_tubes, tubes);
	}
}

void FindCsByName(unordered_map <int, cs>& stations, vector<int>& id_of_stations)
{
	string name_of_object;
	if (stations.empty())
	{
		cout << "�� ��� �� �������\n";
	}
	else
	{
		cout << "������� ��������: ";
		getline(cin >> ws, name_of_object);
		id_of_stations = FindCsByFilter(stations, CheckByName, name_of_object);
		OutputObjects(id_of_stations, stations);
	}
}

void FindCsByRooms(unordered_map <int, cs>& stations, vector<int>& id_of_stations)
{
	if (stations.empty())
	{
		cout << "�� ��� �� �������\n";
	}
	else
	{
		cout << "������� �������: ";
		id_of_stations = FindCsByFilter(stations, CheckByRooms, GetCorrectNumber<double>(0, 100));
		OutputObjects(id_of_stations, stations);
	}
}

void Save(unordered_map <int, tube>& tubes, unordered_map <int, cs>& stations)
{
	tube new_tube; 
	cs new_cs;
	string name_of_file;
	cout << "������� �������� �����, � ������� ����� ��������� ������: ";
	getline(cin >> ws, name_of_file);
	ofstream out(name_of_file + ".txt");
	new_tube.SetMaxId(new_tube.GetMaxId() - 1);
	new_cs.max_id = new_cs.max_id - 1;
	if (out.is_open())
	{
		out << tubes.size() << endl;
		out << new_tube.GetMaxId() << endl;
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
				out << element.second.GetId() << endl;
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
	string name_of_file;
	cout << "������� �������� �����, �� �������� ����� ������� ������: ";
	getline(cin >> ws, name_of_file);
	ifstream in(name_of_file + ".txt");
	if (in.is_open())
	{
		in >> number_of_tubes;
		in >> tube_max_id;
		in >> number_of_cs;
		in >> cs_max_id;
		while (number_of_tubes--)
		{
			tube new_tube;
			int id;
			new_tube.SetMaxId(tube_max_id);
			in >> id;
			new_tube.SetId(id);
			getline(in >> ws, new_tube.name);
			in >> new_tube.length;
			in >> new_tube.diameter;
			in >> new_tube.condition;
			tubes.emplace(new_tube.GetId(), new_tube);
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
		cout << "������ ���������\n";
	}
	in.close();
}

void ShowMenu()
{
	cout << "1. �������� �����\n";
	cout << "2. �������� ��\n";
	cout << "3. ������� �����\n";
	cout << "4. ������� ��\n";
	cout << "5. �������� ���� ��������\n";
	cout << "6. �������������� ����\n";
	cout << "7. �������������� ��\n";
	cout << "8. ����� �� �� ��������\n";
	cout << "9. ����� �� �� �������� ����������������� �����\n";
	cout << "10. ����� ���� �� ��������\n"; 
	cout << "11. ����� ���� �� �������� '� �������'\n";
	cout << "12. ���������\n";
	cout << "13. ���������\n";
	cout << "0. �����\n";
}

//int Run(unordered_map <int, tube>& tubes, unordered_map <int, cs>& stations, vector<int>& id_of_stations, vector<int>& id_of_tubes)
//{
//	string name_of_object;
//	int user_choice = GetCorrectNumber<int>(0, 12);
//	switch (user_choice)
//	{
//	case 1:
//		CreateTube(tubes);
//		return 1;
//	case 2:
//		CreateStation(stations);
//		return 1;
//	case 3:
//		cout << "������� ����� �����, ������� ������ �������: ";
//		tubes.erase(GetCorrectNumber<int>(0, 100000));
//		return 1;
//	case 4:
//		ViewAllObjects(tubes, stations);
//		return 1;
//	case 5:
//		EditTubes(tubes, id_of_tubes);
//		return 1;
//	case 6:
//		EditStations(stations, id_of_stations);
//		/*EditStation(SelectCS(stations));*/
//		return 1;
//	case 7:
//		cout << "������� ��������: ";
//		getline(cin >> ws, name_of_object);
//		id_of_stations = FindCsByFilter(stations, CheckByName, name_of_object);
//		OutputObjects(id_of_stations, stations);
//		return 1;
//	case 8:
//		cout << "������� �������: ";
//		id_of_stations = FindCsByFilter(stations, CheckByRooms, GetCorrectNumber<double>(0, 100));
//		OutputObjects(id_of_stations, stations);
//		return 1;
//	case 9:
//		cout << "������� ��������: ";
//		getline(cin >> ws, name_of_object);
//		id_of_tubes = FindTubesByFilter(tubes, CheckByName, name_of_object);
//		OutputObjects(id_of_tubes, tubes);
//		return 1;
//	case 10:
//		cout << "<0> - ������� �����, ������� � �������" << endl
//			<< "<1> - ������� ��������� �����" << endl;
//		id_of_tubes = FindTubesByFilter(tubes, CheckByStatus, GetCorrectNumber<int>(0, 1));
//		OutputObjects(id_of_tubes, tubes);
//		return 1;
//	case 11:
//		Save(tubes, stations);
//		return 1;
//	case 12:
//		Download(tubes, stations);
//		return 1;
//	case 0:
//		return 0;
//	default:
//		cout << "��������� ������ �� ���������. ����������, ������� ����� ������������� ��� ������.\n\n";
//		return 1;
//	}
//}

void Run()
{
	vector<int> id_of_stations;
	vector<int> id_of_tubes;
	unordered_map <int, tube> tubes;
	unordered_map <int, cs> stations;
	while (true)
	{
		ShowMenu();
		switch (GetCorrectNumber<int>(0, 13))
		{
		case 1:
			CreateTube(tubes);
			break;
		case 2:
			CreateStation(stations);
			break;
		case 3:
			cout << "������� ����� �����, ������� ������ �������: ";
			tubes.erase(GetCorrectNumber<int>(0, 100000));
			break;
		case 4:
			cout << "������� ����� ��, ������� ������ �������: ";
			stations.erase(GetCorrectNumber<int>(0, 100000));
			break;
		case 5:
			ViewAllObjects(tubes, stations);
			break;
		case 6:
			EditTubes(tubes, id_of_tubes);
			break;
		case 7:
			EditStations(stations, id_of_stations);
			break;
		case 8:
			FindCsByName(stations, id_of_stations);
			break;
		case 9:
			FindCsByRooms(stations, id_of_stations);
			break;
		case 10:
			FindTubesByName(tubes, id_of_tubes);
			break;
		case 11:
			FindTubesByStatus(tubes, id_of_tubes);
			break;
		case 12:
			Save(tubes, stations);
			break;
		case 13:
			Download(tubes, stations);
			break;
		case 0:
			exit(0);
		default:
			cout << "��������� ������ �� ���������. ����������, ������� ����� ������������� ��� ������.\n\n";
			break;
		}
	}
}

int main()
{
	setlocale(0, "");
	Run();
	//vector<int> id_of_stations;
	//vector<int> id_of_tubes;
	//unordered_map <int, tube> tubes;
	//unordered_map <int, cs> stations;
	//do 
	//{ 
	//	ShowMenu(); 
	//} 
	//while (Run(tubes, stations, id_of_stations, id_of_tubes));
}