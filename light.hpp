#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_
typedef float intensityType;
#include "camera.hpp"


class Light
{
public:
	Light(coords3D loc = coords3D(), intensityType inten = 0.);
	intensityType getIntensity() const;
	coords3D getLocation() const;

private:
	intensityType intensity;
	coords3D location;
};
#endif