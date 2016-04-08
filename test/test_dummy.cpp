#include <euclid/vector.hpp>

template <typename T1 ,typename T2>
struct addition_traits
{
	using type = decltype(std::declval<T1>() + std::declval<T2>());
};

template <typename T>
struct addition
{
	using result_type = T;
	inline constexpr result_type operator() (T const& lhs, T const& rhs) const noexcept
	{
		return lhs + rhs;
	}
};

template <typename T>
class foo {};

class fee : public foo<fee> {};

int main(void)
{
	using namespace euclid::placehodler;
	
	euclid::vector<float, 4> v = { 1.0f };
	euclid::vector<float, 4> w = { 1.0f, 2.0f, 3.0f, 4.0f};
	euclid::vector<float, 3> x = { 1.0f, 3.0f, 5.0f };
	
	euclid::vector<float, 4> u = w;
	u(_r, _g, _b) = x;
	u(_b, _g, _r) = x;
	
	//euclid::vector<float, 3> r = cross(u(_r, _g, _b), u(_b, _g, _r));

	size_t r = cross(u(_r, _g, _b), u(_b, _g, _r)).complexity();

	return 0;
}