#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
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

template <typename T>
int FindMaxId(T mas)
{
	int current_id;
	int max_id = 1;
	for (auto& element : mas)
	{
		current_id = element.first;
		if (current_id > max_id)
		{
			max_id = current_id;
		}
	}
	return max_id;
}

double UserInputParameter()
{
	double parameter;
	cin >> parameter;
	while (cin.fail() || cin.peek() != '\n' || parameter <= 0)
	{
		cout << "Введенные данные не корректны\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> parameter;
	}
	return parameter;
}

int UserInputIndex()
{
	int parameter;
	cin >> parameter;
	while (cin.fail() || cin.peek() != '\n' || parameter < 0)
	{
		cout << "Введенные данные не корректны\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> parameter;
	}
	return parameter;
}

int InputRooms()
{
	int rooms;
	cin >> rooms;
	while (cin.fail() || cin.peek() != '\n' || rooms <= 0)
	{
		cout << "Введенные данные не корректны\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> rooms;
	}
	return rooms;
}

string InputName()
{
	string name;
	cin >> name;
	while (cin.fail() || cin.peek() != '\n')
	{
		cout << "Введенные данные не корректны\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> name;
	}
	return name;
}

int InputActiveRooms(cs& new_cs)
{
	int active_rooms;
	cin >> active_rooms;
	while (cin.fail() || cin.peek() != '\n' || active_rooms > new_cs.rooms || active_rooms < 0)
	{
		cout << "Введенные данные не корректны\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> active_rooms;
	}
	return active_rooms;
}

int InputEfficiency()
{
	int efficiency;
	cin >> efficiency;
	while (cin.fail() || cin.peek() != '\n' || efficiency <= 0 || efficiency > 5)
	{
		cout << "Введенные данные не корректны\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> efficiency;
	}
	return efficiency;
}

int CorrectChoice()
{
	int user_choice;
	do
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> user_choice;
	} while (cin.fail() || user_choice < 0 || user_choice > 1);
	return user_choice;
}

bool IsCorrectMenuChoice(int user_choice)
{
	if (cin.fail() || cin.peek() != '\n' || user_choice < 0 || user_choice > 12)
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Данные не корректны" << endl;
		return false;
	}
	return true;
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

double ReadValue(ifstream& in)
{
	double parameter = 0;
	if (in.fail() || in.peek() != '\n')
	{
		in >> parameter;
	}
	return parameter;
}

string ReadName(ifstream& in)
{
	string name;
	if (in.fail() || in.peek() != '\n')
	{
		in >> name;
	}
	return name;
}

int GetCorrectId(int min, int max)
{
	int x;
	while ((cin >> x).fail() || x > max || x < min)
	{
		cout << "Введенные данные не корректны\n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return x;
}

tube& SelectTube(unordered_map <int, tube>& tubes)
{
	cout << "Введите номер трубы:" << endl;
	int id = GetCorrectId(1, tubes.size());
	return tubes[id];
}

cs& SelectCS(unordered_map <int, cs>& stations)
{
	cout << "Введите номер трубы:" << endl;
	int id = GetCorrectId(1, stations.size());
	return stations[id];
}

template <typename T>
using Filter1 = bool(*)(cs new_cs, T param);

bool CheckCSByName(cs new_cs, string param)
{
	return new_cs.name == param;
}

bool CheckByRooms(cs new_cs, int percent)
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

bool CheckTubeByName(tube new_tube, string param)
{
	return new_tube.name == param;
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

void CreateTube(unordered_map <int, tube>& tubes)
{
	tube new_tube;
	cout << "Введите название: ";
	getline(cin >> ws, new_tube.name);
	cout << "Введите длину в метрах (используйте <.>): ";
	new_tube.length = UserInputParameter();
	cout << "Введите диаметр в метрах (используйте <.>): ";
	new_tube.diameter = UserInputParameter();
	cout << "Труба исправна\n\n";
	new_tube.condition = 1;
	tubes.emplace(new_tube.id, new_tube);
}

void CreateStation(unordered_map <int, cs>& stations)
{
	cs new_cs;
	cout << "Введите название: ";
	getline(cin >> ws, new_cs.name);
	cout << "Укажите количество цехов: ";
	new_cs.rooms = InputRooms();
	cout << "Укажите количество работающих цехов: ";
	new_cs.active_rooms = InputActiveRooms(new_cs);
	cout << "Введите значение эффективности (от 1 до 5): ";
	new_cs.efficiency = InputEfficiency();
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

void EditTube(tube& new_tube)
{
	if (new_tube.length == 0)
	{
		cout << "Труба еще не создана\n";
	}
	else
	{
		cout << "------------ Редактирование Трубы ------------\n";
		cout << "Введите значение состояния:\n";
		cout << "<1> - Труба исправна  <0> - Труба в ремонте\n";
		switch (CorrectChoice())
		{
		case 1:
			new_tube.condition = 1;
			break;
		case 0:
			new_tube.condition = 0;
			break;
		default:
			cout << "Введенные данные не корректны.\n";
			break;
		}
	}
}

void EditStation(cs& new_cs)
{
	if (new_cs.rooms == 0)
	{
		cout << "КС еще не создана\n";
	}
	else
	{
		cout << "------------ Редактирование КС ------------\n";
		cout << "Количество работающих цехов на данный момент: " << new_cs.active_rooms << endl;
		cout << "<0> - Убрать активный цех, <1> - Добавить активный цех\n";
		switch (CorrectChoice())
		{
		case 1:
			if (IsPosibleTransformationAdd(new_cs))
			{
				new_cs.active_rooms++;
				cout << "Кол-во работающих цехов: " << new_cs.active_rooms << endl;
			}
			break;
		case 0:
			if (IsPosibleTransformationSub(new_cs))
			{
				new_cs.active_rooms--;
				cout << "Кол-во работающих цехов: " << new_cs.active_rooms << endl;
			}
			break;
		default:
			break;
		}
	}
}

void Save(unordered_map <int, tube>& tubes, unordered_map <int, cs>& stations)
{
	ofstream out("Data.txt");
	if (out.is_open())
	{
		out << tubes.size() << endl;
		out << FindMaxId(tubes) << endl;
		out << stations.size() << endl;
		out << FindMaxId(stations) << endl;
		if (tubes.empty())
		{
			cout << "Трубы еще не созданы\n";
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
	tube new_tube;
	cs new_cs;
	int number_of_tubes, number_of_cs;
	ifstream in("Data.txt");
	if (in.is_open())
	{
		in >> number_of_tubes;
		in >> new_tube.max_id;
		in >> number_of_cs;
		in >> new_cs.max_id;
		while (number_of_tubes--)
		{
			in >> new_tube.id;
			getline(in >> ws, new_tube.name);
			in >> new_tube.length;
			in >> new_tube.diameter;
			in >> new_tube.condition;
			tubes.emplace(new_tube.id, new_tube);
		}
		while (number_of_cs--)
		{
			in >> new_cs.id;
			getline(in >> ws, new_cs.name);
			in >> new_cs.rooms;
			in >> new_cs.active_rooms;
			in >> new_cs.efficiency;
			stations.emplace(new_cs.id, new_cs);
		}
	}
	in.close();
	cout << "Данные загружены\n";
}

void ShowMenu()
{
	cout << "1. Добавить трубу\n";
	cout << "2. Добавить КС\n";
	cout << "3. Удалить трубу\n";
	cout << "4. Просмотр всех объектов\n";
	cout << "5. Редактировать трубу\n";
	cout << "6. Редактировать КС\n";
	cout << "7. Поиск КС по названию\n";
	cout << "8. Поиск КС по проценту незадействованных цехов\n";
	cout << "9. Поиск труб по названию\n"; 
	cout << "10. Поиск труб по признаку 'в ремонте'\n";
	cout << "11. Сохранить\n";
	cout << "12. Загрузить\n";
	cout << "0. Выход\n";
}

int Menu(unordered_map <int, tube>& tubes, unordered_map <int, cs>& stations, vector<int>& indexes_of_stations)
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
		tubes.erase(UserInputIndex());
		return 1;
	case 4:
		ViewAllObjects(tubes, stations);
		return 1;
	case 5:
		EditTube(SelectTube(tubes));
		return 1;
	case 6:
		EditStation(SelectCS(stations));
		return 1;
	case 7:
		cout << "Введите название: ";
		cin >> name_of_object;
		for (int element : FindCsByFilter(stations, CheckCSByName, name_of_object))
		{
			cout << stations[element] << endl;
		}
		return 1;
	case 8:
		int percent;
		cout << "Введите процент: ";
		cin >> percent;
		for (int element : FindCsByFilter(stations, CheckByRooms, percent))
		{
			cout << stations[element] << endl;
		}
		return 1;
	case 9:
		cout << "Введите название: ";
		cin >> name_of_object;
		for (int element : FindTubesByFilter(tubes, CheckTubeByName, name_of_object))
		{
			cout << stations[element] << endl;
		}
		return 1;
	case 10:

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
		cout << "Введенные данные не корректны. Пожалуйста, укажите номер интересующего вас пункта.\n\n";
		return 1;
	}
}

int main()
{
	setlocale(0, "");
	vector<int> indexes_of_stations;
	unordered_map <int, tube> tubes;
	unordered_map <int, cs> stations;
	do { ShowMenu(); } while (Menu(tubes, stations, indexes_of_stations) != 0);
}