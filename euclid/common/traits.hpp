#pragma once

namespace euclid
{
	// is scalar expression
	template <typename Expr>
	struct is_scalar_expresion
	{
		static constexpr bool value =
			std::is_base_of<scalar_expression<Expr>, Expr>::value ||
			is_numeric<Expr>;
	};
	/// is scalar expression end

	// is numeric
	template <typename T>
	struct is_numeric : std::false_type {};

	template <>
	struct is_numeric<int8_t> : std::true_type {};

	template <>
	struct is_numeric<int16_t> : std::true_type {};

	template <>
	struct is_numeric<int32_t> : std::true_type {};

	template <>
	struct is_numeric<int64_t> : std::true_type {};

	template <>
	struct is_numeric<uint8_t> : std::true_type {};

	template <>
	struct is_numeric<uint16_t> : std::true_type {};

	template <>
	struct is_numeric<uint32_t> : std::true_type {};

	template <>
	struct is_numeric<uint64_t> : std::true_type {};

	template <>
	struct is_numeric<float_t> : std::true_type {};

	template <>
	struct is_numeric<double_t> : std::true_type {};
	/// is numeric end

	// is_same
	template <typename ... Args>
	struct is_same;

	template <typename T>
	struct is_same<T>
	{
		static constexpr bool value = true;
		typedef T type;
	};

	template <typename T1, typename T2>
	struct is_same<T1, T2> : std::is_same<T1, T2>
	{
		typedef std::enable_if_t<value, T1> type;
	};

	template <typename T1, typename T2, typename ... Args>
	struct is_same<T1, T2, Args...>
	{
		static constexpr bool value = and<is_same<T1, T2>, is_same<T2, Args...>>::value;
		typedef std::enable_if_t<value, T1> type;
	};
	/// is_same
}