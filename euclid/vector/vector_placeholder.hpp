#pragma once 

namespace euclid
{
	template <size_t N>
	struct vector_placeholder : std::integral_constant<size_t, N> {};

	namespace placehodler
	{
		constexpr vector_placeholder<0> _1;
		constexpr vector_placeholder<1> _2;
		constexpr vector_placeholder<2> _3;
		constexpr vector_placeholder<3> _4;

		constexpr vector_placeholder<0> _r;
		constexpr vector_placeholder<1> _g;
		constexpr vector_placeholder<2> _b;
		constexpr vector_placeholder<3> _a;

		constexpr vector_placeholder<0> _x;
		constexpr vector_placeholder<1> _y;
		constexpr vector_placeholder<2> _z;
		constexpr vector_placeholder<3> _w;
	}
}