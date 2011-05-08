//
// Session.cpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//



#include "Session.h"


using boost::asio::ip::tcp;


Session::Session(boost::asio::io_service& io_service, GameRoom& room)
		: _socket(io_service), _room(room)
	{}
	
Session::~Session()
{
	std::cout << "Session::~Session(), I quit!" << std::endl;
}

tcp::socket& Session::socket()
{
	return _socket;
}

char * Session::data()
{
	return _data;
}

void Session::start()
{
	_room.join(shared_from_this());
	_socket.async_read_some(boost::asio::buffer(_data, max_length),
		boost::bind(&Session::handle_read, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void Session::handle_read(const boost::system::error_code& error,
	size_t bytes_transferred)
{
	if (!error)
	{
		_socket.async_read_some(boost::asio::buffer(_data, max_length),
			boost::bind(&Session::handle_read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		
		//std::cout << "session::handle_read(), value of _data: " << _data << std::endl;
	}
	else
	{
		_room.leave(shared_from_this());
	}
}

void Session::send(std::string message)
{
	boost::asio::async_write(_socket, 
		boost::asio::buffer(message, message.length()),
		boost::bind(&Session::handle_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

