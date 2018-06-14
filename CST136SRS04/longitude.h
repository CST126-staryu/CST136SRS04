#pragma once
#include "angle.h"

namespace GPS
{
	class Longitude : public Angle<-180, 180>
	{
	public:
		enum Cardinal { W = -1, E = +1 };

		Longitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second);
	
	private:
		long normalDegree() const override;

		friend bool operator< (const Longitude lhs, const Longitude rhs)
		{
			//compares in order
			//return std::make_tuple(lhs.degree_+360, lhs.minute_, lhs.second_) < std::make_tuple(rhs.degree_+360, lhs.minute_, lhs.second_);
			return lhs.microDegrees() < rhs.microDegrees();
		}
	};
}
