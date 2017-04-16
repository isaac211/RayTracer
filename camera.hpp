#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_
#include <cstdint>
#include <utility>
using std::make_pair;
typedef std::pair<std::size_t,std::size_t> sizingType;
typedef std::pair<double, double> resolutionType;
typedef unsigned int focusType;
typedef std::uint8_t rgbType;
typedef double coordsType;

struct coords3D
{
	coords3D() : x(0.), y(0.), z(0.) {}
	coordsType x, y, z;
};

struct colorType
{
	colorType() : r(0),g(0),b(0) {}
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