#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "ray_tracer.hpp"

TEST_CASE("Test JSON Parser", "[JSON]")
{
	SECTION("scene 0")
	{
		Environment A;
		REQUIRE_NOTHROW(A.unpackJSON("/vagrant/tests/scene0.json"));

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
		REQUIRE_NOTHROW(A.unpackJSON("/vagrant/tests/scene1.json"));

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
		REQUIRE_NOTHROW(A.unpackJSON("/vagrant/tests/scene2.json"));
	}

	SECTION("scene 3")
	{
		Environment A;
		REQUIRE_THROWS(A.unpackJSON("/vagrant/tests/scene3.json"));
	}

	SECTION("scene 4")
	{
		Environment A;
		REQUIRE_THROWS(A.unpackJSON("/vagrant/tests/scene4.json"));
	}
}
