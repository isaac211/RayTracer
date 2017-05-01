#include "ray_tracer.hpp"

RayTracer::RayTracer(Environment s) : scene(s)
{
}

void RayTracer::printImage(const QString &path)
{
	//Set width and height of a QImage pixel map
	const sizeType imageX = scene.getCamera().getSize().first;
	const sizeType imageY = scene.getCamera().getSize().second;
	const auto resX = scene.getCamera().getResolution().first;
	const auto resY = scene.getCamera().getResolution().second;
	QImage pixmap(imageX, imageY, QImage::Format_ARGB32);

	sphereList spheres = scene.getSpheres();
	planeList planes = scene.getPlanes();
	lightList lights = scene.getLights();


	//single light for test
	Light light = lights[0];
	const auto lightInt = light.getIntensity();

	coords3D camCenter(scene.getCamera().getCenter());
	focusType focus(scene.getCamera().getFocus());

	const QRgb black = qRgb(0, 0, 0); //default background color
	const QRgb white = qRgb(255, 255, 255); // for use in shading

	foreach(Sphere s, spheres)
	{
		auto const r = s.getColor().r;
		auto const g = s.getColor().g;
		auto const b = s.getColor().b;
		auto const lambert = s.getLambert();

			for (sizeType i = 0; i < imageX; ++i)
				for (sizeType j = 0; j < imageY; ++j)
				{
					const coordsType pixelX = (i - (imageX / 2)); //TODO: Apply resolution
					const coordsType pixelY = (j - (imageY / 2));
					const rayType ray(camCenter + coords3D(pixelX, pixelY, 0), coords3D(0, 0, -focus));

					//Iterate through each pixel; set color to sphere if intersection occurs
					coordsType t = 0;

					if (s.intersect(ray, t))
					{
						//Calculate point of intersection
						const coords3D &inter = ray.origin + ray.destination*t;

						//Color based on light reflection
						const coords3D &lightRef = light.getLocation() - inter;
						const coords3D &normalRef = s.getNormal(inter);
						coordsType scale = lambert*dotp(lightRef.getNormal(), normalRef.getNormal());
						scale = (scale < 0) ? 0 : scale;

						coords3D precolor = (coords3D(r, g, b) + coords3D(255, 255, 255)*scale) * lightInt;
						const QRgb color = qRgb(rgbLock(std::round( precolor.x)),
							rgbLock( std::round(precolor.y)),
							rgbLock(std::round(precolor.z)));


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