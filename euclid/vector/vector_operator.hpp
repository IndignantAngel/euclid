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
}