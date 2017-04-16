#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_
#include "camera.hpp"

typedef float lambertType;

class Object
{
public:
	Object(coords3D cent = coords3D(), colorType cl = colorType(), lambertType lamb = 0);
	coords3D getCenter();
	colorType getColor();
	lambertType getLambert();

protected:
	coords3D center;
	colorType color;
	lambertType lambert;
};
#endif