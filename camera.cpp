#include "camera.hpp"

Camera::Camera(coords3D c,
	sizingType s,
	focusType f,
	resolutionType r,
	coords3D n
	) : center(c), size(s), focus(f), resolution(r), normal(n)
{}

coords3D Camera::getCenter() const
{
	return center;
}

sizingType Camera::getSize() const
{
	return size;
}

focusType Camera::getFocus() const
{
	return focus;
}

resolutionType Camera::getResolution() const
{
	return resolution;
}

coords3D Camera::getNormal() const
{
	return normal;
}