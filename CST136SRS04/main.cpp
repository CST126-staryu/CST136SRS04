// CST136SRS04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <array>
#include <numeric>
#include <map>
#include <vector>
#include <functional>
#include <algorithm>
#include "longitude.h"
#include "location.h"
#include <forward_list>


double haversine(const double lat_1_deg, const double lon_1_deg, const double lat_2_deg, const double lon_2_deg)
{
	const double pi{ 3.14 };
	// Pulled from: https://github.com/stuartthompson/Haversine/blob/master/haversine.cpp
	// Convert coordinates to radians (rad = deg * (pi / 2))
	double lat_1_rad, lon_1_rad, lat_2_rad, lon_2_rad;
	lat_1_rad = lat_1_deg * (pi / 180);
	lon_1_rad = lon_1_deg * (pi / 180);
	lat_2_rad = lat_2_deg * (pi / 180);
	lon_2_rad = lon_2_deg * (pi / 180);

	// Determine latitude and longitude deltas
	double delta_lat, delta_lon;
	delta_lat = lat_1_rad - lat_2_rad;
	delta_lon = lon_1_rad - lon_2_rad;

	// Calculate sin^2 (delta / 2) for both lat and long
	const auto lat_temp = sin(delta_lat / 2);
	const auto lon_temp = sin(delta_lon / 2);
	double sdlat = lat_temp * lat_temp;
	double sdlon = lon_temp * lon_temp;

	// Radius of the Earth (approximate)
	const double radius_earth_km = 6378;

	// http://en.wikipedia/org/wiki/Haversine_formula
	// d=2r*asin(sqrt(sin^2((lat1-lat2)/2)+cos(l1)cos(l2)sin^2((lon2-lon1)/2)))
	//  if t = sqrt(sin^2((lat1-lat2)/2)+cos(l1)cos(l2)sin^2((lon2-lon1)/2)
	//  -> d = 2 * radius_earth * asin (t)	
	const auto t = sqrt(sdlat + (cos(lat_1_rad) * cos(lat_2_rad) * sdlon));
	const auto distance_km = 2 * radius_earth_km * asin(t);
	return distance_km;
}

int main()
{ 
	using namespace std::literals::string_literals;

	std::array<GPS::Location, 12> island
	{
	GPS::Location{ "Faichuk Islands"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 7, 21, 8 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 151, 36, 30 } },
	GPS::Location{ "Hawaii"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 21, 18, 41 }, GPS::Longitude{ GPS::Longitude::Cardinal::W, 157, 47, 47 } },
	GPS::Location{ "Mariana Islands"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 17, 0, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 146, 0, 0 } },
	GPS::Location{ "Johnston Atoll"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 16, 44, 13 }, GPS::Longitude{ GPS::Longitude::Cardinal::W, 169, 31, 26 } },
	GPS::Location{ "Kosrae"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 5, 19, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 162, 59, 0 } },
	GPS::Location{ "Falalop"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 10, 1, 14 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 139, 47, 23 } },
	GPS::Location{ "Guam"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 13, 30, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 144, 48, 0 } },
	GPS::Location{ "Pohnpei"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 6, 51, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 158, 13, 0 } },
	GPS::Location{ "Marshall Islands"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 7, 7, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 171, 4, 0 } },
	GPS::Location{ "Yap"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 9, 32, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 138, 7, 0 } },
	GPS::Location{ "Wake Island"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 19, 17, 43 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 166, 37, 52 } },
	GPS::Location{ "New Zealand"s, GPS::Latitude{ GPS::Latitude::Cardinal::S, 41, 17, 0 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 174, 27, 0 } },
	};

	{ // S to N - map
		std::map<GPS::Latitude, GPS::Location> south_to_north_map;
		for (const auto& record : island)
		{
			// Insert record into south_to_north_map
			auto current_island{ std::make_pair(record.get_lat(), record) };
			south_to_north_map.insert(current_island);
		}

		const auto* previous_island = &south_to_north_map.cbegin()->second;

		std::vector<double> hop_distance;

		for (const auto& record : south_to_north_map)
		{
			// Insert record into south_to_north_map
			const auto& current_island{ record.second };
			// Calculate distance between previous and current island
			const auto distance{ haversine(
				previous_island->get_lat().regular_degree_value(),
				previous_island->get_lon().regular_degree_value(),
				current_island.get_lat().regular_degree_value(),
				current_island.get_lon().regular_degree_value()) };
			// Add result to vector
			hop_distance.emplace_back(distance);
			previous_island = &current_island;
		}
		auto total_distance{ std::accumulate(hop_distance.cbegin(), hop_distance.cend(), 0.0) };
	}

	{ // W to E - map
		std::map<GPS::Longitude, GPS::Location> west_to_east_map;
		for (const auto& record : island)
		{
			// Insert record into south_to_north_map
			auto current_island{ std::make_pair(record.get_lon(), record) };
			west_to_east_map.insert(current_island);
		}

		const auto* previous_island = &west_to_east_map.cbegin()->second;

		std::vector<double> hop_distance;

		for (const auto& record : west_to_east_map)
		{
			// Insert record into south_to_north_map
			const auto& current_island{ record.second };
			// Calculate distance between previous and current island
			const auto distance{ haversine(
				previous_island->get_lat().regular_degree_value(),
				previous_island->get_lon().regular_degree_value(),
				current_island.get_lat().regular_degree_value(),
				current_island.get_lon().regular_degree_value()) };
			// Add result to vector
			hop_distance.emplace_back(distance);
			previous_island = &current_island;
		}
		auto total_distance{ std::accumulate(hop_distance.cbegin(), hop_distance.cend(), 0.0) };
	}

	{ // S to N Vector
		std::vector<std::reference_wrapper<const GPS::Location>> south_to_north_vector(island.cbegin(), island.cend());
		std::sort(south_to_north_vector.begin(), south_to_north_vector.end(), [](const GPS::Location lhs, const GPS::Location rhs)
		{
			const auto result{ lhs.get_lat() < rhs.get_lat() };
			return result;
		});
		
		auto previous_island{ *south_to_north_vector.cbegin() };
		
		std::vector<double> hop_distance;

		for (const auto& current_island : south_to_north_vector)
		{
			// Calculate distance between previous and current island
			const auto distance{ haversine(
				previous_island.get().get_lat().regular_degree_value(),
				previous_island.get().get_lon().regular_degree_value(),
				current_island.get().get_lat().regular_degree_value(),
				current_island.get().get_lon().regular_degree_value()) };
			// Add result to vector
			hop_distance.emplace_back(distance);
			previous_island = current_island;
		}
		auto total_distance{ std::accumulate(hop_distance.cbegin(), hop_distance.cend(), 0.0) };
	}

	//{ // W to E Vector
	//	std::vector<std::reference_wrapper<const GPS::Location>> west_to_east_vector(island.cbegin(), island.cend());
	//	std::sort(west_to_east_vector.begin(), west_to_east_vector.end(), [](const GPS::Location lhs, const GPS::Location rhs)
	//	{
	//		const auto result{ lhs.get_lat() < rhs.get_lat() };
	//		return result;
	//	});

	//	auto previous_island{ *west_to_east_vector.cbegin() };

	//	std::vector<double> hop_distance;

	//	for (const auto& current_island : west_to_east_vector)
	//	{
	//		// Calculate distance between previous and current island
	//		const auto distance{ haversine(
	//			previous_island.get().get_lat().regular_degree_value(),
	//			previous_island.get().get_lon().regular_degree_value(),
	//			current_island.get().get_lat().regular_degree_value(),
	//			current_island.get().get_lon().regular_degree_value()) };
	//		// Add result to vector
	//		hop_distance.emplace_back(distance);
	//		previous_island = current_island;
	//	}
	//	auto total_distance{ std::accumulate(hop_distance.cbegin(), hop_distance.cend(), 0.0) };
	//}
	{ // S to N - Linked List
		std::forward_list<GPS::Location> south_to_north_linked_list(island.cbegin(), island.cend());
		south_to_north_linked_list.sort([](const GPS::Location lhs, const GPS::Location rhs)
		{
			const auto result{ lhs.get_lat() < rhs.get_lat() };
			return result;
		});
		//auto previous_island{ *south_to_north_linked_list.cbegin() };
		auto previous_island = &*south_to_north_linked_list.cbegin();

		std::vector<double> hop_distance;

		for (const auto& current_island : south_to_north_linked_list)
		{
			// Calculate distance between previous and current island
			const auto distance{ haversine(
				previous_island->get_lat().regular_degree_value(),
				previous_island->get_lon().regular_degree_value(),
				current_island.get_lat().regular_degree_value(),
				current_island.get_lon().regular_degree_value()) };
			// Add result to vector
			hop_distance.emplace_back(distance);
			previous_island = &current_island;
		}
		auto total_distance{ std::accumulate(hop_distance.cbegin(), hop_distance.cend(), 0.0) };
	}
	
	//{ // W to E - Linked List
	//	std::forward_list<GPS::Location> west_to_east_linked_list(island.cbegin(), island.cend());
	//	west_to_east_linked_list.sort([](const GPS::Location lhs, const GPS::Location rhs)
	//	{
	//		const auto result{ lhs.get_lat() < rhs.get_lat() };
	//		return result;
	//	});
	//	auto previous_island = &*west_to_east_linked_list.cbegin();

	//	std::vector<double> hop_distance;

	//	for (const auto& current_island : west_to_east_linked_list)
	//	{
	//		// Calculate distance between previous and current island
	//		const auto distance{ haversine(
	//			previous_island->get_lat().regular_degree_value(),
	//			previous_island->get_lon().regular_degree_value(),
	//			current_island.get_lat().regular_degree_value(),
	//			current_island.get_lon().regular_degree_value()) };
	//		// Add result to vector
	//		hop_distance.emplace_back(distance);
	//		previous_island = &current_island;
	//	}
	//	auto total_distance{ std::accumulate(hop_distance.cbegin(), hop_distance.cend(), 0.0) };
	return 0;
}

