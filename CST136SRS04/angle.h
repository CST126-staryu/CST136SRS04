#pragma once
#include "range.h"

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
