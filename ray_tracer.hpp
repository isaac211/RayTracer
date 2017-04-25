#include "environment.hpp"
#include "qimage.h"
#include <cmath>


class RayTracer
{
public:
	RayTracer(Environment s);
	void printImage(const QString &path);
	void printImage(const string &path);
	void printImage(const char* path);

private:
	Environment scene;

};
