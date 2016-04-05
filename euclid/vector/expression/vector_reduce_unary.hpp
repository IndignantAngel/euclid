#pragma once

namespace euclid
{
	template <typename Expr, typename Func>
	class vector_reduce_unary : public scalar_expression<vector_reduce_unary<Expr, Func>>
	{
		using traits_t = vector_expression_traits<Expr>;
		static_assert(traits_t::value, "Not a valid vector expression!");
	};
}