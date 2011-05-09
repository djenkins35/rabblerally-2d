//
// server.hpp -- async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef B2DRACING_SERVER_H
#define B2DRACING_SERVER_H

#include <set>
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <Box2D/Box2D.h>

#include "Session.h"
#include "GameRoom.h"
#include "../xml/XMLMessage.h"
#include "../xml/LevelLoader.h"
#include "../debug/Debug.h"


using boost::asio::ip::tcp;


namespace B2DRacing {

class Server
{
public:
	bool is_debug;

public:
	Server(boost::asio::io_service& io_service, short port, int update_interval, const bool debug);
	
	
private:
	boost::asio::io_service& io_service_;
	boost::asio::deadline_timer timer1;
	tcp::acceptor acceptor_;
	GameRoom _room;
	XMLMessage _xmessage;
	LevelLoader::LevelLoader _loader;
	int _update_interval;
	b2World* m_world;
	Debug* _pDebugDraw;
	
	void handle_accept(session_ptr new_session, const boost::system::error_code& error);
	void tick(const boost::system::error_code& e);
	void add_time();
	void send(std::string message);
};

};	// namespace B2DRacing

#endif /* B2DRACING_SERVER_H */

