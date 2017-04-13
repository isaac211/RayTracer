#ifndef _ENVIRONMENT_HPP_
#define _ENVIRONMENT_HPP_
#include "camera.hpp"
#include "light.hpp"
#include "object.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include <vector>

typedef std::vector<Object> objectList;
typedef std::vector<Light> lightList;

class Environment
{
public:
	Environment();

protected:
	objectList objects;
	lightList lights;
	Camera camera;
};
#endif