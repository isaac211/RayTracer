#include <iostream>
#include <cctype>
#include <string>
#include "ray_tracer.hpp"

using std::cerr;
using std::isdigit;
using std::string;

static inline void printError(const char* error, bool help = true);

int main(int argc, char *argv[])
{
	unsigned int threads = 1;
	string jsonFile, pngFile;
	if (argc < 3 || argc > 5)
	{
		printError("Error: Incorrect number of arguments.");
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; ++i)
	{
		if (argv[i] == "-t")
		{
			if (!isdigit(argv[i+1][0]) || string(argv[i+1]).size() > 1)
			{
				printError("Error: Please specify valid number of threads.");
				return EXIT_FAILURE;
			}
			else
				threads = std::stoi(argv[i+1]);
		}

		if (string(argv[i]).find(".json") != string::npos)
		{
			if (string(argv[i+1]).find(".png") != string::npos)
			{
				jsonFile = argv[i];
				pngFile = argv[i + 1];
			}
		}
	}

	try
	{
		Environment scene;
		scene.unpackJSON(jsonFile);
		RayTracer run(scene);
		run.printImage(pngFile);
	}
	catch (std::exception& error)
	{
		printError(error.what(), false);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static inline void printError(const char* error, bool help)
{
	cerr << error << '\n';
	if (help)
		cerr <<
		"Instructions for use:\n"
		".\vtray.exe [-t <# of threads>] <JSON> <PNG>\n";
}
#else
static inline void printError(const char* error, bool help)
{
	cerr << error << '\n';
	if (help)
		cerr <<
		"Instructions for use:\n"
		"./vtray [-t <# of threads>] <JSON> <PNG>\n";
}
#endif