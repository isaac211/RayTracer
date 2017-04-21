#include "ray_tracer.hpp"

RayTracer::RayTracer(Environment s) : scene(s)
{
}
void RayTracer::printImage(const QString &path)
{

}

void RayTracer::printImage(const string &path)
{
	printImage(QString::fromStdString(path));
}

void RayTracer::printImage(const char* path)
{
	printImage(QString(path));
}
