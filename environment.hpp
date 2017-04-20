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
#include <string>
#include "qdebug.h"

using std::string;

typedef std::vector<Object*> objectList;
typedef std::vector<Light> lightList;

class Environment
{
public:
	Environment(objectList o = objectList(), lightList l = lightList(), Camera c = Camera());
	void unpackJSON(const QString &path);
	void unpackJSON(const string &path);
	void unpackJSON(const char* path);

	void printImage(const QString &path);
	void printImage(const string &path);
	void printImage(const char* path);

	objectList getObjects() const;
	lightList getLights() const;
	Camera getCamera() const;

protected:
	objectList objects;
	lightList lights;
	Camera camera;
};
#endif