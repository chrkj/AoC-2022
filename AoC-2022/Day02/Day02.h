#include "Core/AocDay.h"
// A = Rock
// B = Paper
// C = Scissors
// 
// X = Rock
// Y = Paper
// Z = Scissors

class Day02 : public AocDay 
{
public:
	int getScore(char myPick, char opponentPick)
	{
		int score = 0;
		switch (myPick)
		{
		case 'X':
			score += 1;
			if (opponentPick == 'A')
				score += 3;
			else if (opponentPick == 'C')
				score += 6;
			break;

		case 'Y':
			score += 2;
			if (opponentPick == 'B')
				score += 3;
			else if (opponentPick == 'A')
				score += 6;
			break;

		case 'Z':
			score += 3;
			if (opponentPick == 'C')
				score += 3;
			else if (opponentPick == 'B')
				score += 6;
			break;

		default:
			break;
		}
		return score;
	}

	void AocDay::part1()
	{
		std::string currentLine;
		std::ifstream input("Day02/1.IN");

		char myPick;
		char opponentPick;
		int totalScore = 0;
		while (getline(input, currentLine))
		{
			myPick = currentLine[2];
			opponentPick = currentLine[0];
			totalScore += getScore(myPick, opponentPick);
		}
		std::cout << totalScore << "\n";
	}

	// X = Lose
	// Y = Draw
	// Z = Win
	char getPick(char opponentPick, char desiredFallout)
	{
		char pick;
		switch (desiredFallout)
		{
		case 'X':
			if (opponentPick == 'A')
				pick = 'Z';
			if (opponentPick == 'B')
				pick = 'X';
			if (opponentPick == 'C')
				pick = 'Y';
			break;

		case 'Y':
			if (opponentPick == 'A')
				pick = 'X';
			if (opponentPick == 'B')
				pick = 'Y';
			if (opponentPick == 'C')
				pick = 'Z';
			break;

		case 'Z':
			if (opponentPick == 'A')
				pick = 'Y';
			if (opponentPick == 'B')
				pick = 'Z';
			if (opponentPick == 'C')
				pick = 'X';
			break;
		}
		return pick;
	}

	void AocDay::part2()
	{
		std::string currentLine;
		std::ifstream input("Day02/1.IN");

		char myPick;
		char opponentPick;
		int totalScore = 0;
		while (getline(input, currentLine))
		{
			opponentPick = currentLine[0];
			myPick = getPick(opponentPick, currentLine[2]);

			totalScore += getScore(myPick, opponentPick);
		}
		std::cout << totalScore << "\n";

	}
};