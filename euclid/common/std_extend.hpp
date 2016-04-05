#pragma once

namespace std
{
	template <typename T, size_t N, typename Base>
	struct tuple_size<euclid::vector<T, N, Base>>
	{
		static constexpr size_t value =
			euclid::vector<T, N, Base>::size();
	};

	template <typename T, size_t N>
	struct tuple_size<euclid::uniform_tuple<T, N>>
	{
		static constexpr size_t value = N;
	};

	template <size_t I, typename T, size_t N>
	inline auto get(euclid::uniform_tuple<T, N> tuple) noexcept
	{
		return tuple.get();
	}

	template <size_t N>
	using size_const = std::integral_constant<size_t, N>;
}