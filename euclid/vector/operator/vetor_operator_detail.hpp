#pragma once

namespace euclid
{
	namespace detail
	{
		struct do_operator_tag_simple {};
		struct do_operator_tag_complex {};

		template <typename Expr, typename LExpr, typename RExpr, size_t ... Is>
		auto do_binary_operator_complex(
			vector_expression<LExpr> const& lhs,
			vector_expression<RExpr> const& rhs,
			std::index_sequence<Is...>) noexcept
		{
			using vector_type = vector<typename Expr::value_type, Expr::size(), typename Expr::base_tag>;
			using binary_functor_type = typename Expr::functor_type;
			return vector_type{ binary_functor_type::get<Is>(get_expression(lhs), get_expression(rhs))... };
		}

		template <typename Expr, typename LExpr, typename RExpr>
		auto do_binary_operator(
			vector_expression<LExpr> const& lhs,
			vector_expression<RExpr> const& rhs,
			do_operator_tag_simple) noexcept
		{
			return Expr{ lhs, rhs };
		}

		template <typename Expr, typename LExpr, typename RExpr>
		auto do_binary_operator(
			vector_expression<LExpr> const& lhs,
			vector_expression<RExpr> const& rhs,
			do_operator_tag_complex) noexcept
		{
			return do_binary_operator_complex<Expr>(lhs, rhs, std::make_index_sequence<Expr::size()>{});
		}

		template <typename Expr, typename LExpr, typename RExpr>
		auto do_binary_operator(vector_expression<LExpr> const& lhs, vector_expression<RExpr> const& rhs) noexcept
		{
			// IF	the complexity of either expression is greater than 1, we create a temprory vector instead
			// ELSE	we create the vector_cross expression we want

			return do_binary_operator<Expr>(lhs, rhs, std::conditional_t<
				or <size_greater_than<LExpr::complexity(), 1>, size_greater_than<RExpr::complexity(), 1>>::value,
				do_operator_tag_complex, do_operator_tag_simple>{});
		}
	}
}