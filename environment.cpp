#include "environment.hpp"


Environment::Environment(sphereList s, planeList p, lightList l, Camera c)
	: spheres(s), planes(p), lights(l), camera(c)
{
}

void Environment::unpackJSON(const QString &path)
{
	//Read in file contents and store in QJsonDocument type
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QJsonParseError JsonParseError;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
	file.close();

	//Check for parsing errors; throw if detected.
	if (JsonParseError.error != QJsonParseError::NoError)
		throw std::runtime_error("Error: Failed to parse JSON!");

	//Store camera, lights, and objects in convenient data types
	QJsonObject rootObject = jsonDoc.object();
	QJsonObject camObj = rootObject["camera"].toObject();
	QJsonArray lightArray = rootObject["lights"].toArray();
	QJsonArray objArray = rootObject["objects"].toArray();

	//camera parsing
	auto centerObj = camObj["center"].toObject();
	auto sizeObj = camObj["size"].toArray();
	auto resolObj = camObj["resolution"].toArray();
	auto normalObj = camObj["normal"].toObject();

	coords3D center(
		centerObj["x"].toDouble(), centerObj["y"].toDouble(), centerObj["z"].toDouble()
		);

	sizingType size(sizeObj[0].toInt(), sizeObj[1].toInt());

	resolutionType resolution(resolObj[0].toDouble(), resolObj[1].toDouble());

	coords3D normal(
		normalObj["x"].toDouble(), normalObj["y"].toDouble(), normalObj["z"].toDouble()
		);
	
	camera = Camera(
		center,
		size,
		(unsigned int)camObj["focus"].toInt(),
		resolution,
		normal
		);

	//Light parsing
	foreach (const QJsonValue &value, lightArray)
	{
		auto lightObj = value.toObject();

		auto locObj = lightObj["location"].toObject();

		lights.push_back(
			Light(
				coords3D(locObj["x"].toDouble(),
					locObj["y"].toDouble(),
					locObj["z"].toDouble()
					),
				(float)lightObj["intensity"].toDouble()
				)
			);
	}

	//object parsing
	foreach  (const QJsonValue &value, objArray)
	{
		auto obj = value.toObject();

		auto centerObj = obj["center"].toObject();
		auto colorObj = obj["color"].toObject();

		if (obj["type"].toString() == "sphere")
		{
			spheres.push_back(Sphere(
				coords3D(
					centerObj["x"].toDouble(),
					centerObj["y"].toDouble(),
					centerObj["z"].toDouble()),
				colorType(
					colorObj["r"].toInt(),
					colorObj["g"].toInt(),
					colorObj["b"].toInt()),
				(float)obj["lambert"].toDouble(),
				obj["radius"].toDouble()
				));
		}

		else if (obj["type"].toString() == "plane")
		{
			auto normalObj = obj["normal"].toObject();
			planes.push_back(Plane(
				coords3D(
					centerObj["x"].toDouble(),
					centerObj["y"].toDouble(),
					centerObj["z"].toDouble()),
				colorType(
					colorObj["r"].toInt(),
					colorObj["g"].toInt(),
					colorObj["b"].toInt()),
				(float)obj["lambert"].toDouble(),
				coords3D(
					normalObj["x"].toDouble(),
					normalObj["y"].toDouble(),
					normalObj["z"].toDouble())
				));
		}
	}
}
void Environment::unpackJSON(const string &path)
{
	unpackJSON(QString::fromStdString(path));
}

void Environment::unpackJSON(const char* path)
{
	unpackJSON(QString(path));
}


sphereList Environment::getSpheres() const
{
	return spheres;
}

planeList Environment::getPlanes() const
{
	return planes;
}

lightList Environment::getLights() const
{
	return lights;
}

Camera Environment::getCamera() const
{
	return camera;
}

bool Environment::isEmpty() const
{
	return (!hasLights() && !hasObjects());
}

bool Environment::hasObjects() const
{
	return (hasSpheres() && hasPlanes());
}

bool Environment::hasSpheres() const
{
	return !spheres.empty();
}

bool Environment::hasPlanes() const
{
	return !planes.empty();
}

bool Environment::hasLights() const
{
	return lights.empty();
}
