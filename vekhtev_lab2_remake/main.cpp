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
		cout << "Количество работающих цехов не может превышать колличество всего цехов на КС.\n";
		return false;
	}
	if (new_cs.active_rooms < 0)
	{
		cout << "Количество работающих цехов не может быть отрицательным.\n";
		return false;
	}
}

bool IsPosibleTransformationSub(cs& new_cs)
{
	if (new_cs.active_rooms > new_cs.rooms)
	{
		cout << "Количество работающих цехов не может превышать колличество всего цехов на КС.\n";
		return false;
	}
	if (new_cs.active_rooms <= 0)
	{
		cout << "Количество работающих цехов не может быть отрицательным.\n";
		return false;
	}
}

tube& SelectTube(unordered_map <int, tube>& tubes)
{
	cout << "Введите номер трубы:" << endl;
	int id = GetCorrectNumber<int>(1, tubes.size());
	return tubes[id];
}

cs& SelectCS(unordered_map <int, cs>& stations)
{
	cout << "Введите номер трубы:" << endl;
	int id = GetCorrectNumber<int>(1, stations.size());
	return stations[id];
}

template <typename T>
using Filter1 = bool(*)(cs new_cs, T param);

template <typename T>
bool CheckByName(T object, string param)
{
	return object.name.find(param) != std::string::npos;
}

bool CheckByRooms(cs new_cs, double percent)
{
	return (1 - static_cast<double>(new_cs.active_rooms) / new_cs.rooms) * 100 >= percent;
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
	cout << "Введите значение состояния, которое будет применено для выбранных труб:\n";
	cout << "<1> - Труба исправна  <0> - Труба в ремонте\n";
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
	cout << "Выберите оперцию, которую необходимо выполнить: " << endl;
	cout << "<0> - Убрать активный цех, <1> - Добавить активный цех\n";
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
			cout << "Операция не может быть выполнена" << endl;
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
			cout << "Операция не может быть выполнена" << endl;
		}
	}
}

template <typename T>
void CleanMas(T& mas, vector<int> v)
{
	for (int i : v)
	{
		mas.erase(i);
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
		cout << "Трубы еще не созданы\n";
	}
	else
	{
		cout << "------------------Трубы------------------" << endl;
		OutputArray(tubes);
	}
	if (stations.empty())
	{
		cout << "КС еще не созданы\n";
	}
	else
	{
		cout << "--------------------КС-------------------" << endl;
		OutputArray(stations);
	}
}

vector<int> FindTubesByName(unordered_map <int, tube>& tubes)
{
	vector<int> id_of_tubes;
	string name_of_object;
	cout << "Введите название: ";
	getline(cin >> ws, name_of_object);
	id_of_tubes = FindTubesByFilter(tubes, CheckByName, name_of_object);
	OutputObjects(id_of_tubes, tubes);
	return id_of_tubes;
}

vector<int> FindTubesByStatus(unordered_map <int, tube>& tubes)
{
	vector<int> id_of_tubes;
	cout << "<0> - вывести трубы, которые в ремонте" << endl
		<< "<1> - вывести исправные трубы" << endl;
	id_of_tubes = FindTubesByFilter(tubes, CheckByStatus, GetCorrectNumber<int>(0, 1));
	OutputObjects(id_of_tubes, tubes);
	return id_of_tubes;
}

vector<int> FindCsByName(unordered_map <int, cs>& stations)
{
	vector<int> id_of_stations;
	string name_of_object;
	cout << "Введите название: ";
	getline(cin >> ws, name_of_object);
	id_of_stations = FindCsByFilter(stations, CheckByName, name_of_object);
	OutputObjects(id_of_stations, stations);
	return id_of_stations;
}

vector<int> FindCsByRooms(unordered_map <int, cs>& stations)
{
	vector<int> id_of_stations;
	cout << "Этот фильтр найдет станции, у которых процент незадействованных цехов превышает значение, которое введете вы" << endl;
	cout << "Введите процент: "; //процент незадействованных цехов будет привышать этот процент
	id_of_stations = FindCsByFilter(stations, CheckByRooms, GetCorrectNumber<double>(0, 100));
	OutputObjects(id_of_stations, stations);
	return id_of_stations;
}

void EditTubes(unordered_map <int, tube>& tubes)
{
	if (tubes.empty())
	{
		cout << "Трубы еще не созданы\n";
	}
	else
	{
		vector<int> id_of_tubes;
		cout << "------------ Редактирование Труб ------------\n";
		cout << "Выберите 1, если хотите редактировать трубы, найденные по названию" << endl
			<< "          2, если хотите редактировать трубы, найденные по признаку 'в ремонте'" << endl
			<< "          3, если хотите редактировать трубы среди всех созданных" << endl;
		switch (GetCorrectNumber(1, 3))
		{
		case 1:
			id_of_tubes = FindTubesByName(tubes);
			break;
		case 2:
			id_of_tubes = FindTubesByStatus(tubes);
			break;
		case 3:
		{
			OutputArray(tubes);
			int id;
			while (true)
			{
				cout << "Введите номер трубы, которую вы хотите добавить в редактирование: " << endl
					<< "Для прекращения ввода, введите 0" << endl;
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
			break;
		}
		default:
			break;
		}
		SetStatus(tubes, id_of_tubes);
		cout << "Преобразования применены к выбранным трубам" << endl;
	}
}

void EditStations(unordered_map <int, cs>& stations)
{
	if (stations.empty())
	{
		cout << "КС еще не созданы\n";
	}
	else
	{
		vector<int> id_of_stations;
		cout << "------------ Редактирование КС ------------\n";
		cout << "Выберите 1, если хотите редактировать КС, найденные по названию" << endl
			<< "          2, если хотите редактировать КС, найденные по проценту незадействованных цехов" << endl
			<< "          3, если хотите редактировать КС среди всех созданных" << endl;

		switch (GetCorrectNumber(1, 3))
		{
		case 1:
			id_of_stations = FindCsByName(stations);
			break;
		case 2:
			id_of_stations = FindCsByRooms(stations);
			break;
		case 3:
		{
			OutputArray(stations);
			int id;
			while (true)
			{
				cout << "Введите номер КС, которую вы хотите добавить в редактирование: " << endl
					<< "Для прекращения ввода, введите 0" << endl;
				cin >> id;
				if (id == 0)
				{
					break;
				}
				if (stations.find(id) != stations.end() and find(id_of_stations.begin(), id_of_stations.end(), id) == id_of_stations.end())
				{
					id_of_stations.push_back(id);
					continue;
				}
			}
			break;
		}
		default:
			break;
		}
		ChangeCsParameter(id_of_stations, stations);
		cout << "Преобразования применены к выбранным КС" << endl;
	}
}

void DeleteTubes(unordered_map <int, tube>& tubes)
{
	if (tubes.empty())
	{
		cout << "Трубы еще не созданы\n";
	}
	else
	{
		vector<int> id_of_tubes;
		cout << "------------ Удаление Труб ------------\n";
		cout << "Выберите 1, если хотите удалить трубы, найденные по названию" << endl
			<< "          2, если хотите удалить трубы, найденные по признаку 'в ремонте'" << endl
			<< "          3, если хотите удалить трубы среди всех созданных" << endl;
		switch (GetCorrectNumber(1, 3))
		{
		case 1:
			id_of_tubes = FindTubesByName(tubes);
			break;
		case 2:
			id_of_tubes = FindTubesByStatus(tubes);
			break;
		case 3:
		{
			OutputArray(tubes);
			int id;
			while (true)
			{
				cout << "Введите номер трубы, которую вы хотите добавить в удаление: " << endl
					<< "Для прекращения ввода, введите 0" << endl;
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
			break;
		}
		default:
			break;
		}
		CleanMas(tubes, id_of_tubes);
		cout << "Выбранные трубы удалены" << endl;
	}
}

void DeleteStations(unordered_map <int, cs>& stations)
{
	if (stations.empty())
	{
		cout << "КС еще не созданы\n";
	}
	else
	{
		vector<int> id_of_stations;
		cout << "------------ Редактирование КС ------------\n";
		cout << "Выберите 1, если хотите редактировать КС, найденные по названию" << endl
			<< "          2, если хотите редактировать КС, найденные по проценту незадействованных цехов" << endl
			<< "          3, если хотите редактировать КС среди всех созданных" << endl;

		switch (GetCorrectNumber(1, 3))
		{
		case 1:
			id_of_stations = FindCsByName(stations);
			break;
		case 2:
			id_of_stations = FindCsByRooms(stations);
			break;
		case 3:
		{
			OutputArray(stations);
			int id;
			while (true)
			{
				cout << "Введите номер КС, которую вы хотите добавить в редактирование: " << endl
					<< "Для прекращения ввода, введите 0" << endl;
				cin >> id;
				if (id == 0)
				{
					break;
				}
				if (stations.find(id) != stations.end() and find(id_of_stations.begin(), id_of_stations.end(), id) == id_of_stations.end())
				{
					id_of_stations.push_back(id);
					continue;
				}
			}
			break;
		}
		default:
			break;
		}
		CleanMas(stations, id_of_stations);
		cout << "Выбранные КС удалены" << endl;
	}
}

void Save(unordered_map <int, tube>& tubes, unordered_map <int, cs>& stations)
{
	string name_of_file;
	cout << "Введите название файла, в который нужно сохранить данные: ";
	getline(cin >> ws, name_of_file);
	ofstream out(name_of_file + ".txt");
	if (out.is_open())
	{
		out << tubes.size() << endl;
		out << tube::GetMaxId() << endl;
		out << stations.size() << endl;
		out << cs::GetMaxId() << endl;
		if (tubes.empty())
		{
			cout << "Трубы еще не созданы\n";
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
			cout << "Данные по трубам сохранены\n\n";
		}
		if (stations.empty())
		{
			cout << "КС еще не созданы\n";
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
			cout << "Данные по КС сохранены\n\n";
		}
	}
	out.close();
}

void Download(unordered_map <int, tube>& tubes, unordered_map <int, cs>& stations)
{
	int number_of_tubes, number_of_cs, cs_max_id, tube_max_id;
	string name_of_file;
	cout << "Введите название файла, из которого нужно считать данные: ";
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
			new_cs.SetMaxId(cs_max_id);
			in >> new_cs.id;
			getline(in >> ws, new_cs.name);
			in >> new_cs.rooms;
			in >> new_cs.active_rooms;
			in >> new_cs.efficiency;
			stations.emplace(new_cs.id, new_cs);
		}
		cout << "Данные загружены\n";
	}
	in.close();
}

void ShowMenu()
{
	cout << "1. Добавить трубу\n";
	cout << "2. Добавить КС\n";
	cout << "3. Удаление труб\n";
	cout << "4. Удаление КС\n";
	cout << "5. Просмотр всех объектов\n";
	cout << "6. Редактирование труб\n";
	cout << "7. Редактирование КС\n";
	cout << "8. Сохранить\n";
	cout << "9. Загрузить\n";
	cout << "0. Выход\n";
}

void Run()
{
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
			DeleteTubes(tubes);
			break;
		case 4:
			DeleteStations(stations);
			break;
		case 5:
			ViewAllObjects(tubes, stations);
			break;
		case 6:
			EditTubes(tubes);
			break;
		case 7:
			EditStations(stations);
			break;
		case 8:
			Save(tubes, stations);
			break;
		case 9:
			Download(tubes, stations);
			break;
		case 0:
			exit(0);
		default:
			cout << "Введенные данные не корректны. Пожалуйста, укажите номер интересующего вас пункта.\n\n";
			break;
		}
	}
}

int main()
{
	setlocale(0, "");
	Run();
}