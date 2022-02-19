#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <Windows.h>
#include <stdio.h>

#define EXPECTED_CONSOLE_LENGTH 80

long double calculateDenominator(int b1, int b2, int b3, long double previous)
{
	return (b1 * previous * previous + b2 * previous + b3);
}

long double calculateMember(int a1, int a2, int a3, long double denominator, long double previous)
{
	return (a1 * previous * previous + a2 * previous + a3) / denominator;
}

int numberOfDigits(int number)
{
	int i = 0;
	while (number > 0)
	{
		number /= 10;
		i++;
	}
	return i;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int a1 = 2, a2 = 10, a3 = 80, b1 = 0, b2 = 1, b3 = -8;
	std::cout << "Въведете начален член и натиснете Enter: ";
	long double lambda;
	std::cin >> lambda;

	while (b1 * lambda * lambda + b2 * lambda + b3 == 0)
	{
		std::cout << "Знаменятелят е нула. Въведете нов начален член: ";
		std::cin >> lambda;
	}
	int tempIndex;
	std::set<int> indexes;
	std::cout
		<< "Въведете номер на член за изчисление и натиснете Enter. За край на въвеждането въведете 0 или отрицателно число: ";
	std::cin >> tempIndex;
	while (tempIndex > 0)
	{
		indexes.insert(tempIndex);
		std::cout << "Следващ номер: ";
		std::cin >> tempIndex;
	}
	if (indexes.empty())
	{
		std::cout << "Няма валидни индекси за изчисление. Край на програмата";
		std::cin.get();
		return 1;
	}
	std::map<int, double> results;
	long double denominator;
	long double temp = lambda;
	for (int i = 2; i <= *indexes.rbegin(); i++)
	{
		denominator = calculateDenominator(b1, b2, b3, temp);
		if (denominator == 0)
		{
			std::cout << "Знаменател на" << " позиция " << i << " е нула. Край на изчислението";
			break;
		}
		temp = calculateMember(a1, a2, a3, denominator, temp);
		if (indexes.find(i) != indexes.end())
		{
			results.emplace(i, temp);
		}
	}

	int indexWidth = numberOfDigits(results.rbegin()->first) + 1;
	std::cout << "\n" << std::left << std::setw(indexWidth) << std::setfill(' ') << "N."
		<< std::left << std::setw((unsigned __int64)EXPECTED_CONSOLE_LENGTH - indexWidth) << std::setfill(' ') << " -> Стойност";
	for (int i = 0; i < EXPECTED_CONSOLE_LENGTH - 1; i++)
	{
		std::cout << "-";
	}
	std::cout << std::endl;
	std::cout << std::left << std::setw(indexWidth) << std::setfill(' ') << "1" << " -> "
		<< std::left << std::setw((unsigned __int64)EXPECTED_CONSOLE_LENGTH - indexWidth) << std::setfill(' ') << std::setprecision(20) << lambda << std::endl;
	for (const std::pair<int, double>& pair : results)
	{
		std::cout << std::left << std::setw(indexWidth) << std::setfill(' ') << pair.first << " -> "
			<< std::left << std::setw((unsigned __int64)EXPECTED_CONSOLE_LENGTH - indexWidth) << std::setfill(' ') << std::setprecision(20) << pair.second
			<< std::endl;
	}
	std::cin.get();
	return 0;
}
