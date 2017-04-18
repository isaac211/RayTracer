#include "sphere.hpp"

Sphere::Sphere(coords3D cent,
	colorType cl,
	lambertType lamb,
	radiusType rad)
	: radius(rad)
{
	center = cent;
	color = cl;
	radius = rad;
}

radiusType Sphere::getRadius() const
{
	return radius;
}