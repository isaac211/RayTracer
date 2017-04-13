#ifndef _PLANE_HPP_
#define _PLANE_HPP_
#include "object.hpp"
class Plane : public Object
{
public:
	Plane();
private:
	coords3D normal;
};
#endif