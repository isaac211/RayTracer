#include "ray_tracer.hpp"

RayTracer::RayTracer(Environment s) : scene(s)
{
}

void RayTracer::printImage(const QString &path)
{
	//Set width and height of a QImage pixel map
	const sizeType imageX = scene.getCamera().getSize().first;
	const sizeType imageY = scene.getCamera().getSize().second;
	QImage pixmap(imageX, imageY, QImage::Format_ARGB32);

	//Iterate through each pixel; set color to sphere if intersection occurs
	for (sizeType i = 0; i < imageX; ++i)
		for (sizeType j = 0; j < imageY; ++j)
		{
			;
		}

	//Save image to a file.
	QFile output(path);
	pixmap.save(output.fileName(), "PNG");
}

void RayTracer::printImage(const string &path)
{
	printImage(QString::fromStdString(path));
}

void RayTracer::printImage(const char* path)
{
	printImage(QString(path));
}