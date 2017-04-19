#include "environment.hpp"

Environment::Environment(objectList o, lightList l, Camera c)
	: objects(o), lights(l), camera(c)
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
			objects.push_back(Sphere(
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
			objects.push_back(Plane(
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

void Environment::printImage(const QString &path)
{

}

void Environment::printImage(const string &path)
{
	printImage(QString::fromStdString(path));
}

void Environment::printImage(const char* path)
{
	printImage(QString(path));
}

	objectList Environment::getObjects() const
{
	return objects;
}

	lightList Environment::getLights() const
{
	return lights;
}

	Camera Environment::getCamera() const
{
	return camera;
}
