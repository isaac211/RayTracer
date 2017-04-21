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
#include <cmath>


using std::string;


typedef std::vector<Sphere> sphereList;
typedef std::vector<Plane> planeList;
typedef std::vector<Light> lightList;
typedef std::vector<std::vector<colorType>> canvasType;

class Environment
{
public:
	Environment(sphereList s = sphereList(), planeList p = planeList(), lightList l = lightList(), Camera c = Camera());
	void unpackJSON(const QString &path);
	void unpackJSON(const string &path);
	void unpackJSON(const char* path);

	void printImage(const QString &path);
	void printImage(const string &path);
	void printImage(const char* path);

	planeList getPlanes() const;
	sphereList getSpheres() const;
	lightList getLights() const;
	Camera getCamera() const;

	bool isEmpty() const;
	bool hasLights() const;
	bool hasObjects() const;
	bool hasSpheres() const;
	bool hasPlanes() const;

protected:
	sphereList spheres;
	planeList planes;
	lightList lights;
	Camera camera;

	canvasType canvas;
};
#endif