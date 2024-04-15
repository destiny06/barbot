//==============================================================================
//
//	IRC.cpp:
//
//
//
//
//
//==============================================================================

#include "IRC.hpp"
#include <iostream>
//	System dependencies ...

//	Boost dependencies ...

//	Ogre dependencies ...

//	Project dependencies ...
#include "IrcParser.hpp"
#include "CommandHandler.hpp"

namespace irclib
{

	IRC::IRC()
		: m_Parser(), m_OnWrite(), writeFn()
	{
		m_Parser.addIrcCommandHandler("PING", std::bind(&IRC::doHandlePing, this, _1));
		m_Parser.addIrcCommandHandler("PRIVMSG", std::bind(&IRC::doHandlePrivmsg, this, _1));
	}

	IRC::~IRC()
	{
	}

	//////////////////////////////////////////////////////////////////////////
	void IRC::nick(const std::string &name)
	{
		writeFn(std::string("NICK ") + name);
	}

	void IRC::user(const std::string &name)
	{
		writeFn(std::string("USER ") + name + " * * :" + name);
	}

	void IRC::join(const std::string &channels)
	{
		std::string cmd = std::string("JOIN ") + channels;

		writeFn(cmd);
	}

	// void IRC::privmsg(const std::string & recipient, const std::string & text)
	//{
	//
	// }
	//
	// void IRC::part(const std::string & channel, const std::string & partmsg)
	//{
	//
	// }
	//
	// void IRC::quit(const std::string & quitmsg)
	//{
	//
	// }

	//////////////////////////////////////////////////////////////////////////
	void IRC::readline(const std::string &line)
	{
		m_Parser.parseLine(line);
	}

	void IRC::addIrcMessageHandler(const IrcMessageHandle &handle)
	{
		m_OnWrite.addHandle(handle);
	}

	void IRC::setWriteFn(const WriteFn &fn)
	{
		writeFn = fn;
	}

	void IRC::doHandlePing(const IrcMessage &original)
	{
		IrcMessage response("PONG", "", {original.trail()});

		writeFn(m_Parser.parseMessage(response));
		//
		// auto to = original.trail();
		//
		// std::string cmd = std::string("PONG ") + to;
		//
		// writeFn(cmd);
		//
		// IrcMessage pongmsg("PONG");
		//
		// std::string msg = m_Parser.parseMessage(pongmsg);
		//
		// writeFn(msg);
	}
	void IRC::doHandlePrivmsg(const IrcMessage &original)
	{

		std::cout << "mdr";
		std::cout << original.command() << std::endl;
		auto lol = std::string("Barbot");
		std::cout << "mdr";

		std::cout << original.trail() << std::endl;

		std::cout << "mdr";
	
		if (original.trail().find(lol) != std::string::npos)
		{
			ParamType lol;
			IrcMessage response("PRIVMSG", "", std::vector<std::string>(original.params()), "Tg je suis pas encore ouvert.");

			writeFn(m_Parser.parseMessage(response));
		}
		else
		{
			std::cout << "nope";
		}

		//
		// auto to = original.trail();
		//
		// std::string cmd = std::string("PONG ") + to;
		//
		// writeFn(cmd);
		//
		// IrcMessage pongmsg("PONG");
		//
		// std::string msg = m_Parser.parseMessage(pongmsg);
		//
		// writeFn(msg);
	}

}
