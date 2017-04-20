#include "object.hpp"

Object::Object(coords3D cent, colorType cl, lambertType lamb) : center(cent),color(cl),lambert(lamb)
{
}
coords3D Object::getCenter() const
{
	return center;
}
colorType Object::getColor() const
{
	return color;
}
lambertType Object::getLambert() const
{
	return lambert;
}

