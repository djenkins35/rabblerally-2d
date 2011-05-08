//
// Session.h
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef B2DRACING_SESSION_H
#define B2DRACING_SESSION_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "GameRoom.h"


class GameRoom;


using boost::asio::ip::tcp;


class Session : public boost::enable_shared_from_this<Session>
{
public:
	// max buffer read size, surely there's a better way to define this
	const static int max_length = 1024;
	
	
	Session(boost::asio::io_service& io_service, GameRoom& room);
	~Session();
	tcp::socket& socket();
	char * data();
	void start();
	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred);
	void send(std::string message);

private:
	tcp::socket _socket;
	char _data[max_length];	// read/write buffer
	GameRoom& _room;
};


#endif	// B2DRACING_SESSION_H
