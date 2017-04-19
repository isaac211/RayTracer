#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "environment.hpp"

TEST_CASE("Test JSON Parser", "[JSON]")
{
	SECTION("scene 0")
	{
		Environment A;
		REQUIRE_NOTHROW(A.unpackJSON("../tests/scene0.json"));

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
			REQUIRE(A.getObjects()[0].getCenter().x == 0);
			REQUIRE(A.getObjects()[0].getCenter().y == 0);
			REQUIRE(A.getObjects()[0].getCenter().z == 5);
			REQUIRE(A.getObjects()[0].getColor().b == 0);
			REQUIRE(A.getObjects()[0].getColor().g == 0);
			REQUIRE(A.getObjects()[0].getColor().r == 255);
			REQUIRE(A.getObjects()[0].getLambert() == 1);
		}
	}

	SECTION("scene 1")
	{
		Environment A;
		REQUIRE_NOTHROW(A.unpackJSON("../tests/scene1.json"));

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
			REQUIRE(A.getObjects()[0].getCenter().x == 0);
			REQUIRE(A.getObjects()[0].getCenter().y == 0);
			REQUIRE(A.getObjects()[0].getCenter().z == 5);
			REQUIRE(A.getObjects()[0].getColor().b == 0);
			REQUIRE(A.getObjects()[0].getColor().g == 0);
			REQUIRE(A.getObjects()[0].getColor().r == 255);
			REQUIRE(A.getObjects()[0].getLambert() == 1);
		}
	}
}
// IMPORTANT NOTE:
// These are just a few examples from my solution and **should be removed**.
// Depending on your code design your class and functions names would differ

/*
#include "geometry.hpp"

TEST_CASE( "Test Basic Geometry: Vec3d ", "[geometry]" ) {

  Vec3d a(2,0,0), b(0,4,0);
  
  REQUIRE(a.x == Approx(2));
  REQUIRE(a.y == Approx(0));
  REQUIRE(a.z == Approx(0));

  REQUIRE(b.x == Approx(0));
  REQUIRE(b.y == Approx(4));
  REQUIRE(b.z == Approx(0));

  double adotb = dot(a,b);
  REQUIRE(adotb == Approx(0));

  Vec3d anorm = norm(a);
  REQUIRE(anorm.x == Approx(1));
  REQUIRE(anorm.y == Approx(0));
  REQUIRE(anorm.z == Approx(0));

  Vec3d bnorm = norm(b);
  REQUIRE(bnorm.x == Approx(0));
  REQUIRE(bnorm.y == Approx(1));
  REQUIRE(bnorm.z == Approx(0));
}
*/