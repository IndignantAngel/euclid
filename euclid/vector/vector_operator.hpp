#pragma once

namespace euclid
{
	template <typename Expr>
	auto operator+ (vector_expression<Expr> const& e) noexcept
	{
		static_assert(false, "");
		return false;
	}

	template <typename Expr>
	auto operator- (vector_expression<Expr> const& e) noexcept
	{
		static_assert(false, "");
		return false;
	}

	template <typename Expr>
	auto abs(vector_expression<Expr> const& e) noexcept
	{
		static_assert(false, "");
		return false;
	}

	template <typename Expr>
	auto square(vector_expression<Expr> const& e) noexcept
	{
		static_assert(false, "");
		return false;
	}

	namespace detail
	{

	}

	template <typename LExpr, typename RExpr>
	auto cross(vector_expression<LExpr> const& lhs, vector_expression<RExpr> const& rhs) noexcept
	{
		static_assert(size_equal<LExpr::size(), 3>::value, "Cross production is only defined with 3-dimensional vectors!");
		using result_type = vector_binary<LExpr, RExpr, vector_cross>;

		return result_type( lhs, rhs );
	}
}