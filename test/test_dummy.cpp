#include <euclid/vector.hpp>

int main(void)
{
	using namespace euclid::placehodler;
	
	euclid::vector<float, 4> v = { 1.0f };
	euclid::vector<float, 4> w = { 1.0f, 2.0f, 3.0f, 4.0f};
	euclid::vector<float, 3> x = { 1.0f, 3.0f, 5.0f };
	
	euclid::vector<float, 4> u = w;
	u(_r, _g, _b) = x;
	u(_b, _g, _r) = x;
	return 0;
}