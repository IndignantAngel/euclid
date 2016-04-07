#pragma once 

namespace euclid
{
	/************* vector unary functor **************/
	/// vector_unary_functor
	template <typename Expr, template <typename> class ScalarUnary>
	struct vector_unary_functor
	{
		using scalar_unary_t = ScalarUnary<typename Expr::value_type>;
		using argument_type = Expr;
		using result_type = typename scalar_unary_t::result_type;

		template <size_t Index>
		static result_type get(argument_type const& e) noexcept
		{
			return scalar_unary_t{}(e.get<Index>());
		}

		result_type operator() (argument_type const& e, size_t index) const noexcept
		{
			return scalar_unary_t{}(e(index));
		}
	};

	/// vector_positive
	template <typename Expr>
	using vector_positive = vector_unary_functor<Expr, scalar_positive>;

	/// vector_negative
	template <typename Expr>
	using vector_negative = vector_unary_functor<Expr, scalar_negative>;

	/// vector_square
	template <typename Expr>
	using vector_square = vector_unary_functor<Expr, scalar_square>;

	/// vector inverse
	template <typename Expr>
	using vector_inverse = vector_unary_functor<Expr, scalar_inverse>;

	/************* vector binary functor **************/
	/// vector_binary_function
	template <typename LExpr, typename RExpr, template <typename, typename> class ScalarBinary>
	struct vector_binary_functor
	{
		using scalar_binary_t = ScalarBinary<typename LExpr::value_type, typename RExpr::value_type>;
		using first_argument_type = LExpr;
		using second_argument_type = RExpr;
		using result_type = typename scalar_binary_t::result_type;

		template <size_t Index>
		static result_type get(first_argument_type const& lhs, second_argument_type const& rhs) noexcept
		{
			return scalar_binary_t{}(lhs.get<Index>(), rhs.get<Index>());
		}

		result_type operator() (first_argument_type const& lhs, second_argument_type const& rhs, size_t index) const noexcept
		{
			return scalar_binary_t{}(lhs(index), rhs(index));
		}

		static constexpr size_t complexity() noexcept
		{
			return 1;
		}
	};

	/// vector_addition
	template <typename LExpr, typename RExpr>
	using vector_addition = vector_binary_functor<LExpr, RExpr, scalar_addition>;

	/// vector_subtraction
	template <typename LExpr, typename RExpr>
	using vector_subtraction = vector_binary_functor<LExpr, RExpr, scalar_subtraction>;

	/// vector_multiplication
	template <typename LExpr, typename RExpr>
	using vector_multiplication = vector_binary_functor<LExpr, RExpr, scalar_multiplication>;
}