#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_
#include "camera.hpp"

typedef float lambertType;
typedef double radiusType;

struct rayType
{
	coords3D origin, destination;
	rayType(coords3D o, coords3D d) : origin(o), destination(o) {}
};

inline coordsType dotp(const coords3D &a, const coords3D &b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

class Object
{
public:
	Object(coords3D cent = coords3D(), colorType cl = colorType(), lambertType lamb = 0);
	coords3D getCenter() const;
	colorType getColor() const;
	lambertType getLambert() const;
protected:
	coords3D center;
	colorType color;
	lambertType lambert;
};
#endif