#include "Core/AocDay.h"

class Day01 : public AocDay
{
public:
	void AocDay::Part1()
	{
		std::string currentLine;
		std::ifstream input("Day01/1.IN");

		std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

		int runningSum = 0;
		while (getline(input, currentLine))
		{
			if (currentLine.empty())
			{
				if (pq.size() < 2 || runningSum > pq.top())
				{
					if (pq.size() > 2)
						pq.pop();
					pq.push(runningSum);
				}
				runningSum = 0;
			}
			else
			{
				runningSum += stoi(currentLine);
			}
		}

		int maxSum = 0;
		int size = pq.size();
		for (size_t i = 0; i < size; i++)
		{
			maxSum += pq.top();
			pq.pop();
		}

		printf("Amount of cal: %i", maxSum);
	}
};