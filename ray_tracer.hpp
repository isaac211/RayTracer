#include "environment.hpp"
#include "qimage.h"
#include <cmath>

inline rgbType autoExpose(const rgbType &color)
{
	return (color > 255) ? 255 : (color < 0) ? 0 : color;
}

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
