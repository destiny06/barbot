//==============================================================================
//
//	main.cpp:
//
//
//
//
//
//==============================================================================

//	System dependencies ...
#include <iostream>
#include <fstream>
#include <sstream>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
//	Boost dependencies ...

//	Project dependencies ...
#include "Bot.hpp"

using namespace std;

int main(int args, const char *argv[], const char *arge[])
{
	// Unused things

	string lol(argv[0]);
	auto pos = lol.find_last_of("/\\");
	std::string line;

	string second(lol.substr(0,pos)+"\\config.txt");
	
	try
	{
		// Start Smartass Bot with the variables set in the file "config.txt"
		smartass::Bot bot(second);

		// Main execution
		bot.waitForEvents();
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
		std::string keypress;
		std::cin >> keypress;
	}

	return 0;
}