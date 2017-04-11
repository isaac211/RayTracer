#include <cstdint>
#include <utility>
typedef std::pair<std::size_t,std::size_t> sizingType;
typedef std::pair<double, double> resolutionType;
typedef unsigned int focusType;

struct coords3D
{
	double x, y, z;
};

struct colorType
{
	std::uint8_t r, g, b;
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