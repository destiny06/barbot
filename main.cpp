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

//	Project dependencies ...
#include "Bot.hpp"

using namespace std;

int main(int args, const char *argv[], const char *arge[])
{

	// Getting config file, assuming it's at the same path as the .exe
	string ExecPath(argv[0]);
	auto aPos = ExecPath.find_last_of("/\\");
	string configFilePath(ExecPath.substr(0,aPos)+"\\config.txt");
	
	try
	{
		// Start Smartass Bot with the variables set in the file "config.txt"
		smartass::Bot bot(configFilePath);

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