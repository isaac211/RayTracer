#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_
typedef float intensityType;
#include "camera.hpp"


class Light
{
public:
	Light();

private:
	intensityType intensity;
	coords3D location;
};
#endif