#pragma once

namespace euclid
{
	template <typename LExpr, typename RExpr, template <typename, typename> class Func>
	class vector_binary : public vector_expression<vector_binary<LExpr, RExpr, Func>>
	{
		using left_traits = vector_expression_traits<LExpr>;
		using right_traits = vector_expression_traits<RExpr>;
		static_assert(left_traits::is_valid, "Left expression is not a valid vector expression!");
		static_assert(right_traits::is_valid, "Right expression is not a valid vector expression!");
		static_assert(LExpr::size() == RExpr::size(), "Vector binary size dosen`t match!");
	
	public:
		using base_type = vector_expression<vector_binary<LExpr, RExpr, Func>>;
		using lsub_base_expression_t = typename left_traits::base_expression_t;
		using rsub_base_expression_t = typename right_traits::base_expression_t;
		using lsub_expression_t = typename left_traits::expression_t;
		using rsub_expression_t = typename right_traits::expression_t;

		using functor_type = Func<lsub_expression_t, rsub_expression_t>;
		using value_type = typename functor_type::result_type;
		using base_tag = typename lsub_expression_t::base_tag;

	public:
		vector_binary(
			lsub_base_expression_t const& lhs,
			rsub_base_expression_t const& rhs) noexcept
			: lhs_(lhs), rhs_(rhs)
		{

		}

		static constexpr size_t size() noexcept
		{
			return lsub_expression_t::size();
		}

		static constexpr size_t complexity() noexcept
		{
			//return 
			//	select<std::greater>(
			//		select<std::greater>(
			//			lsub_expression_t::complexity(),
			//			size_multiply<functor_type::complexity(), lsub_expression_t::complexity()>::value
			//		),
			//		select<std::greater>(
			//			rsub_expression_t::complexity(),
			//			size_multiply<functor_type::complexity(), rsub_expression_t::complexity()>::value
			//		)
			//	);
			return std::greater<size_t>{}(
				size_multiply<std::greater<size_t>{}(1, lsub_expression_t::complexity()), functor_type::complexity()>::value,
				size_multiply<std::greater<size_t>{}(1, rsub_expression_t::complexity()), functor_type::complexity()>::value);
		}

		value_type operator() (size_t index) const noexcept
		{
			return functor_type{}(get_expression(lhs_), get_expression(rhs_), index);
		}

		template <size_t Index>
		value_type get() const noexcept
		{
			return functor_type::get<Index>(get_expression(lhs_), get_expression(rhs_));
		}

		using base_type::operator();

	private:
		lsub_base_expression_t const& lhs_;
		rsub_base_expression_t const& rhs_;
	};
}