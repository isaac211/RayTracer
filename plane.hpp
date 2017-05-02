#ifndef _PLANE_HPP_
#define _PLANE_HPP_
#include "object.hpp"
class Plane : public Object
{
public:
	Plane(coords3D cent = coords3D(),
		colorType cl = colorType(),
		lambertType lamb = 0,
		coords3D norm = coords3D());
	coords3D getNormal() const;
	bool intersect(const rayType &ray, coordsType &t) const;

private:
	coords3D normal;
};
#endif