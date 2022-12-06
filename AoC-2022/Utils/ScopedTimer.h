#pragma once
#include <iostream>

#include "Timer.h"

class ScopedTimer : public Timer
{
public:
	ScopedTimer()
	{
		Reset();
	}

	~ScopedTimer()
	{
		std::cout << "\n" << ElapsedMillis() << "ms\n";
	}

};
