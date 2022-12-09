#include "Day09.h"

#define INPUT "Day09/1.IN"

struct hashFunction
{
	size_t operator()(const pair<int, int>& x) const
	{
		return x.first ^ x.second;
	}
};

struct Knot
{
	int x = 0;
	int y = 0;

	Knot() {}

	Knot(int x, int y)
		: x(x), y(y)
	{}

	void right() { x++; }
	void left()	 { x--; }
	void up()	 { y++; }
	void down()  { y--; }
	void upRight()	 { y++; x++; }
	void upLeft()	 { y++; x--; }
	void downRight() { y--; x++; }
	void downLeft()  { y--; x--; }
};

bool operator==(const Knot& lhs, const Knot& rhs)
{
	if (lhs.x == rhs.x && lhs.y == rhs.y) return true;
	else return false;
}

void Day09::Part1()
{
	ScopedTimer timer;

	auto input = Utils::StringToPair<char, int>(Utils::ReadInput(INPUT));

	std::unordered_set<std::pair<int, int>, hashFunction> visited;
	visited.emplace(0, 0);

	Knot head;
	Knot tail;
	for (auto it = input.begin(); it != input.end(); ++it)
	{
		const std::pair<char, int>& p = *it;
		char direction = p.first;
		int amount = p.second;

		for (size_t i = 0; i < amount; i++)
		{
			switch (direction)
			{
			case 'R':
				head.right();
				break;
			case 'L':
				head.left();
				break;
			case 'U':
				head.up();
				break;
			case 'D':
				head.down();
				break;
			}
			
			if (Knot(tail.x + 2, tail.y) == head)
				tail.right();
			else if (Knot(tail.x - 2, tail.y) == head)
				tail.left();
			else if (Knot(tail.x, tail.y + 2) == head)
				tail.up();
			else if (Knot(tail.x, tail.y - 2) == head)
				tail.down();
			else if (Knot(tail.x + 2, tail.y - 1) == head || Knot(tail.x + 1, tail.y - 2) == head || Knot(tail.x + 2, tail.y - 2) == head)
				tail.downRight();
			else if (Knot(tail.x + 2, tail.y + 1) == head || Knot(tail.x + 1, tail.y + 2) == head || Knot(tail.x + 2, tail.y + 2) == head)
				tail.upRight();
			else if (Knot(tail.x - 2, tail.y - 1) == head || Knot(tail.x - 1, tail.y - 2) == head || Knot(tail.x - 2, tail.y - 2) == head)
				tail.downLeft();
			else if (Knot(tail.x - 2, tail.y + 1) == head || Knot(tail.x - 1, tail.y + 2) == head || Knot(tail.x - 2, tail.y + 2) == head)
				tail.upLeft();

			visited.emplace(tail.x, tail.y);
		}
	}
	printf("Tail visited: %d", (int)visited.size());
}

void Day09::Part2()
{
	ScopedTimer timer;

	auto input = Utils::StringToPair<char, int>(Utils::ReadInput(INPUT));

	std::unordered_set<std::pair<int, int>, hashFunction> visited;
	visited.emplace(0, 0);

	std::vector<Knot> knots(10);
	Knot& head = knots[0];
	Knot& tail = knots[9];
	for (auto it = input.begin(); it != input.end(); ++it)
	{
		const std::pair<char, int>& p = *it;
		char direction = p.first;
		int amount = p.second;

		for (size_t i = 0; i < amount; i++)
		{
			switch (direction)
			{
			case 'R':
				head.right();
				break;
			case 'L':
				head.left();
				break;
			case 'U':
				head.up();
				break;
			case 'D':
				head.down();
				break;
			}

			for (int i = 1; i < knots.size(); i++)
			{
				Knot& currentKnot = knots[i];
				Knot& previousKnot = knots[i - 1];

				if (Knot(currentKnot.x + 2, currentKnot.y) == previousKnot)
					currentKnot.right();
				else if (Knot(currentKnot.x - 2, currentKnot.y) == previousKnot)
					currentKnot.left();
				else if (Knot(currentKnot.x, currentKnot.y + 2) == previousKnot)
					currentKnot.up();
				else if (Knot(currentKnot.x, currentKnot.y - 2) == previousKnot)
					currentKnot.down();
				else if (Knot(currentKnot.x + 2, currentKnot.y - 1) == previousKnot || Knot(currentKnot.x + 1, currentKnot.y - 2) == previousKnot || Knot(currentKnot.x + 2, currentKnot.y - 2) == previousKnot)
					currentKnot.downRight();
				else if (Knot(currentKnot.x + 2, currentKnot.y + 1) == previousKnot || Knot(currentKnot.x + 1, currentKnot.y + 2) == previousKnot || Knot(currentKnot.x + 2, currentKnot.y + 2) == previousKnot)
					currentKnot.upRight();
				else if (Knot(currentKnot.x - 2, currentKnot.y - 1) == previousKnot || Knot(currentKnot.x - 1, currentKnot.y - 2) == previousKnot || Knot(currentKnot.x - 2, currentKnot.y - 2) == previousKnot)
					currentKnot.downLeft();
				else if (Knot(currentKnot.x - 2, currentKnot.y + 1) == previousKnot || Knot(currentKnot.x - 1, currentKnot.y + 2) == previousKnot || Knot(currentKnot.x - 2, currentKnot.y + 2) == previousKnot)
					currentKnot.upLeft();

				visited.emplace(tail.x, tail.y);
			}
		}
	}
	printf("Tail visited: %d", (int)visited.size());
}