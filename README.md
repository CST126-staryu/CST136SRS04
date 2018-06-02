# CST136SRS04
Island Hopping

Project Name: Atoll

Purpose:

- Learn to use the C++ standard library algorithms
- Learn to use the C++ standard library containers

The navigation of the Pacific is one of the greatest explorations humans have ever achieved. Some say it was as bold as our exploration of space. 

The ancient explorers used the stars, birds, and even the ocean swells to determine where they could find land. 

Today we use GPS and detailed maps find our way. 

Your task is to navigate a route to Hawaii, making stops at every location along the way.

Below is a navigation chart you are to use. Each entry contains an island and its coordinates. 

| Island Name      | Lat Deg | Lat Min | Lat Sec | N/S | Lng Deg | Lng Min | Lng Sec | E/W | 
| ---------------- | ------- | ------- | ------- | --- | ------- | ------- | ------- | --- |
| Faichuk Islands  |       7 |      21 |       8 |   N |     151 |      36 |      30 |   E |
| Hawaii           |      21 |      18 |      41 |   N |     157 |      47 |      47 |   W |
| Mariana Islands  |      17 |       0 |       0 |   N |     146 |       0 |       0 |   E |
| Johnston Atoll   |      16 |      44 |      13 |   N |     169 |      31 |      26 |   W |
| Kosrae           |       5 |      19 |       0 |   N |     162 |      59 |       0 |   E |
| Falalop          |      10 |       1 |      14 |   N |     139 |      47 |      23 |   E |
| Guam             |      13 |      30 |       0 |   N |     144 |      48 |       0 |   E |
| Pohnpei          |       6 |      51 |       0 |   N |     158 |      13 |       0 |   E |
| Marshall Islands |       7 |       7 |       0 |   N |     171 |       4 |       0 |   E |
| Yap              |       9 |      32 |       0 |   N |     138 |       7 |       0 |   E |
| Wake Island      |      19 |      17 |      43 |   N |     166 |      37 |      52 |   E |
| New Zealand      |      41 |      17 |       0 |   S |     174 |      27 |       0 |   E |

Use standard organization for your code. Templates and declarations  in .h files, C++ implementations in .cpp files. File names are lower case with the same name as the class. Place your GPS related classes in a GPS namespace.

Use the following code to get yourself started. This code is not complete, it is only a rough outline of what I'm looking to see. 
```
template<typename T, T min, T max>
class Range // You should re-code and simplify your SRS01 RangeInt
{
private:
	using value_type = T;

	value_type value_;

public:
	Range(const value_type value);
};

namespace GPS
{
	template<int min, int max>
	class Angle
	{
		static_assert(min < max);

	private:
		using base_degree_type = int;
		using base_minute_type = unsigned;
		using base_second_type = unsigned;

	protected:
		using degree_type = Range<base_degree_type, min, max>;
		using minute_type = Range<base_minute_type, 0, 60>;
		using second_type = Range<base_second_type, 0, 60>;

	private:
		const degree_type degree_;
		const minute_type minute_;
		const second_type second_;

	public:
		Angle(const degree_type degree, const minute_type minute, const second_type second);
	};
}

namespace GPS
{
	class Latitude: public Angle<-89, 90>
	{
	public:
		enum class Cardinal { S = -1, N = +1 };

		Latitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second);
	};
}

namespace GPS
{
	class Longitude : public Angle<-180, 180>
	{
	public:
		enum class Cardinal { W = -1, E = +1 };

		Longitude(const Cardinal cardinal, const degree_type degree, const minute_type minute, const second_type second);
	};
}

namespace GPS
{
	class Location
	{
	private:
		const std::string name_;
		const Latitude latitude_;
		const Longitude longitude_;

	public:
		Location(const std::string name, const Latitude latitude, const Longitude longitude);
	};
}
```

Initialize a std::array using the above table:

```
	std::array<GPS::Location, 12> island
	{
		GPS::Location{ "Faichuk Islands"s, GPS::Latitude{ GPS::Latitude::Cardinal::N, 7, 21, 8 }, GPS::Longitude{ GPS::Longitude::Cardinal::E, 151, 36, 30 } } 
    /// ... In order as shown in the above table....
	};
```

Calculate the distance travelled as you hop from island to island. 

For each hop, follow a [Great Circle](https://en.wikipedia.org/wiki/Great-circle_distance). Approximated using the [Haversine Formula](https://en.wikipedia.org/wiki/Haversine_formula) to calculate the Kilometers between the islands. Assume the Earth's radius is: 6378_km. 

You must take 2 routes. The first is to travel from South to North, in order. The second is to travel from West to East in order. 

Record the distance travelled between each pair of locations in their order. South to North and West to East. 

Use 3 different data structures for the data to solve the distances. std::forward_list, std::vector, and std::map. 

This is a total of 6 combinations of calculations but you can only enter the data once into your program as a std::array. 

Record the distances in order of the destination Island Name distance and sum the total distance travelled for that route. Do NOT sum the distances by looping, you must use an algorithm. 

## For those students wishing an extra challenge:

This is only available to students who accurately complete all aspects of this assignment on time and want to do extra work. 

Measure the time each calculation takes to determine which data structure and algorithm does the sorting and summation calculation the fastest. 

The student with fastest release version with an accurate calculations that fully meets the specification win. The winner will recieve an SRS forgiveness (and a Smartie). 

You are allowed to do any calculations at compile time you wish but you may not hand calculate anything. 

Turn this in as a second SRS by copying your original SRS and modifying it. 
