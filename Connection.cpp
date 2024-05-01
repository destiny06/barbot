//==============================================================================
//
//	Connection.cpp:
//
//
//
//
//
//==============================================================================

#include "Connection.hpp"

//	System dependencies ...
#include <stdexcept>
#include <thread>
#include <functional>
#include <iostream>

#include <future>
#include <thread>
#include <cstring>
#include <winsock2.h>
#include <ws2tcpip.h>

//	Project dependencies ...
#include "Logger.hpp"

namespace smartass
{
	Connection::Connection()

	{
	}

	Connection::Connection(const std::string &addr, const std::string &port)
		: m_Address(addr), m_Port(port)
	{
		connectChat();
	}

	void Connection::connectChat()
	{
		std::cout << "lol" << m_Address << m_Port;
		struct addrinfo *result = nullptr, *ptr = nullptr, hints;
		// C++

		// Initialize Winsock
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			std::cerr << "WSAStartup failed" << std::endl;
		}

		std::memset(&hints, 0, sizeof(hints));
		hints.ai_family = AF_UNSPEC; // Use IPv4 or IPv6
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		// Resolve the server address and port
		if (getaddrinfo("irc.libera.chat", "6667", &hints, &result) != 0)
		{
			std::cerr << "getaddrinfo failed" << std::endl;
			WSACleanup();
		}

		// Creating socket
		for (ptr = result; ptr != nullptr; ptr = ptr->ai_next)
		{
			sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

			if (sock == INVALID_SOCKET)
			{
				std::cerr << "Socket creation error" << std::endl;
				WSACleanup();
			}

			if (connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen) == SOCKET_ERROR)
			{
				std::cerr << "Socket connection error" << std::endl;
				closesocket(sock);
				sock = INVALID_SOCKET;
				continue;
			}
			break;
		}

		freeaddrinfo(result);

		if (sock == INVALID_SOCKET)
		{
			std::cerr << "Unable to connect to server" << std::endl;
			WSACleanup();
		}

		/*

			 ////// end

			 boost::asio::ip::tcp::resolver resolver(m_Io);
		 boost::asio::ip::tcp::resolver::query query(m_Address, m_Port);
		 boost::system::error_code error = boost::asio::error::host_not_found;

		 auto iter = resolver.resolve(query);
		 decltype(iter) end;

		 while (iter != end)
		 {
			 if (!error)
			 {
				 break;
			 }

			 m_Socket.close();
			 logLine("Info", "Trying to connect: " + m_Address + ":" + m_Port);

			 m_Socket.connect(*iter++, error);

			 if (error)
			 {
				 logLine("ERROR", error.message());
			 }
		 }

		 if (error)
		 {
			 throw std::runtime_error(error.message());
		 }
 */
		logLine("Info", "Connected!");
	}

	void Connection::connectChat(const std::string &addr, const std::string &port)
	{
		m_Address = addr;
		m_Port = port;

		connectChat();
	}

	void Connection::run()
	{
		// std::thread write_handler_thread(m_WriteHandler);

		// Launch asynchronous read operation
		Connection c;
		std::future<void>
			fut = std::async(std::launch::async, &Connection::read, this, sock);

		// m_Io.run();
		// write_handler_thread.join();
	}

	bool Connection::alive() const
	{
		// return m_Socket.is_open();
	}

	void Connection::close()
	{
		logLine("INFO", "Closing connection to " + m_Address + ":" + m_Port);

		/*m_Socket.close();
		m_Io.stop();*/
		closesocket(sock);
	}

	void Connection::write(const std::string &content)
	{
		logLine("WRITE", content);
		// boost::asio::write(m_Socket, boost::asio::buffer(content + "\r\n"));
		send(sock, content.c_str(), 4048, 0);
	}

	void Connection::read(SOCKET socket)
	{
		/*if (error)
		{
			// Got error...
			logLine("ERROR", "Connection said something..." + error.message());

			if (
				error == boost::asio::error::connection_reset ||
				error == boost::asio::error::broken_pipe ||
				error == boost::asio::error::not_found)
			{
				connectChat();
			}
			else
			{
				close();
			}
		}
		else
		{*/

		while (true)
		{
			char buffer[4096] = {0};
			int valread = recv(socket, buffer, 4096, 0);
			if (valread > 0)
			{
				std::cout << "Server response: " << buffer << std::endl;
			}
			else if (valread == 0)
			{
				std::cout << "Connection closed by server" << std::endl;
				break;
			}
			else
			{
				std::cerr << "recv failed with error: " << WSAGetLastError() << std::endl;
				break;
			}
			int count = 0;
			// m_ReadHandler(std::string(m_ReadBuffer.data(), count));
		}
		// async_read();
		// }
	}

	void Connection::setReadHandler(const ReadHandler &handler)
	{
		m_ReadHandler = handler;
	}

	void Connection::setWriteHandler(const WriteHandler &handler)
	{
		m_WriteHandler = handler;
	}

	void Connection::async_read()
	{
		/*m_Socket.async_read_some(boost::asio::buffer(m_ReadBuffer),
								 boost::bind(&Connection::read, this,
											 boost::asio::placeholders::error,
											 boost::asio::placeholders::bytes_transferred));*/
	}
}
