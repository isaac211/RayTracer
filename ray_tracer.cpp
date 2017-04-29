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


	//single light for test
	Light light = lights[0];

	coords3D camCenter(scene.getCamera().getCenter());
	focusType focus(scene.getCamera().getFocus());

	const QRgb black = qRgb(0, 0, 0); //default background color
	const QRgb white = qRgb(255, 255, 255); // for use in shading

	foreach(Sphere s, spheres)
	{
		QRgb color = qRgb(
			rgbLock(s.getColor().r),
			rgbLock(s.getColor().g),
			rgbLock(s.getColor().b)
			);


		for (sizeType i = 0; i < imageX; ++i)
			for (sizeType j = 0; j < imageY; ++j)
			{
				const rayType ray(camCenter + coords3D(i,j,0), coords3D(0,0,focus));

				//Iterate through each pixel; set color to sphere if intersection occurs
				coordsType t = 0;

				if (s.intersect(ray, t))
				{
					pixmap.setPixel(i, j, color);
				}
				else
					pixmap.setPixel(i, j, black);
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