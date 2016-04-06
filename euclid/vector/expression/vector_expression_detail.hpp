#pragma once 

namespace euclid
{
	// detail for vector ±¾Îï
	namespace detail
	{
		template <size_t N, typename ... Args>
		using variadic_param_enable_if_t =
			std::enable_if_t<size_equal<N, sizeof...(Args)>::value>;
	}

	// detail for vector proxy
	namespace detail
	{
		// is_index_sequence
		template <typename Indices>
		struct is_index_sequence : std::false_type {};

		template <size_t I>
		struct is_index_sequence<std::index_sequence<I>> : std::true_type {};

		template <size_t M, size_t N, size_t ... Indices>
		struct is_index_sequence<std::index_sequence<M, N, Indices...>>
		{
			static constexpr bool value =
				and< 
					size_equal<size_increment<M>::value, N>,
					is_index_sequence<std::index_sequence<N, Indices...>>
				>::value;
		};
		/// is_index_sequence

		// proxy_lvalue_traits
		template <size_t N, size_t ... Is>
		struct proxy_indices_valid_impl;

		template <size_t N, size_t I>
		struct proxy_indices_valid_impl<N, I>
		{
			static constexpr bool value = size_greater_than<N, I>::value;
		};

		template <size_t N, size_t I, size_t ... Is>
		struct proxy_indices_valid_impl<N, I, Is...>
		{
			static constexpr bool value =
				and<size_greater_than<N, I>, proxy_indices_valid_impl<N, Is...>>::value;
		};

		template <typename Expr, typename Indices>
		struct proxy_indices_valid;

		template <typename Expr, size_t ... Is>
		struct proxy_indices_valid<Expr, std::index_sequence<Is...>>
			: proxy_indices_valid_impl<Expr::size(), Is...> {};

		template <typename Expr, typename Indices>
		struct proxy_lvalue_traits
		{
			static constexpr bool is_contiguous_memory = is_index_sequence<Indices>::value;

			static constexpr size_t complexity =
				std::conditional_t<
					size_equal<Expr::complexity(), 0>::value,
					std::conditional_t<is_contiguous_memory, std::size_const<0>, std::size_const<1>>,
					std::size_const<Expr::complexity()>>::value;

			static constexpr bool is_lvalue = and<size_equal<complexity, 0>, not<std::is_const<Expr>>>::value;
		};
		/// proxy_lvalue_traits
	}
}