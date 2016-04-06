#pragma once

namespace euclid
{
	template <typename T>
	struct scalar_positive : std::unary_function<T, T>
	{
		constexpr result_type operator() (argument_type const& arg) const noexcept
		{
			return arg;
		}
	};

	template <typename T>
	struct scalar_negative : std::unary_function<T, decltype(-std::declval<T>())>
	{
		constexpr result_type operator() (argument_type const& arg) const noexcept
		{
			return -arg;
		}
	};

	template <typename T>
	struct scalar_square : std::unary_function<T, decltype(std::declval<T>() * std::declval<T>())>
	{
		constexpr result_type operator() (argument_type const& arg) const noexcept
		{
			return arg * arg;
		}
	};

	template <typename T>
	struct scalar_inverse : std::unary_function<T, decltype(std::declval<T>() / std::declval<T>())>
	{
		constexpr result_type operator() (argument_type const& arg) const noexcept
		{
			return static_cast<T>(1) / arg;
		}
	};

	template <typename T1, typename T2>
	struct scalar_addition : std::binary_function<T1, T2, decltype(std::declval<T1>() + std::declval<T2>())>
	{
		constexpr result_type operator() (
			first_argument_type const& lhs, 
			second_argument_type const& rhs) const noexcept
		{
			return lhs + rhs;
		}
	};

	template <typename T1, typename T2>
	struct scalar_subtraction : std::binary_function<T1, T2, decltype(std::declval<T1>() - std::declval<T2>())>
	{
		constexpr result_type operator() (
			first_argument_type const& lhs,
			second_argument_type const& rhs) const noexcept
		{
			return lhs - rhs;
		}
	};

	template <typename T1, typename T2>
	struct scalar_multiplication : std::binary_function<T1, T2, decltype(std::declval<T1>() * std::declval<T2>())>
	{
		constexpr result_type operator() (
			first_argument_type const& lhs,
			second_argument_type const& rhs) const noexcept
		{
			return lhs * rhs;
		}
	};

	template <typename T1, typename T2>
	struct scalar_division : std::binary_function<T1, T2, decltype(std::declval<T1>() / std::declval<T2>())>
	{
		constexpr result_type operator() (
			first_argument_type const& lhs,
			second_argument_type const& rhs) const noexcept
		{
			return lhs / rhs;
		}
	};
}