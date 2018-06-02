#pragma once
#include <string>

template<typename T, T min, T max>
class Range // You should re-code and simplify your SRS01 RangeInt
{
private:
	using value_type = T;

	value_type value_;

public:
	Range(const value_type value);
};

