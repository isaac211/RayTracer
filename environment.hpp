#ifndef _ENVIRONMENT_HPP_
#define _ENVIRONMENT_HPP_
#include "camera.hpp"
#include "light.hpp"
#include "object.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include <vector>
#include "qjsondocument.h"
#include "qimage.h"
#include "qfile.h"
#include "qstring.h"
#include "qjsonobject.h"
#include "qjsonarray.h"

typedef std::vector<Object> objectList;
typedef std::vector<Light> lightList;

class Environment
{
public:
	Environment();
	void unpackJSON(const QString &path);
	void printImage();

protected:
	objectList objects;
	lightList lights;
	Camera camera;

private:
	void setCamera
		(
			const coords3D &center,
			const sizingType &size,
			const focusType &focus,
			const resolutionType &resolution,
			const coords3D &normal
			);

	void pushLight
		(
			const intensityType &intensity,
			const coords3D &location
			);

	void pushObject
		(

			);
};
#endif