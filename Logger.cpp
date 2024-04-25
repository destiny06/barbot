//==============================================================================
//
//	Logger.cpp:
//
//
//
//
//
//==============================================================================

#include "Logger.hpp"
#include "irclib/IrcMessage.hpp"

//	System dependencies ...
#include <iostream>
#include <chrono>
//	Boost dependencies ...

//	Project dependencies ...

namespace smartass
{
	void logLine(const std::string &type, const std::string &message)
	{
		//
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "The system clock is currently at " << std::ctime(&t_c);

		std::cout << std::ctime(&t_c) << " [" << type << "]:>>>" << message << "<<<" << std::endl;
	}
}
