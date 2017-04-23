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
	lambert = lamb;
}

radiusType Sphere::getRadius() const
{
	return radius;
}

bool Sphere::intersect(const rayType &ray, coordsType &t) const
{
	//Calculate quadratic
	const coords3D origin = ray.origin;
	const coords3D destination = ray.destination;
	const coords3D oc = origin - center;

	const coordsType b = 2 * dotp(oc, destination);
	const coordsType c = dotp(oc, oc) - radius*radius;

	//Calculate distance to center, no intersect if number close to 0
	coordsType dist2c = b*b - 4 * c;

	if (dist2c < 1e-5)
		return false;

	//Choose between two possible quadratic answers for surface intersection and return it
	dist2c = std::sqrt(dist2c);
	const coordsType t0 = -b - dist2c;
	const coordsType t1 = -b + dist2c;
	t = (t0 < t1) ? t0 : t1;

	return true;
}

coords3D Sphere::getNormal(const coords3D &pi) const
{
	return (pi - center) / radius;
}
