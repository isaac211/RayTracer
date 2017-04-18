#include "environment.hpp"

Environment::Environment(objectList o, lightList l, Camera c)
	: objects(o), lights(l), camera(c)
{
}

void Environment::unpackJSON(const QString &path)
{
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QJsonParseError JsonParseError;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
	file.close();

	QJsonObject rootObject = jsonDoc.object();
	QJsonArray camArray = rootObject["camera"].toArray();
	QJsonArray lightArray = rootObject["lights"].toArray();
	QJsonArray objArray = rootObject["objects"].toArray();

	foreach (const QJsonValue &value, camArray)
	{
		auto camObj = value.toObject();

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
	}

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

void Environment::printImage()
{

}