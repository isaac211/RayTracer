#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_
#include "object.hpp"
#include <stdexcept>

class Sphere : public Object
{
public:
	Sphere(coords3D cent = coords3D(),
		colorType cl = colorType(),
		lambertType lamb = 0,
		radiusType rad = 0.);

	radiusType getRadius() const;

	bool intersect(const rayType &ray, coordsType &t) const;
	coords3D getNormal(const coords3D &pi) const;
private:
	radiusType radius;
};
#endif