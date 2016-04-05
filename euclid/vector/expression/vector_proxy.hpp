#pragma once

namespace euclid
{
	template <typename Expr, typename Indices>
	class vector_proxy : public vector_expression<vector_proxy<Expr, Indices>>
	{
		using traits_t = vector_expression_traits<Expr>;

		static_assert(traits_t::value, "Not a valid vector expression!");
		static_assert(size_equal_greater_than<4, Indices::size()>::value, "Proxy size dosen`t match!");
		static_assert(detail::proxy_indices_valid<Expr, Indices>::value, "Index overflow!");
	public:
		using base_type = vector_expression<vector_proxy<Expr, Indices>>;
		using sub_base_expression_t = typename traits_t::base_expression_t;
		using sub_expression_t = typename traits_t::expression_t;

		using proxy_traits = detail::proxy_lvalue_traits<sub_expression_t, Indices>;

		using value_type = typename sub_expression_t::value_type;
		using reference = typename sub_expression_t::reference;
		using const_reference = typename sub_expression_t::const_reference;
		using pointer = typename sub_expression_t::pointer;
		using const_pointer = typename sub_expression_t::const_pointer;
		using base_tag = typename sub_expression_t::base_tag;

		static constexpr size_t the_size = Indices::size();

	public:
		vector_proxy(sub_base_expression_t& e) noexcept
			: e_(e)
		{

		}

		static constexpr size_t size() noexcept
		{
			return Indices::size();
		}

		static constexpr size_t complexity() noexcept
		{
			return proxy_traits::complexity;
		}

		auto data() noexcept
			-> std::enable_if_t<proxy_traits::is_lvalue, pointer>
		{
			return get_expression(e_).data();
		}

		auto data() const noexcept
			->std::enable_if_t<proxy_traits::is_lvalue, const_pointer>
		{
			return get_expression(e_).data();
		}

		using base_type::operator();

	private:
		sub_base_expression_t&	e_;
	};
}