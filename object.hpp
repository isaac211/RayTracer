#include "camera.hpp"

typedef float lambertType;

class Object
{
public:
	Object();

private:
	coords3D center;
	colorType color;
	lambertType lambert;
};