#pragma once
#include <iostream>

template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail() || std::cin.peek() != '\n' || x > max || x < min)
	{
		std::cout << "¬веденные данные не корректны\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	return x;
}