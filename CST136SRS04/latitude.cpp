#include "stdafx.h"
#include "latitude.h"


GPS::Latitude::Latitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second):
	Angle<-89, 90>{ cardinal * degree, minute, second }
{
}

long GPS::Latitude::normalDegree() const
{
	//auto not used intentionally, this is a conversion.
	auto const degree{ degree_ };
	return degree;
}
