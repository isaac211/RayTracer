#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#define RELPATH 0
#include "catch.hpp"

#include "ray_tracer.hpp"

TEST_CASE("Test JSON Parser", "[JSON]")
{
	SECTION("scene 0")
	{
		Environment A;
#if RELPATH == 0
		REQUIRE_NOTHROW(A.unpackJSON("/vagrant/tests/scene0.json"));
#else
		REQUIRE_NOTHROW(A.unpackJSON("../tests/scene0.json"));
#endif

		SECTION("camera")
		{
			REQUIRE(A.getCamera().getCenter().x == 0);
			REQUIRE(A.getCamera().getCenter().y == 0);
			REQUIRE(A.getCamera().getCenter().z == 0);
			REQUIRE(A.getCamera().getFocus() == 10);
			REQUIRE(A.getCamera().getNormal().x == 0);
			REQUIRE(A.getCamera().getNormal().y == 0);
			REQUIRE(A.getCamera().getNormal().z == 1);
			REQUIRE(A.getCamera().getResolution().first == 0.01);
			REQUIRE(A.getCamera().getResolution().second == 0.01);
			REQUIRE(A.getCamera().getSize().first == 256);
			REQUIRE(A.getCamera().getSize().second == 256);
		}


		SECTION("lights")
		{
			REQUIRE(A.getLights()[0].getIntensity() == 1);
			REQUIRE(A.getLights()[0].getLocation().x == 5);
			REQUIRE(A.getLights()[0].getLocation().y == -5);
			REQUIRE(A.getLights()[0].getLocation().z == 0);
		}

		SECTION("objects")
		{
			REQUIRE(A.getSpheres()[0].getCenter().x == 0);
			REQUIRE(A.getSpheres()[0].getCenter().y == 0);
			REQUIRE(A.getSpheres()[0].getCenter().z == 5);
			REQUIRE(A.getSpheres()[0].getColor().b == 0);
			REQUIRE(A.getSpheres()[0].getColor().g == 0);
			REQUIRE(A.getSpheres()[0].getColor().r == 255);
			REQUIRE(A.getSpheres()[0].getLambert() == 1);
			REQUIRE(A.getSpheres()[0].getRadius() == 1);
		}
	}

	SECTION("scene 1")
	{
		Environment A;
#if RELPATH == 0
		REQUIRE_NOTHROW(A.unpackJSON("/vagrant/tests/scene1.json"));
#else
		REQUIRE_NOTHROW(A.unpackJSON("../tests/scene1.json"));
#endif
		SECTION("camera")
		{
			REQUIRE(A.getCamera().getCenter().x == 0);
			REQUIRE(A.getCamera().getCenter().y == 0);
			REQUIRE(A.getCamera().getCenter().z == 0);
			REQUIRE(A.getCamera().getFocus() == 10);
			REQUIRE(A.getCamera().getNormal().x == 0);
			REQUIRE(A.getCamera().getNormal().y == 0);
			REQUIRE(A.getCamera().getNormal().z == 1);
			REQUIRE(A.getCamera().getResolution().first == 0.01);
			REQUIRE(A.getCamera().getResolution().second == 0.01);
			REQUIRE(A.getCamera().getSize().first == 1024);
			REQUIRE(A.getCamera().getSize().second == 1024);
		}


		SECTION("lights")
		{
			REQUIRE(A.getLights()[0].getIntensity() == 1);
			REQUIRE(A.getLights()[0].getLocation().x == 5);
			REQUIRE(A.getLights()[0].getLocation().y == -5);
			REQUIRE(A.getLights()[0].getLocation().z == 0);
		}

		SECTION("objects")
		{
			SECTION("Sphere 1")
			{
				REQUIRE(A.getSpheres()[0].getCenter().x == 0);
				REQUIRE(A.getSpheres()[0].getCenter().y == 0);
				REQUIRE(A.getSpheres()[0].getCenter().z == 5);
				REQUIRE(A.getSpheres()[0].getColor().b == 0);
				REQUIRE(A.getSpheres()[0].getColor().g == 0);
				REQUIRE(A.getSpheres()[0].getColor().r == 255);
				REQUIRE(A.getSpheres()[0].getLambert() == 1);
				REQUIRE(A.getSpheres()[0].getRadius() == 1);
			}

			SECTION("Plane 1")
			{
				REQUIRE(A.getPlanes()[0].getCenter().x == 0);
				REQUIRE(A.getPlanes()[0].getCenter().y == 5);
				REQUIRE(A.getPlanes()[0].getCenter().z == 0);
				REQUIRE(A.getPlanes()[0].getColor().b == 255);
				REQUIRE(A.getPlanes()[0].getColor().g == 255);
				REQUIRE(A.getPlanes()[0].getColor().r == 255);
				REQUIRE(A.getPlanes()[0].getLambert() == 1);
				REQUIRE(A.getPlanes()[0].getNormal().x == 0);
				REQUIRE(A.getPlanes()[0].getNormal().y == -1);
				REQUIRE(A.getPlanes()[0].getNormal().z == 0);

			}
		}
	}

	SECTION("scene 2")
	{
		Environment A;
#if RELPATH == 0
		REQUIRE_NOTHROW(A.unpackJSON("/vagrant/tests/scene2.json"));
#else
		REQUIRE_NOTHROW(A.unpackJSON("../tests/scene2.json"));
#endif
	}

	SECTION("scene 3")
	{
		Environment A;
#if RELPATH == 0
		REQUIRE_THROWS(A.unpackJSON("/vagrant/tests/scene3.json"));
#else
		REQUIRE_THROWS(A.unpackJSON("../tests/scene3.json"));
#endif
	}

	SECTION("scene 4")
	{
		Environment A;
#if RELPATH == 0
		REQUIRE_THROWS(A.unpackJSON("/vagrant/tests/scene4.json"));
#else
		REQUIRE_THROWS(A.unpackJSON("../tests/scene4.json"));
#endif
	}
}

TEST_CASE("Test Math", "[OBJECT][RAY_TRACER]")
{
	SECTION("Vector arithmetic")
	{
		SECTION("Zeroes")
		{
			const coords3D A(0, 0, 0);
			const coords3D B(0, 0, 0);
			const coordsType constant(42);

			REQUIRE(A + B == coords3D(0, 0, 0));
			REQUIRE(A - B == coords3D(0, 0, 0));
			REQUIRE(A * constant == coords3D(0, 0, 0));
			REQUIRE(A / constant == coords3D(0, 0, 0));
		}
		SECTION("A = 3 3 3, B =  5 7 1, constant = 2")
		{
			const coords3D A(3, 3, 3);
			const coords3D B(5, 7, 1);
			const coordsType constant = 2;

			REQUIRE(A + B == coords3D(8, 10, 4));
			REQUIRE(A - B == coords3D(-2, -4, 2));
			REQUIRE((A*constant) == coords3D(6, 6, 6));
			REQUIRE((B*constant) == coords3D(10, 14, 2));
			REQUIRE((A + B) / constant == coords3D(4, 5, 2));
		}
	}
	SECTION("dot product")
	{
		SECTION("Zero vectors")
		{
			const coords3D A(0, 0, 0);
			const coords3D B(0, 0, 0);

			REQUIRE(dotp(A, B) == 0);
		}

		SECTION("A = 1 3 4, B = 4 3 1, dot = 17")
		{
			const coords3D A(1, 3, 4);
			const coords3D B(4, 3, 1);

			REQUIRE(dotp(A, B) == 17);
		}

		SECTION("A = -2 -3 -5, B = 14 -4 -8, dot = 24")
		{
			const coords3D A(-2, -3, -5);
			const coords3D B(14, -4, -8);

			REQUIRE(dotp(A, B) == 24);
		}
	}

	SECTION("Normalize")
	{
		coordsType x(5), y(8), z(13);
		const coordsType mg = std::sqrt(x*x + y*y + z*z);
		REQUIRE(std::floor(mg) == 16);
		REQUIRE(coords3D(x, y, z).normalize() == coords3D(x / mg, y / mg, z / mg));
	}
}

TEST_CASE("Test renders","[SPHERE][PLANE]")
{
	SECTION("scene0")
	{
		Environment A;
		#if RELPATH == 0
		REQUIRE_NOTHROW(A.unpackJSON("/vagrant/tests/scene0.json"));
#else
		REQUIRE_NOTHROW(A.unpackJSON("../tests/scene0.json"));
#endif
		RayTracer scene(A);
		REQUIRE_NOTHROW(scene.printImage("./scene0.png"));
	}

	SECTION("scene1")
	{
		Environment A;
		#if RELPATH == 0
		REQUIRE_NOTHROW(A.unpackJSON("/vagrant/tests/scene1.json"));
#else
		REQUIRE_NOTHROW(A.unpackJSON("../tests/scene1.json"));
#endif
		RayTracer scene(A);
		REQUIRE_NOTHROW(scene.printImage("./scene1.png"));
	}

	SECTION("scene2")
	{
		Environment A;
		#if RELPATH == 0
		REQUIRE_NOTHROW(A.unpackJSON("/vagrant/tests/scene2.json"));
#else
		REQUIRE_NOTHROW(A.unpackJSON("../tests/scene2.json"));
#endif
		RayTracer scene(A);
		REQUIRE_NOTHROW(scene.printImage("./scene2.png"));
	}
}