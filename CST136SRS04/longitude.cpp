#include "stdafx.h"
#include "longitude.h"

GPS::Longitude::Longitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second) :
	Angle<-180, 180>{ cardinal * degree, minute, second }
{
}

long GPS::Longitude::normalDegree() const
{
	auto result{ static_cast<long>(degree_) }; // static_cast used to be explicit about the conversion.

	if (degree_ < 0)
	{
		result += 360;
	}
	return result;
}