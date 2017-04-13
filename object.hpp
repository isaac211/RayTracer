#include "camera.hpp"

typedef float lambertType;

class Object
{
public:
	Object(coords3D center, colorType color, lambertType lambert = 0);

protected:
	coords3D center;
	colorType color;
	lambertType lambert;
};