#include "Day06.h"
#include <Utils/Utils.h>

int getMarkerIndex(std::string data, uint32_t distanctCharaters)
{
	std::map<char, int> map;
	for (size_t rightPtr = 0, leftPtr = 0; rightPtr < data.length(); rightPtr++)
	{
		char currentChar = data[rightPtr];
		if (map.contains(currentChar) && map[currentChar] >= leftPtr)
			leftPtr = map[currentChar] + 1;

		map[currentChar] = rightPtr;
		if ((rightPtr - leftPtr) >= distanctCharaters - 1)
		{
			return rightPtr + 1;
			break;
		}
	}
}

void Day06::part1()
{
	ScopedTimer timer;

	std::string dataStream;
	std::ifstream input("Day06/1.IN");
	getline(input, dataStream);
	printf("Index: %d", getMarkerIndex(dataStream, 4));
}

void Day06::part2()
{
	ScopedTimer timer;

	std::string dataStream;
	std::ifstream input("Day06/1.IN");
	getline(input, dataStream);
	printf("Index: %d", getMarkerIndex(dataStream, 14));
}