#include "object.hpp"

Object::Object(coords3D cent, colorType cl, lambertType lamb) : center(cent),color(cl),lambert(lamb)
{
}
coords3D Object::getCenter()
{
	return center;
}
colorType Object::getColor()
{
	return color;
}
lambertType Object::getLambert()
{
	return lambert;
}