#include "Day03.h"

int GetPrioValue(char c)
{
	int value = (int)c;
	if (value < 96)
		return value - 38;
	else
		return value - 96;
}

void Day03::Part1()
{
	ScopedTimer timer;
	
	std::string currentLine;
	std::ifstream input("Day03/TEST.IN");

	int32_t prioritySum = 0;
	while (getline(input, currentLine))
	{
		char duplicate;
		std::unordered_set<char> compartmentOne;

		for (size_t i = 0; i < currentLine.size() / 2; i++)
			compartmentOne.insert(currentLine[i]);

		for (size_t i = currentLine.size() / 2; i < currentLine.size(); i++) 
		{
			if (compartmentOne.contains(currentLine[i]))
			{
				duplicate = currentLine[i];
				break;
			}
		}

		prioritySum += GetPrioValue(duplicate);
	}
	printf("Sum: %d", prioritySum);
}

void Day03::Part2()
{
	ScopedTimer timer;

	std::string currentLine;
	std::ifstream input("Day03/1.IN");

	int32_t prioritySum = 0;
	while (getline(input, currentLine))
	{
		char badge;
		std::unordered_set<char> firstSet;
		std::unordered_set<char> secondSet;
		
		for (size_t i = 0; i < currentLine.length(); i++)
			firstSet.insert(currentLine[i]);

		getline(input, currentLine);
		for (size_t j = 0; j < currentLine.length(); j++)
		{
			if (firstSet.contains(currentLine[j]))
				secondSet.insert(currentLine[j]);
		}

		getline(input, currentLine);
		for (size_t k = 0; k < currentLine.length(); k++)
		{
			if (secondSet.contains(currentLine[k]))
				badge = currentLine[k];
		}

		prioritySum += GetPrioValue(badge);
	}
	printf("Sum: %d", prioritySum);
}