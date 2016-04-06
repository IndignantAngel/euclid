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

		template <typename OtherExpr>
		vector_proxy& operator= (vector_expression<OtherExpr> const& e) noexcept
		{
			using vector_type = vector<value_type, the_size, base_tag>;
			vector_type temp = e;
			assign(*this, temp);
			return *this;
		}

		static constexpr size_t size() noexcept
		{
			return Indices::size();
		}

		static constexpr size_t complexity() noexcept
		{
			return proxy_traits::complexity;
		}

		template <typename = std::enable_if_t<proxy_traits::is_lvalue>>
		pointer data() noexcept
		{
			return get_expression(e_).data();
		}
		
		template <typename = std::enable_if_t<proxy_traits::is_lvalue>>
		const_pointer data() const noexcept
		{
			return get_expression(e_).data();
		}

		template <size_t Index>
		reference get() noexcept
		{
			// implement nonconst with const
			return const_cast<reference>(const_cast<vector_proxy const&>(*this).get<Index>());
		}

		template <size_t Index>
		const_reference get() const noexcept
		{
			constexpr auto index = std::get<Index>(Indices{});
			return get_expression(e_).get<index>();
		}

	private:
		sub_base_expression_t&	e_;
	};
}