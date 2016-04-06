#pragma once

namespace euclid
{
	// fill
	namespace detail
	{
		struct vector_fill_tag_memset {};
		struct vector_fill_tag_memberwise {};
		struct vector_fill_tag_tuple {};
		struct vector_fill_tag_to_tuple {};

		template <typename Expr, typename Tuple, size_t ... Indices>
		inline void fill_impl_memberwise(vector_expression<Expr>& e, Tuple&& tuple, std::index_sequence<Indices...>) noexcept
		{
			auto swallow = { get_expression(e)[Indices] = std::get<Indices>(std::forward<Tuple>(tuple)) ... };
		}

		template <typename Expr, typename Tuple>
		inline void fill_impl_memberwise(vector_expression<Expr>& e, Tuple&& tuple, vector_fill_tag_tuple) noexcept
		{
			fill_impl_memberwise(e, std::forward<Tuple>(tuple),
				std::make_index_sequence<std::tuple_size<Expr>::value>{});
		}

		template <typename Expr, typename T>
		inline void fill_impl_memberwise(vector_expression<Expr>& e, T&& t, vector_fill_tag_to_tuple) noexcept
		{
			fill_impl_memberwise(e, make_uniform_tuple<std::tuple_size<Expr>::value>(std::forward<T>(t)), vector_fill_tag_tuple{});
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

	template <typename Expr, typename T>
	inline void fill(vector_expression<Expr>& e, T&& t) noexcept
	{
		detail::fill_impl(e, std::forward<T>(t));
	}
	/// fill

	// vector assign
	namespace detail
	{
		struct vector_assign_tag_simple {};
		struct vector_assign_tag_complex {};
		struct vector_assign_tag_memcpy {};
		struct vector_assign_tag_memberwise {};

		template <typename LExpr, typename RExpr>
		inline void assign_impl_memcpy(
			vector_expression<LExpr>& lhs,
			vector_expression<RExpr> const& rhs) noexcept
		{
			constexpr auto size = sizeof(typename LExpr::value_type) * LExpr::size();
			std::memcpy(
				get_expression(lhs).data(),
				get_expression(rhs).data(),
				size);
		}

		template <typename LExpr, typename RExpr, size_t ... Indices>
		inline void assign_impl_memberwise(
			vector_expression<LExpr>& lhs,
			vector_expression<RExpr> const& rhs,
			std::index_sequence<Indices...>) noexcept
		{
			auto swallow = { get_expression(lhs).get<Indices>() = get_expression(rhs).get<Indices>() ... };
		}

		template <typename LExpr, typename RExpr>
		inline void assign_impl_style_select(
			vector_expression<LExpr>& lhs,
			vector_expression<RExpr> const& rhs,
			vector_assign_tag_memcpy) noexcept
		{
			assign_impl_memcpy(lhs, rhs);
		}

		template <typename LExpr, typename RExpr>
		inline void assign_impl_style_select(
			vector_expression<LExpr>& lhs,
			vector_expression<RExpr> const& rhs,
			vector_assign_tag_memberwise) noexcept
		{
			assign_impl_memberwise(lhs, rhs, std::make_index_sequence<LExpr::size()>{});
		}

		template <typename LExpr, typename RExpr>
		inline void assign_impl_complexity(
			vector_expression<LExpr>& lhs,
			vector_expression<RExpr> const& rhs,
			vector_assign_tag_complex) noexcept
		{
			using right_vector_type =
				vector<typename RExpr::value_type, RExpr::size(), typename RExpr::base_tag>;

			// begin another assign routine
			right_vector_type temp = rhs;

			// it is simple now
			assign_impl_complexity(lhs, temp, vector_assign_tag_simple{});
		}

		template <typename LExpr, typename RExpr>
		inline void assign_impl_complexity(
			vector_expression<LExpr>& lhs,
			vector_expression<RExpr> const& rhs,
			vector_assign_tag_simple) noexcept
		{
			assign_impl_style_select(lhs, rhs,
				std::conditional_t<and<
					size_equal<RExpr::complexity(), 0>,
					size_equal<LExpr::complexity(), 0>,
					std::is_same<typename LExpr::value_type, typename RExpr::value_type>
				>::value, vector_assign_tag_memcpy, vector_assign_tag_memberwise>{});
		}

		template <typename LExpr, typename RExpr>
		inline void assign_impl(vector_expression<LExpr>& lhs, vector_expression<RExpr> const& rhs) noexcept
		{
			assign_impl_complexity(lhs, rhs,
				std::conditional_t<size_greater_than<RExpr::complexity(), 1>::value,
					vector_assign_tag_complex, vector_assign_tag_simple>{});
		}
	}

	template<typename LExpr, typename RExpr>
	auto assign(vector_expression<LExpr>& lhs, vector_expression<RExpr> const& rhs) noexcept
		-> std::enable_if_t<size_equal<LExpr::size(), RExpr::size()>::value>
	{
		detail::assign_impl(lhs, rhs);
	}
	/// vector assign
}