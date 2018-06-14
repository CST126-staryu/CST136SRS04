#pragma once
#include "angle.h"

namespace GPS
{
	class Latitude : public Angle<-89, 90>
	{
	public:
		enum Cardinal { S = -1, N = +1 };

		Latitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second) ;
	
	private:
		long normalDegree() const override;

		friend bool operator< (const Latitude lhs, const Latitude rhs)
			{
				//compares in order
				//return std::make_tuple(lhs.degree_+360, lhs.minute_, lhs.second_) < std::make_tuple(rhs.degree_+360, lhs.minute_, lhs.second_);
				return lhs.microDegrees() < rhs.microDegrees();
			}
	};
}
