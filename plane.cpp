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

bool Plane::intersect(const rayType &ray, coordsType &t) const
{
	coordsType discrim = dotp(normal.normalize(), ray.destination.normalize());
	if (discrim < 0)
		return false;
	coords3D originsinter = ray.origin.normalize() - center.normalize();
	t = dotp(originsinter, normal.normalize());
	return (t >= 0);
}