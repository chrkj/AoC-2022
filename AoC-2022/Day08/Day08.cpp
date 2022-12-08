#include "Day08.h"

#define INPUT "Day08/1.IN"

bool TraverseDir(const std::vector<std::vector<int>>& forrest, int currentHeight, int x, int y, int xDir, int yDir)
{
	x += xDir;
	y += yDir;
	while (x >= 0 && y >= 0 && x <= forrest.size() - 1 && y <= forrest[0].size() - 1)
	{
		if (forrest[y][x] >= currentHeight)
			return false;
		x += xDir;
		y += yDir;
	}
	return true;
}

int CalculateScore(const std::vector<std::vector<int>>& forrest, int currentHeight, int x, int y, int xDir, int yDir)
{
	int score = 0;
	x += xDir;
	y += yDir;
	while (x >= 0 && y >= 0 && x <= forrest.size() - 1 && y <= forrest[0].size() - 1)
	{
		if (forrest[y][x] >= currentHeight)
			return score + 1;
		x += xDir;
		y += yDir;
		score++;
	}
	return score;
}

int FindMaxNumVisable(const std::vector<std::vector<int>>& forrest) 
{
	// could optimize by caching largest seen tree in a given direction
	int numVisable = 0;
	for (size_t treeline = 0; treeline < forrest.size(); treeline++)
	{
		for (size_t tree = 0; tree < forrest[treeline].size(); tree++)
		{
			int currentTreeHeight = forrest[treeline][tree];

			bool left = TraverseDir(forrest, currentTreeHeight, tree, treeline, -1, 0);
			bool right = TraverseDir(forrest, currentTreeHeight, tree, treeline, 1, 0);
			bool up = TraverseDir(forrest, currentTreeHeight, tree, treeline, 0, 1);
			bool down = TraverseDir(forrest, currentTreeHeight, tree, treeline, 0, -1);
		
			if (left || right || up || down)
				numVisable++;
		}
	}
	return numVisable;
}

int FindMaxScenicScore(const std::vector<std::vector<int>>& forrest)
{
	int maxScore = 0;
	for (size_t treeline = 0; treeline < forrest.size(); treeline++)
	{
		for (size_t tree = 0; tree < forrest[treeline].size(); tree++)
		{
			int currentTreeHeight = forrest[treeline][tree];

			int left = CalculateScore(forrest, currentTreeHeight, tree, treeline, -1, 0);
			int right = CalculateScore(forrest, currentTreeHeight, tree, treeline, 1, 0);
			int up = CalculateScore(forrest, currentTreeHeight, tree, treeline, 0, 1);
			int down = CalculateScore(forrest, currentTreeHeight, tree, treeline, 0, -1);

			if ((left * right * up * down) > maxScore) 
				maxScore = left * right * up * down;
		}
	}
	return maxScore;
}

void Day08::Part1()
{
	ScopedTimer timer;

	auto input = Utils::StringToVectorOfInts(Utils::ReadInput(INPUT));

	printf("Max number of visible trees: %d" , FindMaxNumVisable(input));
}

void Day08::Part2()
{
	ScopedTimer timer;

	auto input = Utils::StringToVectorOfInts(Utils::ReadInput(INPUT));

	printf("Max scenic score: %d", FindMaxScenicScore(input));
}