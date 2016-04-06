#pragma once

namespace euclid
{
	template <typename Expr, typename Func>
	class vector_unary : public vector_expression<vector_unary<Expr, Func>>
	{
		using traits_t = vector_expression_traits<Expr>;
		static_assert(traits_t::is_valid, "Not a valid vector expression!");
	
	public:
		using base_type = vector_expression<vector_unary<Expr, Func>>;
	};
}