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

	template <typename LExpr, typename RExpr>
	auto cross(vector_expression<LExpr> const& lhs, vector_expression<RExpr> const& rhs) noexcept
	{
		static_assert(size_equal<LExpr::size(), 3>::value, "Cross production is only defined with 3-dimensional vectors!");
		using expression_t = vector_binary<LExpr, RExpr, vector_cross>;
		return detail::do_binary_operator<expression_t>(lhs, rhs);
	}

	template <typename Expr>
	auto norm_1(vector_expression<Expr> const& lhs) noexcept
	{
		return 0;
	}

	template <typename Expr>
	auto norm_2(vector_expression<Expr> const& lhs) noexcept
	{
		return 0;
	}

	template <typename Expr>
	auto norm_inf(vector_expression<Expr> const& lhs) noexcept
	{
		return 0;
	}
}