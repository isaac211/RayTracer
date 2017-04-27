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

class Environment
{
public:
	Environment(sphereList s = sphereList(), planeList p = planeList(), lightList l = lightList(), Camera c = Camera());
	void unpackJSON(const QString &path);
	void unpackJSON(const string &path);
	void unpackJSON(const char* path);


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

	inline bool notInt(const QString &a)
	{
		foreach(QChar x, a)
			if (!x.isDigit()) 
				if (x != '-') return true;
		return false;
	}

	inline bool notDouble(const QString &a)
	{
		foreach(QChar x, a)
			if (!x.isDigit()) 
				if (x != '.' && x != '-') return true;
		return false;
	}
};
#endif