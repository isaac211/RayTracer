#include "ray_tracer.hpp"
#include <qdebug.h>

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
	coords3D camNormal(scene.getCamera().getNormal());
	focusType focus(scene.getCamera().getFocus());

	const QRgb black = qRgb(0, 0, 0); //default background color
	const QRgb white = qRgb(255, 255, 255); // for use in shading

	foreach(Sphere s, spheres)
	{
		auto const r = s.getColor().r;
		auto const g = s.getColor().g;
		auto const b = s.getColor().b;
		auto const lambert = s.getLambert();
		std::queue<coords3D> precolorsQueue;
		std::queue<bool> intersectQueue;

		coordsType highR(0), lowR(0), highG(0), lowG(0), highB(0), lowB(0);

		for (sizeType j = 0; j < imageY; ++j)
			for (sizeType i = 0; i < imageX; ++i)
			{
				const coordsType pixelX = resX*(i - (imageX / 2));
				const coordsType pixelY = resY*(j - (imageY / 2));
				const coords3D newOrig = camNormal * -focus + camCenter;
				const coords3D newDest = (coords3D(pixelX, pixelY, camCenter.z) - newOrig);
				const rayType ray(newOrig, newDest);

				//Iterate through each pixel; set color to sphere if intersection occurs
				coordsType t = 0;

				if (s.intersect(ray, t))
				{
					intersectQueue.push(true);

					//Calculate point of intersection
					const coords3D inter = ray.origin + ray.destination*t;

					//Color based on light reflection
					const coords3D &lightRef = light.getLocation();
					const coords3D &normalRef = s.getNormal(inter);
					coordsType scale = lambert*dotp(lightRef.normalize(), normalRef.normalize());
					scale = (scale < 0) ? 0 : scale;

					coords3D precolor = (coords3D(r, g, b) *scale) * lightInt;
					precolorsQueue.push(precolor);

					//Find lowest and highest scaled values for auto exposure
					lowR = (precolor.x < lowR) ? precolor.x : lowR;
					highR = (precolor.x > highR) ? precolor.x : highR;
					lowG = (precolor.x < lowG) ? precolor.x : lowG;
					highG = (precolor.x > highG) ? precolor.x : highG;
					lowB = (precolor.x < lowB) ? precolor.x : lowB;
					highB = (precolor.x > highB) ? precolor.x : highB;

				}
				else
					intersectQueue.push(false);
			}

		auto const balancedR = highR - lowR;
		auto const balancedB = highB - lowB;
		auto const balancedG = highG - lowG;

		for (sizeType j = 0; j < imageY; ++j)
			for (sizeType i = 0; i < imageX; ++i)
			{
				if (intersectQueue.front())
				{
					coords3D precolor = precolorsQueue.front();
					precolorsQueue.pop();

					//Auto exposure
					QRgb color = qRgb(precolor.x / balancedR * 255,
						precolor.y / balancedG * 255,
						precolor.z / balancedB * 255);

					pixmap.setPixel(i, j, color);
				}
				else
					pixmap.setPixel(i, j, black);
				intersectQueue.pop();
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