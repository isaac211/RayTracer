#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_
#include "object.hpp"

typedef double radiusType;

class Sphere : public Object
{
public:
	Sphere(coords3D cent = coords3D(),
		colorType cl = colorType(),
		lambertType lamb = 0,
		radiusType rad = 0.);

	radiusType getRadius() const;
private:
	radiusType radius;
};
#endif