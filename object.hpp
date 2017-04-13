#include "camera.hpp"

typedef float lambertType;
typedef double radiusType;
enum objectType
{sphere};

class Object
{
public:
	Object();

private:
	coords3D center;
	colorType color;
	lambertType lambert;
	radiusType radius;
	objectType object;
};