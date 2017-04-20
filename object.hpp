#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_
#include "camera.hpp"

typedef float lambertType;
typedef double radiusType;

class Object
{
public:
	Object(coords3D cent = coords3D(), colorType cl = colorType(), lambertType lamb = 0);
	coords3D getCenter() const;
	colorType getColor() const;
	lambertType getLambert() const;
	virtual radiusType getRadius() const;
	virtual coords3D getNormal() const;
protected:
	coords3D center;
	colorType color;
	lambertType lambert;
};
#endif