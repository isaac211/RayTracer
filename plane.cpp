#include "plane.hpp"
Plane::Plane(coords3D cent,
	colorType cl,
	lambertType lamb,
	coords3D norm) : normal(norm)
{
	center = cent;
	color = cl;
	lambert = lamb;
}

coords3D Plane::getNormal() const
{
	return normal;
}