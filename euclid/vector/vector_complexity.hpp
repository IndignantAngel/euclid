#pragma once

namespace euclid
{
	namespace detail
	{
		template <typename Expr>
		constexpr size_t get_vector_complexity() noexcept
		{
			return select<std::greater, size_t>(1, vector_complexity<Expr>::complexity());
		}

		template <typename Expr>
		struct vector_complexity_default_unary
		{	
			static constexpr size_t complexity() noexcept
			{
				return get_vector_complexity<Expr>();
			}
		};

		template <typename LExpr, typename RExpr>
		struct vector_complexity_default_binary
		{
			static constexpr size_t complexity() noexcept
			{
				return calculate<std::multiplies, size_t>(
					detail::get_vector_complexity<LExpr>(),
					detail::get_vector_complexity<RExpr>());
			}
		};
	}
}