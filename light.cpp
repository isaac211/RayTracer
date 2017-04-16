#include "light.hpp"

Light::Light(coords3D loc, intensityType inten) : location(loc), intensity(inten)
{
}

intensityType Light::getIntensity() const
{
	return intensity;
}
coords3D Light::getLocation() const
{
	return location;
}
