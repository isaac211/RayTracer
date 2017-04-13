#include <iostream>
#include <cctype>
#include <string>
using std::cerr;
using std::isdigit;
using std::string;

static inline void printError(const char* error, bool help = true);

int main(int argc, char *argv[])
{
	unsigned int threads = 1;
	if (argc < 3 || argc > 5)
	{
		printError("Error: Incorrect number of arguments.");
		return EXIT_FAILURE;
	}
	else if (argv[1] == "-t")
	{
		if (!isdigit(argv[2][0]) || string(argv[2]).size() > 1)
		{
			printError("Error: Please specify valid number of threads.");
			return EXIT_FAILURE;
		}
		else
			threads = std::stoi(argv[2]);
	}
	try
	{
		//TODO call other functions
	}
	catch (std::exception& error)
	{
		printError(error.what(), false);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

static inline void printError(const char* error, bool help)
{
	cerr << error << '\n';
	if (help)
		cerr <<
		"Instructions for use:\n"
		"Linux:\n"
		"./vtray [-t <# of threads>] <JSON> <PNG>\n"
		"Windows:\n"
		".\vtray.exe [-t <# of threads>] <JSON> <PNG>\n";
}