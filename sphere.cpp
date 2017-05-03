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
	const coords3D oc = ray.origin - center;

	const coordsType b = 2 * dotp(oc, ray.destination);
	const coordsType c = dotp(oc, oc) - radius*radius;
	const coordsType a = dotp(ray.destination, ray.destination);

	//Calculate discriminant, no intersect if number close to 0
	coordsType discrim = b*b - 4 *a* c;

	//Choose between two possible quadratic answers for surface intersection and return it
	coordsType t0, t1;
	if (discrim < 0)
		return false;
	else if (discrim == 0)
		t0 = t1 = -b / a;
	else
	{
		discrim = std::sqrt(discrim);
		coordsType q = (b <= 0) ? (-b + discrim) : (-b - discrim);
		t0 = q/a;
		t1 = c/q;
	}

	if (t0 > t1)
		std::swap(t0, t1);

	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0) return false;
	}
	t = t0;
	return true;
}

coords3D Sphere::getNormal(const coords3D &pi) const
{
	return (pi - center) / radius;
}
