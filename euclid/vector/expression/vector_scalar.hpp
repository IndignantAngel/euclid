#pragma once

namespace euclid
{
	template <typename Expr, typename T, typename Func>
	class vector_scalar : public vector_expression<vector_scalar<Expr, T, Func>>
	{
		using traits_t = vector_expression_traits<Expr>;
		static_assert(traits_t::is_valid, "Not a valid vector expression!");
	};
}