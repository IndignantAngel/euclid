#pragma once

namespace euclid
{
	struct colume_base {};
	struct row_base {};

	template <size_t N>
	struct vector_placeholder;

	template <typename Expr>
	class vector_expression;

	template <typename Type, size_t N, typename Base = colume_base>
	class vector;

	template <typename Expr, typename Indices>
	class vector_proxy;

	template <typename Expr, template <typename> class Func>
	class vector_unary;

	template <typename LExpr, typename RExpr, template <typename, typename> class Func>
	class vector_binary;

	template <typename Expr, typename T, template <typename> class Func>
	class vector_scalar;

	template <typename Expr, template <typename> class Func>
	class vector_reduce_unary;

	template <typename LExpr, typename RExpr, template <typename, typename> class Func>
	class vector_reduce_binary;
}