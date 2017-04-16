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

	//TODO read into variables
	//TODO write functions to do the above
}

void Environment::printImage()
{

}