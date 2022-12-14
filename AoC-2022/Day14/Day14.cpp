#include "Day14.h"

#define INPUT "Day14/1.IN"
#define INF numeric_limits<int>::max()

inline void PrintCave(vector<vector<char>>& map)
{
	for (auto& line : map)
	{
		for (auto& ch : line)
			cout << ch;
		cout << "\n";
	}
}

void Day14::Part1()
{
    ScopedTimer timer;

	vector<string> delimiters = { "->", " "};
	auto input = Utils::ReadInput2D(INPUT, delimiters);

	// Generate pair<int, int>
	int minX = INF, minY = INF;
	vector<vector<pair<int, int>>> verticies(input.size());
	for (size_t i = 0; i < input.size(); i++)
	{
		for (size_t j = 0; j < input[i].size(); j++)
		{
			auto pair = Utils::GetIntPairFromString(input[i][j]);
			verticies[i].push_back(pair);
			if (pair.first < minX)
				minX = pair.first;
			if (pair.second < minY)
				minY = pair.second;
		}
	}

	// Normalize pairs
	int maxX = 0; int maxY = 0;
	for (auto& line : verticies)
	{
		for (auto& pair : line)
		{
			pair.first -= minX;
			if (pair.first > maxX)
				maxX = pair.first;
			if (pair.second > maxY)
				maxY = pair.second;
		}
	}

	// Create cave slice
	vector<vector<char>> caveMap(maxY+1, vector<char>(maxX+1, '.'));
	for (size_t i = 0; i < verticies.size(); i++)
	{
		for (size_t j = 0; j < verticies[i].size() - 1; j++)
		{
			auto vert1 = verticies[i][j];
			auto vert2 = verticies[i][j+1];

			int x = vert2.first - vert1.first;
			int y = vert2.second - vert1.second;

			bool xNeg = x < 0; bool yNeg = y < 0;
			for (size_t dx = 0; dx < abs(x) + 1; dx++)
			{
				int sign = 1;
				if (xNeg) sign *= -1;
				caveMap[vert1.second][vert1.first + dx * sign] = '#';
			}
			for (size_t dy = 0; dy < abs(y) + 1; dy++)
			{
				int sign = 1;
				if (yNeg) sign *= -1;
				caveMap[vert1.second + dy * sign][vert1.first] = '#';
			}
		}
	}

	// Simulate sand
	int sandCount = 0;
	bool shouldEnd = false;
	while (!shouldEnd)
	{
		int startX = 500 - minX;
		int startY = 0;
		int dx = 0; int dy = 0;
		while (caveMap[startY + 1 + dy][startX + dx] == '.' || caveMap[startY + 1 + dy][startX - 1 + dx] == '.' || caveMap[startY + 1 + dy][startX + 1 + dx] == '.')
		{
			if (caveMap[startY + 1 + dy][startX + dx] == '.')
			{
				dy++;
			}
			else if (caveMap[startY + 1 + dy][startX - 1 + dx] == '.')
			{
				dy++;
				dx--;
			}
			else if (caveMap[startY + 1 + dy][startX + 1 + dx] == '.')
			{
				dy++;
				dx++;
			}
			
			if (startY + dy >= maxY || startX + dx <= 0 || startX + dx >= maxX)
			{
				shouldEnd = true;
				break;
			}
		}
		if (!shouldEnd)
		{
			sandCount++;
			caveMap[startY + dy][startX + dx] = 'o';
		}
	}
	//PrintCave(caveMap);	
	printf("Sand count: %d", sandCount);
}

void Day14::Part2()
{
	ScopedTimer timer;

	vector<string> delimiters = { "->", " " };
	auto input = Utils::ReadInput2D(INPUT, delimiters);

	int xOffset = 150;
	int yOffset = 2;

	// Generate pair<int, int>
	int minX = INF, minY = INF;
	vector<vector<pair<int, int>>> verticies(input.size());
	for (size_t i = 0; i < input.size(); i++)
	{
		for (size_t j = 0; j < input[i].size(); j++)
		{
			auto pair = Utils::GetIntPairFromString(input[i][j]);
			verticies[i].push_back(pair);
			if (pair.first < minX)
				minX = pair.first;
			if (pair.second < minY)
				minY = pair.second;
		}
	}

	// Normalize pairs
	int maxX = 0; int maxY = 0;
	for (auto& line : verticies)
	{
		for (auto& pair : line)
		{
			pair.first -= minX;
			pair.first += xOffset;
			if (pair.first > maxX)
				maxX = pair.first;
			if (pair.second > maxY)
				maxY = pair.second;
		}
	}

	// Create cave slice
	vector<vector<char>> caveMap(maxY + 1 + yOffset, vector<char>(maxX + 1 + xOffset, '.'));
	for (auto& c : caveMap[maxY + yOffset])
		c = '#';
	for (auto& line : caveMap)
	{
		line[0] = '#';
		line[maxX + xOffset] = '#';
	}
	for (size_t i = 0; i < verticies.size(); i++)
	{
		for (size_t j = 0; j < verticies[i].size() - 1; j++)
		{
			auto vert1 = verticies[i][j];
			auto vert2 = verticies[i][j + 1];

			int x = vert2.first - vert1.first;
			int y = vert2.second - vert1.second;

			bool xNeg = x < 0; bool yNeg = y < 0;
			for (size_t dx = 0; dx < abs(x) + 1; dx++)
			{
				int sign = 1;
				if (xNeg) sign *= -1;
				caveMap[vert1.second][vert1.first + dx * sign] = '#';
			}
			for (size_t dy = 0; dy < abs(y) + 1; dy++)
			{
				int sign = 1;
				if (yNeg) sign *= -1;
				caveMap[vert1.second + dy * sign][vert1.first] = '#';
			}
		}
	}

	// Simulate sand
	int sandCount = 0;
	bool shouldEnd = false;
	while (!shouldEnd)
	{
		int startX = 500 - minX + xOffset;
		int startY = 0;
		int dx = 0; int dy = 0;
		bool moreSand = caveMap[startY + 1 + dy][startX + dx] == '.' || caveMap[startY + 1 + dy][startX - 1 + dx] == '.' || caveMap[startY + 1 + dy][startX + 1 + dx] == '.';
		if (!moreSand) break;
		while (caveMap[startY + 1 + dy][startX + dx] == '.' || caveMap[startY + 1 + dy][startX - 1 + dx] == '.' || caveMap[startY + 1 + dy][startX + 1 + dx] == '.')
		{
			if (caveMap[startY + 1 + dy][startX + dx] == '.')
			{
				dy++;
			}
			else if (caveMap[startY + 1 + dy][startX - 1 + dx] == '.')
			{
				dy++;
				dx--;
			}
			else if (caveMap[startY + 1 + dy][startX + 1 + dx] == '.')
			{
				dy++;
				dx++;
			}

			if (startY + dy >= maxY + yOffset || startX + dx <= 0 || startX + dx >= maxX + xOffset)
			{
				shouldEnd = true;
				break;
			}
		}
		if (!shouldEnd)
		{
			sandCount++;
			caveMap[startY + dy][startX + dx] = 'o';
		}
	}
	// PrintCave(caveMap);
	printf("Sand count: %d", sandCount + 1);
}
