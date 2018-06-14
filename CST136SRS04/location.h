#pragma once
#include <string>
#include "latitude.h"
#include "longitude.h"

namespace GPS
{
	class Longitude;

	class Location
	{
	private:
		const std::string name_;
		const Latitude latitude_;
		const Longitude longitude_;

	public:
		Location(const std::string name, const Latitude latitude, const Longitude longitude);
		Latitude get_lat() const;
		Longitude get_lon() const; 
		
	};
}
