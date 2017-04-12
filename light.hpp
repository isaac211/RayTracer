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