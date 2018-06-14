#pragma once
#include <string>

template<typename T, T min, T max>
class Range // You should re-code and simplify your SRS01 RangeInt, use template
{
private:
	using value_type = T;

public:
	value_type value_;

public:
	Range(const value_type value) : value_{ value }
	{
	}
	
	//operator - member function (implicit conversion, single jump) everything else explicitly 
	operator value_type() const 
	{
		return value_;
	}
};



