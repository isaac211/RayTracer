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
	coords3D(coordsType xin = 0, coordsType yin = 0, coordsType zin = 0) : x(xin), y(yin), z(zin) {}
	coordsType x, y, z;
};

struct colorType
{
	colorType(rgbType rin = 0, rgbType gin = 0, rgbType bin = 0) : r(rin),g(gin),b(bin) {}
	rgbType r, g, b;
};

class Camera
{
public:
	Camera();

private:
	coords3D center;
	sizingType size;
	focusType focus;
	resolutionType resolution;
	coords3D normal;
};
#endif