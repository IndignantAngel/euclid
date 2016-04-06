#pragma once

namespace euclid
{
	template <typename LExpr, typename RExpr, typename Func>
	class vector_reduce_binary : public scalar_expression<vector_reduce_binary<LExpr, RExpr, Func>>
	{
		using left_traits = vector_expression<LExpr>;
		using right_traits = vector_expression<RExpr>;
		static_assert(left_traits::is_valid, "Left expression is not a valid vector expression!");
		static_assert(right_traits::is_valid, "Right expression is not a valid vector expression!");
		static_assert(LExpr::size() == RExpr::size(), "Vector binary size dosen`t match!");
	
	public:
	};
}