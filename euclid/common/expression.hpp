#pragma once

#include <utility>
#include <functional>

namespace euclid
{
	template <typename Expr>
	class base_expression
	{
	public:
		using expression_t = Expr;
		using const_expression_t = std::add_const_t<Expr>;
	protected:
		base_expression() noexcept = default;
	};

	template <typename Expr>
	decltype(auto) get_expression(base_expression<Expr>& expression) noexcept
	{
		return static_cast<Expr&>(expression);
	}

	template <typename Expr>
	decltype(auto) get_expression(base_expression<Expr> const& expression) noexcept
	{
		return static_cast<Expr const&>(expression);
	}

	template <typename Expr>
	class scalar_expression : public base_expression<Expr>
	{
	public:
		static constexpr size_t size() noexcept
		{
			return 1;
		}
	};
}