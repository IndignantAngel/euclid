#pragma once

namespace euclid
{
	// and
	template <typename ... Args>
	struct and;

	template <typename Arg>
	struct and<Arg>
	{
		static constexpr bool value = Arg::value;
	};

	template <typename Arg, typename ... Args>
	struct and<Arg, Args ...>
	{
		static constexpr bool value = Arg::value &&
			and<Args...>::value;
	};
	/// end of and

	// or
	template <typename ... Args>
	struct or;

	template <typename Arg>
	struct or<Arg>
	{
		static constexpr bool value = Arg::value;
	};

	template <typename Arg, typename ... Args>
	struct or<Arg, Args ...>
	{
		static constexpr bool value = Arg::value ||
			or<Args...>::value;
	};
	/// end of or

	// not
	template <typename Arg>
	struct not
	{
		static constexpr bool value = !Arg::value;
	};
	/// not

	// greater_than
	template <typename T, T Lhs, T Rhs>
	struct greater_than
	{
		static constexpr bool value =
			Lhs > Rhs;
	};
	template <size_t Lhs, size_t Rhs>
	using size_greater_than = greater_than<size_t, Lhs, Rhs>;
	/// greater_than

	// equal_greater_than
	template <typename T, T Lhs, T Rhs>
	struct equal_greater_than
	{
		static constexpr bool value =
			Lhs >= Rhs;
	};
	template <size_t Lhs, size_t Rhs>
	using size_equal_greater_than = equal_greater_than<size_t, Lhs, Rhs>;
	/// equal_greater_than

	// less_than
	template <typename T, T Lhs, T Rhs>
	struct less_than
	{
		static constexpr bool value =
			Lhs < Rhs;
	};
	template <size_t Lhs, size_t Rhs>
	using size_less_than = less_than<size_t, Lhs, Rhs>;
	/// less_than

	// equal_less_than
	template <typename T, T Lhs, T Rhs>
	struct equal_less_than
	{
		static constexpr bool value =
			Lhs <= Rhs;
	};
	template <size_t Lhs, size_t Rhs>
	using size_equal_less_than = equal_less_than<size_t, Lhs, Rhs>;
	/// equal_less_than

	// equal
	template <typename T, T Lhs, T Rhs>
	struct equal
	{
		static constexpr bool value =
			Lhs == Rhs;
	};
	template <size_t Lhs, size_t Rhs>
	using size_equal = equal<size_t, Lhs, Rhs>;
	/// equal

	// add & size_add, size_increment
	template <typename T, T Val, T Add>
	struct add : std::integral_constant<T, Val + Add>{ };
	template <size_t Val, size_t Add>
	using size_add = add<size_t, Val, Add>;
	template <size_t Val>
	using size_increment = add<size_t, Val, 1>;
	/// add

	// greater
	template <typename T, T ... Vals>
	struct greater;
	template <typename T, T First>
	struct greater<T, First>
	{
		static constexpr T value = First;
	};
	template <typename T, T First, T Second, T ... Rests>
	struct greater<T, First, Second, Rests...>
	{
		static constexpr T value = First > Second ?
			greater<T, First, Rests...>::value : greater<T, Second, Rests...>::value;
	};
	template <size_t ... Vals>
	using size_greater = greater<size_t, Vals...>;

	// less
	template <typename T, T Lhs, T Rhs>
	struct less
	{
		static constexpr T value = Lhs < Rhs ? Lhs : Rhs;
	};
	template <size_t Lhs, size_t Rhs>
	using size_less = less<size_t, Lhs, Rhs>;

	// subtract & size_subtract, size_decrement
	template <typename T, T Val, T Sub>
	struct subtract : std::integral_constant<T, Val - Sub> 
	{
		static_assert(
			std::conditional_t<
				std::is_unsigned<T>::value,
				equal_greater_than<T, Val, Sub>,
				std::true_type>::value,
			"Val must be equal greater than Sub when T is unsigned!");
	};
	template <size_t Val, size_t Sub>
	using size_subtract = subtract<size_t, Val, Sub>;
	template <size_t Val>
	using size_decrement = subtract<size_t, Val, 1>;
	/// subtract

	// add & size_add, size_increment
	template <typename T, T Val, T Mult>
	struct multiply : std::integral_constant<T, Val * Mult> { };
	template <size_t Val, size_t Mult>
	using size_multiply = multiply<size_t, Val, Mult>;
	template <size_t Val>
	using size_square = multiply<size_t, Val, Val>;

	template <typename T, T Val, T Mod, typename = 
		std::enable_if_t<std::is_integral<T>::value>>
	struct mod : std::integral_constant<T, Val % Mod> {};
	template <size_t Val, size_t Mod>
	using size_mod = mod<size_t, Val, Mod>;
}