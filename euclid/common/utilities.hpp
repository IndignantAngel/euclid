#pragma once

namespace euclid
{
	// select
	template <template <typename> typename Pred, typename T>
	constexpr T select(T const lhs, T const rhs) noexcept
	{
		return Pred<T>{}(lhs, rhs) ? lhs : rhs;
	}
	/// select

	// calculate
	template <template <typename> typename Opr, typename T>
	constexpr T calculate(T const lhs, T const rhs) noexcept
	{
		return Opr<T>{}(lhs, rhs);
	}
	/// calculate

	// uniform tuple
	template <typename T, size_t N>
	class uniform_tuple
	{
		static_assert(is_numeric<T>::value, "Only for numeric types!");
	public:
		using value_type = T;
		using reference = T const&;
		using const_reference = T const&;
		using pointer = T const*;
		using const_poitner = T const*;
		using ptrdiff_t = std::ptrdiff_t;

	public:
		explicit uniform_tuple(value_type value) noexcept
			: value_(value)
		{

		}

		static constexpr size_t size() noexcept
		{
			return N;
		}

		value_type get() const noexcept
		{
			return value_;
		}

	private:
		value_type	value_;
	};

	template <size_t N, typename T>
	auto make_uniform_tuple(T value) noexcept
	{
		return uniform_tuple<T, N>{ value };
	}
	/// uniform tuple
}