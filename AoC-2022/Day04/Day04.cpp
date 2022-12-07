#include "Day04.h"

void Day04::Part1()
{
	ScopedTimer timer;

	std::vector<std::string> delimiters = { ",", "-" };
	std::vector<std::vector<int>> input = Utils::InputToInt2D(Utils::ReadInput2D("Day04/1.IN", delimiters));

	int32_t count = 0;
	for (const auto& line : input) 
	{
		if ((line[0] >= line[2] && line[1] <= line[3]) || (line[2] >= line[0] && line[3] <= line[1])) 
			count++;
	}
	printf("Count: %d", count);
}

void Day04::Part2()
{
	ScopedTimer timer;

	std::vector<std::string> delimiters = { ",", "-" };
	std::vector<std::vector<int>> input = Utils::InputToInt2D(Utils::ReadInput2D("Day04/1.IN", delimiters));

	int32_t count = 0;
	for (const auto& line : input)
	{
		if ((line[0] <= line[2] && line[1] >= line[2]) || (line[2] <= line[0] && line[3] >= line[0]))
			count++;
	}
	printf("Count: %d", count);
}