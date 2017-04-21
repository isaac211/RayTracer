#include "environment.hpp"

struct rayType
{
	coords3D origin, destination;
	rayType(coords3D o, coords3D d) : origin(o), destination(o) {}
};

typedef std::vector<std::vector<colorType>> canvasType;
class RayTracer
{
public:
	RayTracer(Environment s);
	void printImage(const QString &path);
	void printImage(const string &path);
	void printImage(const char* path);

private:
	static inline coordsType dotp(const coords3D &a, const coords3D &b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}
	Environment scene;
	canvasType canvas;

};
