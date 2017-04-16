#include "environment.hpp"

Environment::Environment()
{
}

void Environment::unpackJSON(const QString &path)
{
	QFile file(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QJsonParseError JsonParseError;
	QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
	file.close();

	//TODO read into variables
}

void Environment::printImage()
{

}