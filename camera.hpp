#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_
#include <cstdint>
#include <utility>
#include <cmath>
using std::make_pair;
typedef long int sizeType;
typedef std::pair<sizeType,sizeType> sizingType;
typedef std::pair<double, double> resolutionType;
typedef int focusType;
typedef int rgbType;
typedef double coordsType;

struct coords3D
{
	coordsType x, y, z;
	coords3D(coordsType xin = 0, coordsType yin = 0, coordsType zin = 0) : x(xin), y(yin), z(zin) {}
	coords3D operator+ (const coords3D & vec) const 
	{
		return coords3D(x + vec.x, y + vec.y, z+vec.z);
	}

	coords3D operator- (const coords3D & vec) const 
	{
		return coords3D(x - vec.x, y - vec.y, z-vec.z);
	}

	coords3D operator* (const coordsType m) const 
	{
		return coords3D(x*m, y*m, z*m);
	}

	coords3D operator/ (const coordsType d) const 
	{
		return coords3D(x/d, y/d, z/d);
	}

	bool operator== ( const coords3D &b) const
	{
		return (this->x != b.x) ? false : (this->y != b.y) ? false : (this->z != b.z) ? false : true;
	}

	coords3D getNormal() const
	{
		coordsType mg = std::sqrt(x*x + y*y + z*z);
		return coords3D(x / mg, y / mg, z / mg);
	}
};

struct colorType
{
	colorType(rgbType rin = 0, rgbType gin = 0, rgbType bin = 0) : r(rin),g(gin),b(bin) {}
	rgbType r, g, b;
};

class Camera
{
public:
	Camera(coords3D c = coords3D(),
		sizingType s = sizingType(),
		focusType f = 0,
		resolutionType r = resolutionType(),
		coords3D n = coords3D()
		);

	coords3D getCenter() const;
	sizingType getSize() const;
	focusType getFocus() const;
	resolutionType getResolution() const;
	coords3D getNormal() const;

private:
	coords3D center;
	sizingType size;
	focusType focus;
	resolutionType resolution;
	coords3D normal;
};
#endif