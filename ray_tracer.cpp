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

	sphereList spheres = scene.getSpheres();
	planeList planes = scene.getPlanes();
	lightList lights = scene.getLights();

	//Iterate through each pixel; set color to sphere if intersection occurs
	coordsType t;

	//single light for test
	Light light = lights[0];

	foreach(Sphere s, spheres)
	{
		QColor color(
			s.getColor().r,
			s.getColor().g,
			s.getColor().b);
		for (sizeType i = 0; i < imageX; ++i)
			for (sizeType j = 0; j < imageY; ++j)
			{
				const rayType ray(coords3D(i,j,0), s.getCenter());
				if (s.intersect(ray, t))
				{
					pixmap.setPixel(i, j, color.rgb());
				}
			}
	}

	//Save image to a file.
	pixmap.save(path, "PNG");
}

void RayTracer::printImage(const string &path)
{
	printImage(QString::fromStdString(path));
}

void RayTracer::printImage(const char* path)
{
	printImage(QString(path));
}