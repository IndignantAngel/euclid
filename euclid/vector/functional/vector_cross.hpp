#pragma once

namespace euclid
{
	/// cross production for vector
	template <typename LExpr, typename RExpr>
	struct vector_cross
	{
	private:
		using first_value_type = typename LExpr::value_type;
		using second_value_type = typename RExpr::value_type;
		static constexpr size_t the_size = LExpr::size();

	public:
		using first_argument_type = LExpr;
		using second_argument_type = RExpr;
		using result_type = typename
			scalar_multiplication<first_value_type, second_value_type>::result_type;

		template <size_t Index>
		static result_type get(first_argument_type const& lhs, second_argument_type const& rhs) noexcept
		{
			constexpr size_t I = size_mod<size_add<Index, 1>::value, the_size>::value;
			constexpr size_t J = size_mod<size_add<Index, 2>::value, the_size>::value;

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