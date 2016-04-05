#pragma once

namespace euclid
{
	template <typename Expr>
	class vector_expression : public base_expression<Expr>				// export expression type
	{
	public:
		using base_type = base_expression<Expr>;
		using expression_t = typename base_type::expression_t;
		using const_expression_t = typename base_type::const_expression_t;
		
	public:
		template <size_t ... N>
		auto operator() (vector_placeholder<N> const ...) noexcept
			-> vector_proxy<expression_t, std::index_sequence<N...>>
		{
			return { get_expression(*this) };
		}

		template <size_t ... N>
		auto operator() (vector_placeholder<N> const ...) const noexcept
			-> vector_proxy<const_expression_t, std::index_sequence<N...>>
		{
			return { get_expression(*this) };
		}
	};

	template <typename Expr>
	struct vector_expression_traits
	{
		static constexpr bool value = std::is_base_of<
			vector_expression<Expr>, Expr>::value;

		using base_expression_t = std::conditional_t<
			std::is_const<Expr>::value,
			std::add_const_t<vector_expression<Expr>>,
			vector_expression<Expr>> ;

		using expression_t = Expr;
	};
}