#include "camera.hpp"

typedef float lambertType;

class Object
{
public:
	Object(coords3D cent, colorType cl, lambertType lamb = 0);
	coords3D getCenter();
	colorType getColor();
	lambertType getLambert();

protected:
	coords3D center;
	colorType color;
	lambertType lambert;
};