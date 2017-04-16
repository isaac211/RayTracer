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
};
#endif