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
	coordsType discrim = dotp(normal.getNormal(), ray.destination.getNormal());
	if (discrim < 0)
		return false;
	coords3D originsinter = ray.origin.getNormal() - center.getNormal();
	t = dotp(originsinter, normal.getNormal());
	return (t >= 0);
}