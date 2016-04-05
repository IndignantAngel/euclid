#include <euclid/vector.hpp>

int main(void)
{
	using euclid::placehodler::_1;
	using euclid::placehodler::_2;
	using euclid::placehodler::_3;
	using euclid::placehodler::_4;

	euclid::vector<float, 4> v = { 1.0f };
	euclid::vector<float, 4> w = { 1.0f, 2.0f, 3.0f, 4.0f};

	euclid::vector<double, 4> u = w;

	u = v;

	//u(_1, _2, _3, _4) = w;

	return 0;
}