#pragma once

namespace euclid
{
	template <typename T, size_t N, typename Base>
	class vector : public vector_expression<vector<T, N, Base>>
	{
		static_assert(is_numeric<T>::value, "Must be a numeric type!");
		static_assert(and<size_equal_greater_than<N, 2>, size_equal_less_than<N, 4>>::value
			, "Illegal demension for vector!");
	public:
		using base_type = vector_expression<vector<T, N, Base>>;

		using value_type = T;
		using reference = T&;
		using const_reference = T const&;
		using pointer = T*;
		using const_pointer = T const*;
		using array_type = std::array<T, N>;
		using base_tag = Base;

		static constexpr size_t the_size = N;

	public:
		
		// default construct
		vector() noexcept = default;

		// one param construct
		vector(value_type value) noexcept
		{
			fill(*this, value);
		}

		// variadic construct
		template <typename Arg0, typename ... Args, typename = 
			detail::variadic_param_enable_if_t<the_size, Arg0, Args...>>
		vector(Arg0 arg0, Args ... args) noexcept
		{
			fill(*this, std::make_tuple(arg0, args...));
		}

		// copy construct
		vector(vector const&) noexcept = default;

		// convert construct
		template <typename Expr>
		vector(vector_expression<Expr> const& vec) noexcept
		{
			assign(*this, vec);
		}

		// copy assign
		vector& operator= (vector const&) noexcept = default;

		template <typename Expr>
		vector& operator= (vector_expression<Expr> const& vec) noexcept
		{
			vector temp = vec;
			assign(*this, temp);
			return *this;
		}

		// get size
		static constexpr size_t size() noexcept
		{
			return the_size;
		}

		// get calculation complexity
		static constexpr size_t complexity() noexcept
		{
			return 0;
		}

		// operator index
		const_reference operator() (size_t const index) const noexcept
		{
			return data_[index];
		}

		reference operator() (size_t index) noexcept
		{
			return data_[index];
		}
		/// operator index

		// static member indexing
		template <size_t Index>
		const_reference get() const noexcept
		{
			return data_[Index];
		}

		template <size_t Index>
		reference get() noexcept
		{
			return data_[Index];
		}
		/// static member indexing

		// data
		pointer data() noexcept
		{
			return data_.data();
		}

		const_pointer data() const noexcept
		{
			return data_.data();
		}
		/// data

		using base_type::operator();

	private:
		array_type		data_;
	};
}