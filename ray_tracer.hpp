#include "environment.hpp"
typedef std::vector<std::vector<colorType>> canvasType;
class RayTracer
{
public:
	RayTracer(Environment s);
	void printImage(const QString &path);
	void printImage(const string &path);
	void printImage(const char* path);

private:
	Environment scene;
	canvasType canvas;

};
