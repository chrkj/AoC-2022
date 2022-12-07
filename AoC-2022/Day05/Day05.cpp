#include "Day05.h"

#define INPUT "Day05/1.IN"

void Day05::Part1()
{
	ScopedTimer timer;

	std::vector<std::string> delimiters = { "move ", " from ", " to " };
	std::vector<std::vector<std::string>> input = Utils::ReadInput2D(INPUT, delimiters);

	int32_t stackSize = (input[0][0].size() + 1) / 4;
	std::vector<std::deque<char>> stacks(stackSize);

	int lineIndex = 0;
	while (input[lineIndex][0][1] != '1') 
	{
		for (size_t index = 1, stackIndex = 0; index < input[0][0].size(); index += 4, stackIndex++)
		{
			char currentChar = input[lineIndex][0][index];
			if (currentChar != ' ')
				stacks[stackIndex].push_back(currentChar);
		}
		lineIndex++;
	}
	lineIndex += 2; // Skip to procedures

	while (lineIndex < input.size())
	{
		int32_t amountToMove = stoi(input[lineIndex][0]);
		int32_t fromStack = stoi(input[lineIndex][1]) - 1;
		int32_t toStack = stoi(input[lineIndex][2]) - 1;
		for (size_t i = 0; i < amountToMove; i++)
		{
			char charToMove = stacks[fromStack].front();
			stacks[fromStack].pop_front();
			stacks[toStack].push_front(charToMove);
		}
		lineIndex++;
	}

	for (size_t i = 0; i < stacks.size(); i++)
		std::cout << stacks[i].front();
}

void Day05::Part2()
{
	ScopedTimer timer;

	std::vector<std::string> delimiters = { "move ", " from ", " to " };
	std::vector<std::vector<std::string>> input = Utils::ReadInput2D(INPUT, delimiters);

	int32_t stackSize = (input[0][0].size() + 1) / 4;
	std::vector<std::deque<char>> stacks(stackSize);

	int lineIndex = 0;
	while (input[lineIndex][0][1] != '1')
	{
		for (size_t index = 1, stackIndex = 0; index < input[0][0].size(); index += 4, stackIndex++)
		{
			char currentChar = input[lineIndex][0][index];
			if (currentChar != ' ')
				stacks[stackIndex].push_back(currentChar);
		}
		lineIndex++;
	}
	lineIndex += 2; // Skip to procedures

	while (lineIndex < input.size())
	{
		std::deque<char> creates;
		int32_t amountToMove = stoi(input[lineIndex][0]);
		int32_t fromStack = stoi(input[lineIndex][1]) - 1;
		int32_t toStack = stoi(input[lineIndex][2]) - 1;

		for (size_t i = 0; i < amountToMove; i++)
		{
			char charToMove = stacks[fromStack].front();
			stacks[fromStack].pop_front();
			creates.push_front(charToMove);
		}

		for (size_t i = 0; i < amountToMove; i++)
		{
			stacks[toStack].push_front(creates.front());
			creates.pop_front();
		}
		lineIndex++;
	}

	for (size_t i = 0; i < stacks.size(); i++)
		std::cout << stacks[i].front();
}