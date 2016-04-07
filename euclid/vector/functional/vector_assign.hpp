#pragma once 

namespace euclid
{
	// vector assign
	namespace detail
	{
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
		inline void assign_impl(vector_expression<LExpr>& lhs, vector_expression<RExpr> const& rhs) noexcept
		{
			assign_impl_style_select(lhs, rhs,
				std::conditional_t<and<
				size_equal<RExpr::complexity(), 0>,
				size_equal<LExpr::complexity(), 0>,
				std::is_same<typename LExpr::value_type, typename RExpr::value_type>
				>::value, vector_assign_tag_memcpy, vector_assign_tag_memberwise>{});
		}
	}

	/// vector assign
	template<typename LExpr, typename RExpr>
	auto assign(vector_expression<LExpr>& lhs, vector_expression<RExpr> const& rhs) noexcept
		-> std::enable_if_t<size_equal<LExpr::size(), RExpr::size()>::value>
	{
		detail::assign_impl(lhs, rhs);
	}
}