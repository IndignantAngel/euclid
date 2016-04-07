#pragma once

// fill
namespace euclid
{
	namespace detail
	{
		struct vector_fill_tag_memset {};
		struct vector_fill_tag_memberwise {};
		struct vector_fill_tag_tuple {};
		struct vector_fill_tag_to_tuple {};

		template <typename Expr, typename Tuple, size_t ... Indices>
		inline void fill_impl_memberwise(vector_expression<Expr>& e, Tuple&& tuple, std::index_sequence<Indices...>) noexcept
		{
			auto swallow = { get_expression(e).get<Indices>() = std::get<Indices>(std::forward<Tuple>(tuple)) ... };
		}

		template <typename Expr, typename Tuple>
		inline void fill_impl_memberwise(vector_expression<Expr>& e, Tuple&& tuple, vector_fill_tag_tuple) noexcept
		{
			fill_impl_memberwise(e, std::forward<Tuple>(tuple),
				std::make_index_sequence<std::tuple_size<vector_expression<Expr>>::value>{});
		}

		template <typename Expr, typename T>
		inline void fill_impl_memberwise(vector_expression<Expr>& e, T&& t, vector_fill_tag_to_tuple) noexcept
		{
			fill_impl_memberwise(e, make_uniform_tuple<std::tuple_size<vector_expression<Expr>>::value>(std::forward<T>(t)), vector_fill_tag_tuple{});
		}

		template <typename Expr, typename T>
		inline void fill_impl(vector_expression<Expr>& e, T&& t, vector_fill_tag_memberwise) noexcept
		{
			using type = std::remove_reference_t<std::remove_cv_t<T>>;

			// member wise assign
			fill_impl_memberwise(e, std::forward<T>(t),
				std::conditional_t<is_numeric<type>::value,
				vector_fill_tag_to_tuple, vector_fill_tag_tuple>{});
		}

		template <typename Expr>
		inline void fill_impl(vector_expression<Expr>& e, uint8_t value, vector_fill_tag_memset) noexcept
		{
			// for signed char type, memory set directly
			std::memset(get_expression(e).data(), value, cont.size());
		}

		template <typename Expr>
		inline void fill_impl(vector_expression<Expr>& e, int8_t value, vector_fill_tag_memset) noexcept
		{
			// for unsigned char type, memory set directlty
			std::memset(get_expression(e).data(), value, cont.size());
		}

		template <typename Expr, typename T>
		inline void fill_impl(vector_expression<Expr>& e, T&& t) noexcept
		{
			using type = std::remove_cv_t<T>;

			fill_impl(e, std::forward<T>(t), std::conditional_t<
				and<
				or <std::is_same<type, uint8_t>, std::is_same<type, int8_t>>,
				std::is_same<type, typename Expr::value_type>
				>::value,
				vector_fill_tag_memset, vector_fill_tag_memberwise> {}
			);
		}
	}

	/// vector fill
	template <typename Expr, typename T>
	inline void fill(vector_expression<Expr>& e, T&& t) noexcept
	{
		detail::fill_impl(e, std::forward<T>(t));
	}
}