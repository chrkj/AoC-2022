#include "Day03.h"

int calculatePrioSum(char c)
{
	int value = (int)c;
	if (value < 96)
		return value - 38;
	else
		return value - 96;
}

void Day03::part1()
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

		prioritySum += calculatePrioSum(duplicate);
	}
	printf("Sum: %d", prioritySum);
}

void Day03::part2()
{

}