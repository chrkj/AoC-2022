#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_set>
#include <map>
#include <charconv>

#include "Utils/Utils.h"
#include "Utils/Timer.h"
#include "Utils/ScopedTimer.h"

#define PI 3.1415926535897932384626433832795

class AocDay
{
public:
	AocDay()  { }
	~AocDay() { }

	virtual void Part1() = 0;
	virtual void Part2() = 0;
};
