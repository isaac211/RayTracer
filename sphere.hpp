#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_
#include "object.hpp"

typedef double radiusType;

class Sphere : public Object
{
public:
	Sphere();

private:
	radiusType radius;
};
#endif