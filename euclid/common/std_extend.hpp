#pragma once

namespace std
{
	//template <typename T, size_t N, typename Base>
	//struct tuple_size<euclid::vector<T, N, Base>>
	//{
	//	static constexpr size_t value =
	//		euclid::vector<T, N, Base>::size();
	//};

	template <typename Expr>
	struct tuple_size<euclid::vector_expression<Expr>>
	{
		static constexpr size_t value = Expr::size();
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

	namespace euclid_detail
	{
		template <size_t I, size_t ... Indices>
		struct get_index_sequence;
	
		template <size_t I, size_t ... Indices>
		struct get_index_sequence<0, I, Indices...>
		{
			static constexpr auto value = I;
		};
	
		template <size_t I, size_t J, size_t ... Indices>
		struct get_index_sequence<I, J, Indices...>
		{
			static constexpr auto value = get_index_sequence<
				euclid::size_decrement<I>::value, Indices...>::value;
		};
	}
	
	template <size_t I, size_t ... Indices>
	inline constexpr auto get(std::index_sequence<Indices...>) noexcept
	{
		return euclid_detail::get_index_sequence<I, Indices...>::value;
	}

	template <size_t N>
	using size_const = std::integral_constant<size_t, N>;
}