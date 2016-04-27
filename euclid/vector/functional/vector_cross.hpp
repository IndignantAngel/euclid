#pragma once

namespace euclid
{
	/// cross production for vector
	template <typename LExpr, typename RExpr>
	struct vector_cross
	{
		using first_value_type = typename LExpr::value_type;
		using second_value_type = typename RExpr::value_type;
		static constexpr size_t the_size = 3;

	public:
		using first_argument_type = LExpr;
		using second_argument_type = RExpr;
		using result_type = typename
			scalar_multiplication<first_value_type, second_value_type>::result_type;

		using value_type = result_type;
		using reference = result_type;
		using const_reference = result_type;
		using pointer = result_type*;
		using const_pointer = result_type const*;

		template <size_t Index>
		static result_type get(first_argument_type const& lhs, second_argument_type const& rhs) noexcept
		{
			constexpr size_t I = (Index + 1) % the_size;
			constexpr size_t J = (Index + 2) % the_size;
			return lhs.get<I>() * rhs.get<J>() - lhs.get<J>() * rhs.get<I>();
		}

		// this kind of access is not effective
		result_type operator() (first_argument_type const& lhs, second_argument_type const& rhs, size_t index) const noexcept
		{
			size_t i = (Index + 1) % the_size;
			size_t j = (Index + 2) % the_size;
			return lhs(i) * rhs(j) - lhs(j) * rhs(i);
		}

		static constexpr size_t complexity() noexcept
		{
			return 2;
		}
	};
}