#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_set>

#include "Utils/Timer.h"
#include "Utils/ScopedTimer.h"

#define PI 3.1415926535897932384626433832795

template<typename T>
void printVector(const T& t) {
	std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

class AocDay
{
public:
	AocDay()  { }
	~AocDay() { }

	virtual void part1() = 0;
	virtual void part2() = 0;
};
