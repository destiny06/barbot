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
#include <regex>

extern int global = 0;

using namespace std;

std::vector<std::string> split(const std::string &str, const std::string &delim)
{
	std::vector<std::string> v;
	for (std::size_t last_pos = 0; last_pos < str.size();)
	{
		std::size_t pos = str.find(delim, last_pos);
		if (pos == str.npos)
			pos = str.size();
		v.push_back(str.substr(last_pos, pos - last_pos));
		last_pos = pos + delim.size();
	}
	return v;
}

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

		IrcMessage response;
		auto lol = std::string("Barbotage");

		std::cout << "Prefix:" << original.origin() << endl;
		std::cout << "Command:" << original.command() << endl;

		for (auto a : original.params())
		{
			std::cout << "Param:" << a << endl;
		}
		std::cout << "Trail:" << original.trail() << endl;

		// ♥
		std::string message = original.trail();
		std::smatch sm;
		std::string orig = original.origin();
		const std::regex dep("mklutra");
		const std::regex coeur("\u2665");

		if (std::regex_search(orig, sm, dep) && original.trail().find("Inventaire") == std::string::npos && original.trail().find("déposé dans le slot") == std::string::npos
		&& original.trail().find("ramassé") == std::string::npos)
		{
			global = 0;
			std::cout << "passing global to 0" << endl;
			string del = "\u2665";

			if (std::regex_search(message, sm, coeur))
			{
				std::cout << "coeur trouvé" << sm.size() << endl;

				std::vector<std::string> words = split(message, del);
				cout << words.size() << endl;
				for (auto a : words)
				{
					const std::regex nombre("[0-9]*");
					auto pos1 = a.rfind("]");
					auto pos2 = a.rfind("[");
					if (pos1 != string::npos && pos2 != string::npos)
					{

						string att = a.substr(pos2 + 1, pos1 - pos2 - 1);
						string digit = "";

						for (auto chdar : att)
						{
							cout << "ascii " << chdar;
							cout << "isdigit" << isdigit(chdar) << endl;
							if (isdigit(chdar))
							{
								digit = digit + chdar;
							}
						}

						response = IrcMessage("PRIVMSG", "", std::vector<std::string>(original.params()), "!pick " + digit);
						writeFn(m_Parser.parseMessage(response));

						/*if (std::regex_search(att, sm, nombre))
						{
							for (auto aa : sm)
							{

								for (auto chdar : aa.str())
								{
									cout << "ascii " << chdar;
									cout << isdigit(chdar) << endl;
								}
								cout << "word" << aa.str() << endl;
								response = IrcMessage("PRIVMSG", "", std::vector<std::string>(original.params()), "!pick " + aa.str());
								writeFn(m_Parser.parseMessage(response));
							}
						}*/
					}
				}
			}
		}

		const std::regex victoire("VICTOIRE. Pendant la bagarre j'ai vendu");

		if (std::regex_search(message, sm, victoire))
		{
			global = 1;
			std::cout << "passing global to 1" << endl;

			response = IrcMessage("PRIVMSG", "", std::vector<std::string>(original.params()), "!loot");
			writeFn(m_Parser.parseMessage(response));
		}

		if (original.trail().find(lol) != std::string::npos)
		{
			string zoologist = "zoologist";
			string destiny = "destiny";


			if (original.trail().find("stock") != std::string::npos)
			{
				response = IrcMessage("PRIVMSG", "", std::vector<std::string>(original.params()), "!inventory");
				writeFn(m_Parser.parseMessage(response));
			}
			else if (original.origin().find("drop") != std::string::npos)
			{
				std::string pattern("sers [0-9]");
				const std::regex rx(pattern);

				std::cout << lol << message;
				std::smatch sm;
				if (std::regex_search(message, sm, rx))
				{
					int number = (sm[0].str()).back() - '0';
					std::cout << "lol" << number;
					response = IrcMessage("PRIVMSG", "", std::vector<std::string>(original.params()), "!drop " + std::to_string(number));
					writeFn(m_Parser.parseMessage(response));
				}
				else
				{
					std::cout << "fail";
				}
			}
			ParamType lol;
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
