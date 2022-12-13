#include "Day11.h"

#define INPUT "Day11/1.IN"

enum OPERATOR { ADD, MULTIPLY };
enum OPERATOR_VALUE { INTEGER, SELF };

struct Item
{
	unsigned long long worryLevel;

	Item(unsigned long long worryLevel)
		:worryLevel(worryLevel)
	{}
};

struct Monkey
{
	unsigned long long itemsInspected = 0;
	std::deque<Item> items;
	OPERATOR op;
	OPERATOR_VALUE opv;
	int opvI;
	int testValue;
	int falseMonkey, trueMonkey;

	void InspectItem()
	{
		itemsInspected++;
	}

	void SetFalseMonley(int falseMonkey)
	{
		this->falseMonkey = falseMonkey;
	}

	void SetTrueMonley(int trueMonkey)
	{
		this->trueMonkey = trueMonkey;
	}

	void SetOperator(OPERATOR op)
	{
		this->op = op;
	}

	void SetOperatorValue(OPERATOR_VALUE opv)
	{
		this->opv = opv;
	}

	void SetTestValue(int testValue)
	{
		this->testValue = testValue;
	}

	void SetOperatorValueI(int opvI)
	{
		this->opvI = opvI;
	}
	
	void GiveItem(Item item)
	{
		items.push_front(item);
	}

	Item GetNextItem()
	{
		Item item = items.back();
		return item;
	}

	void ThrowItem()
	{
		items.pop_back();
	}

	bool PerformTest(unsigned long long worryLevel)
	{
		return (worryLevel % testValue) == 0;
	}

};

void SimulateMonkeys(std::vector<Monkey>& monkeys, int noRounds, int part)
{
	for (size_t i = 0; i < noRounds; i++)
	{
		for (auto& monkey : monkeys)
		{
			for (auto& item : monkey.items)
			{
				monkey.InspectItem();

				unsigned long long worryLevel;
				if (monkey.opv == OPERATOR_VALUE::INTEGER)
				{
					if (monkey.op == OPERATOR::ADD)
						worryLevel = item.worryLevel + monkey.opvI;
					else if (monkey.op == OPERATOR::MULTIPLY)
						worryLevel = item.worryLevel * monkey.opvI;
				}
				else if (monkey.opv == OPERATOR_VALUE::SELF)
				{
					worryLevel = item.worryLevel * item.worryLevel;
				}

				if (part == 1)
					worryLevel /= 3;
				else
					worryLevel = worryLevel % 9699690;

				if (monkey.PerformTest(worryLevel))
					monkeys[monkey.trueMonkey].GiveItem(Item(worryLevel));
				else
					monkeys[monkey.falseMonkey].GiveItem(Item(worryLevel));
				monkey.ThrowItem();
			}
		}
	}
}

std::vector<Monkey> GenerateMonkeys(std::vector<string>& input)
{
	std::vector<Monkey> monkeys;
	int currentLineIndex = 0;
	while (currentLineIndex < input.size())
	{
		Monkey monkey;
		for (size_t i = currentLineIndex; i < currentLineIndex + 5; i++)
		{
			std::string currentLine = input[i + 1];
			if (i % 7 == 0)
			{
				// Setup Items
				auto items = Utils::GetIntegersFromString(currentLine);
				for (const auto& item : items)
					monkey.GiveItem(Item(item));
			}
			else if (i % 7 == 1)
			{
				// Setup operation
				auto value = Utils::GetIntegersFromString(currentLine);
				char op = currentLine[23];
				if (op == '+')
					monkey.SetOperator(OPERATOR::ADD);
				else if (op == '*')
					monkey.SetOperator(OPERATOR::MULTIPLY);
				if (value.size() == 0)
				{
					monkey.SetOperatorValue(OPERATOR_VALUE::SELF);
				}
				else
				{
					monkey.SetOperatorValueI(value[0]);
					monkey.SetOperatorValue(OPERATOR_VALUE::INTEGER);
				}

			}
			else if (i % 7 == 2)
			{
				// Setup test
				auto testValue = Utils::GetIntegersFromString(currentLine);
				monkey.SetTestValue(testValue[0]);
			}
			else if (i % 7 == 3)
			{
				// Setup true monkey
				monkey.SetTrueMonley((int)(currentLine[currentLine.size() - 1] - '0'));
			}
			else if (i % 7 == 4)
			{
				// Setup false monkey
				monkey.SetFalseMonley((int)(currentLine[currentLine.size() - 1] - '0'));
			}
		}
		monkeys.push_back(monkey);
		currentLineIndex += 7;
	}
	return monkeys;
}

void Day11::Part1()
{
	ScopedTimer timer;
	
	auto input = Utils::ReadInput(INPUT);

	std::vector<Monkey> monkeys = GenerateMonkeys(input);
	SimulateMonkeys(monkeys, 20, 1);

	std::vector<int> monkeyInspects;
	for (auto& monkey : monkeys) 
	{
		monkeyInspects.push_back(monkey.itemsInspected);
		printf("Monkey: %lld\n", monkey.itemsInspected);
	}
	sort(monkeyInspects.begin(), monkeyInspects.end(), greater<int>());
	printf("Monkey business: %d", monkeyInspects[0] * monkeyInspects[1]);
}

void Day11::Part2()
{
	ScopedTimer timer;

	auto input = Utils::ReadInput(INPUT);

	std::vector<Monkey> monkeys = GenerateMonkeys(input);
	SimulateMonkeys(monkeys, 10000, 2);

	std::vector<unsigned long long> monkeyInspects;
	for (auto& monkey : monkeys)
	{
		monkeyInspects.push_back(monkey.itemsInspected);
		printf("Monkey: %lld\n", monkey.itemsInspected);
	}
	sort(monkeyInspects.begin(), monkeyInspects.end(), greater<unsigned long long>());
	printf("Monkey business: %lld", monkeyInspects[0] * monkeyInspects[1]);
}