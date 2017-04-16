#include "camera.hpp"

Camera::Camera() : focus(0)
{
	resolution = std::make_pair(0., 0.);
	size = std::make_pair(0, 0);
}