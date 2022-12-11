#include "Day10.h"

#define INPUT "Day10/1.IN"

void Day10::Part1()
{
	ScopedTimer timer;
	
	std::vector<std::string> delimiter = { " " };
	auto input = Utils::ReadInput2D(INPUT, delimiter);

	int x = 1;
	int cycle = 1;
	int sumOfSignals = 0;
	int nextStrengthCalculation = 20;
	for (size_t i = 0; i < input.size(); i++)
	{
		std::string op = input[i][0];

		if (op == "addx") 
		{
			x += std::stoi(input[i][1]);
			cycle += 2;
		}
		else if (op == "noop")
		{
			cycle++;
		}

		if (cycle + 1 >= nextStrengthCalculation)
		{
			int signalStrength = nextStrengthCalculation * x;
			sumOfSignals += signalStrength;
			printf("Signal strength: %d\n", signalStrength);
			nextStrengthCalculation += 40;
		}
	}	
	printf("Sum of signals: %d", sumOfSignals);
}

int RenderCRT(int spritePos, int crtPos, int cycle, int nextStrengthCalculation)
{
	if (spritePos - 1 == crtPos || spritePos == crtPos || spritePos + 1 == crtPos)
		std::cout << "#";
	else
		std::cout << ".";
	if (cycle >= nextStrengthCalculation)
	{
		nextStrengthCalculation += 40;
		std::cout << "\n";
		return nextStrengthCalculation;
	}
	return nextStrengthCalculation;
}

void Day10::Part2()
{
	ScopedTimer timer;

	std::vector<std::string> delimiter = { " " };
	auto input = Utils::ReadInput2D(INPUT, delimiter);
	std::cout << "";

	int x = 1;
	int cycle = 1;
	int nextStrengthCalculation = 40;
	for (size_t i = 0; i < input.size(); i++)
	{
		std::string op = input[i][0];

		if (op == "addx")
		{
			nextStrengthCalculation = RenderCRT(x + 1, (cycle) % 40, cycle, nextStrengthCalculation);
			cycle++;
			nextStrengthCalculation = RenderCRT(x + 1, (cycle) % 40, cycle, nextStrengthCalculation);
			cycle++;
			x += std::stoi(input[i][1]);
		}
		else if (op == "noop")
		{
			nextStrengthCalculation = RenderCRT(x + 1, (cycle) % 40, cycle, nextStrengthCalculation);
			cycle++;
		}
	}
}