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
	if (rootObject["camera"].isUndefined()) //throw if no camera
		throw std::runtime_error("Error: Missing camera!");
	QJsonObject camObj = rootObject["camera"].toObject();
	QJsonArray lightArray = rootObject["lights"].toArray();
	QJsonArray objArray = rootObject["objects"].toArray();

	//camera error checking
	if (camObj["center"].isUndefined()
		|| camObj["size"].isUndefined()
		|| camObj["resolution"].isUndefined()
		|| camObj["normal"].isUndefined()
		)
		throw std::runtime_error("Error: Missing camera values!");

	//camera parsing
	auto centerObj = camObj["center"].toObject();
	auto sizeObj = camObj["size"].toArray();
	auto resolObj = camObj["resolution"].toArray();
	auto normalObj = camObj["normal"].toObject();

	//camera sub value error checking
	if (
		centerObj["x"].isUndefined()
		|| centerObj["y"].isUndefined()
		|| centerObj["z"].isUndefined()
		)
		throw std::runtime_error("Error: Missing camera location coordinates!");

	//Missing or negative size
	if (sizeObj[0].isUndefined() || sizeObj[1].isUndefined()
		|| sizeObj[0].toInt() < 0 || sizeObj[1].toInt() < 0
		|| notInt(sizeObj[0].toString()) || notInt(sizeObj[1].toString())
		)
		throw std::runtime_error("Error: Invalid camera size!");

	//Missing or negative resolution
	if (resolObj[0].isUndefined() || resolObj[1].isUndefined()
		|| resolObj[0].toDouble() < 0 || resolObj[0].toDouble() < 0)
		throw std::runtime_error("Error: Invalid camera resolution!");

	if (normalObj["x"].isUndefined()
		|| normalObj["y"].isUndefined()
		|| normalObj["z"].isUndefined()
		)
		throw std::runtime_error("Error: Missing camera normal values!");

	if (camObj["focus"].isUndefined())
		throw std::runtime_error("Error: Missing camera focus!");

	//parsing for camera sub values
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

		//throw if no location
		if (lightObj["location"].isUndefined())
			throw std::runtime_error("Error: Missing light location!");

		//store location
		auto locObj = lightObj["location"].toObject();

		//throw if no location coordinates
		if (locObj["x"].isUndefined()
			|| locObj["y"].isUndefined()
			|| locObj["z"].isUndefined()
			|| notDouble(locObj["x"].toString())
			|| notDouble(locObj["y"].toString())
			|| notDouble(locObj["z"].toString())
				)
			throw std::runtime_error("Error: Missing light location values!");

		//throw if missing or negative intensity
		if (lightObj["intensity"].isUndefined()
			|| lightObj["intensity"].toDouble() < 0
			|| notDouble(lightObj["intensity"].toString()))
			throw std::runtime_error("Error: Invalid light intensity!");

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

		//throw if missing or invalid center, color, or type
		if (obj["center"].isUndefined()
			|| obj["color"].isUndefined()
			|| obj["type"].isUndefined()
			|| obj["lambert"].isUndefined()
			|| obj["lambert"].toDouble() < 0.
			|| obj["lambert"].toDouble() > 1.
			|| notDouble(obj["lambert"].toString())
			)
			throw std::runtime_error(
				"Error: Check object has center, color, lambert, and type!");

		auto centerObj = obj["center"].toObject();
		auto colorObj = obj["color"].toObject();

		//throw if center and color do not have values
		if (centerObj["x"].isUndefined()
			|| centerObj["y"].isUndefined()
			|| centerObj["z"].isUndefined()
			|| notDouble(centerObj["x"].toString())
			|| notDouble(centerObj["y"].toString())
			|| notDouble(centerObj["z"].toString()))
			throw std::runtime_error("Error: Missing object center (XYZ)!");

		if (colorObj["r"].isUndefined()
			|| colorObj["g"].isUndefined()
			|| colorObj["b"].isUndefined()
			|| notInt(colorObj["r"].toString())
			|| notInt(colorObj["g"].toString())
			|| notInt(colorObj["b"].toString())
			)
			throw std::runtime_error("Error: Missing object colors (RGB)!");

		if (obj["type"].toString() == "sphere")
		{
			//throw if missing or negative radius
			if (obj["radius"].isUndefined()
				|| obj["radius"].toDouble() < 0
				|| notDouble(obj["radius"].toString())
				)
				throw std::runtime_error("Error: Invalid sphere radius!");
			
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
			//throw if no normal
			if (obj["normal"].isUndefined())
				throw std::runtime_error("Error: Missing plane normal!");

			auto normalObj = obj["normal"].toObject();

			//throw if no normal coordinates
			if (normalObj["x"].isUndefined()
				|| normalObj["y"].isUndefined()
				|| normalObj["z"].isUndefined()
				|| notDouble(normalObj["x"].toString())
				|| notDouble(normalObj["y"].toString())
				|| notDouble(normalObj["z"].toString()))
				throw std::runtime_error("Error: Missing plane normal (XYZ)!");

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
