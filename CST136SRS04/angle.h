#pragma once
#include "range.h"

namespace GPS
{
	template<int min, int max>
	class Angle;
	
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

	protected:
		const degree_type degree_;
	private:
		const minute_type minute_;
		const second_type second_;

		virtual long normalDegree() const = 0;
		
	protected:
		long microDegrees() const
		{
			auto const degreeFinal{ normalDegree() };
			
			static_assert(std::numeric_limits<long>::max() > 360'000'000);

			auto const result{ 1'000'000L * degreeFinal + 1'000'000L * minute_ / 60 + 1'000'000L * second_ / (60 * 60) };
			
			return result;
		}

	public:
		double regular_degree_value() const
		{
			auto const result{ 1.0 * degree_ + minute_ / 60 + second_ / (60 * 60) };
			return result;
		}

	public:
		Angle(const degree_type degree, const minute_type minute, const second_type second) : degree_{ degree }, minute_{ minute }, second_{ second }
		{
		}
	};
}
