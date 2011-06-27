//
// server.hpp -- async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#include <cstdlib>
#include "Server.h"

namespace B2DRacing {


using boost::asio::ip::tcp;
using std::cout;
using std::endl;


Server::Server(boost::asio::io_service& io_service, short port, int update_interval,
	const bool debug)
	: io_service_(io_service), acceptor_(io_service, tcp::endpoint(tcp::v4(), port)),
		_room(),
		_update_interval(update_interval),
		timer1(io_service, boost::posix_time::millisec(update_interval)),
		//m_world(0),
		is_debug(debug),
		_world()
{
	session_ptr new_session(new Session(io_service_, _room));
	acceptor_.async_accept(new_session->socket(),
		boost::bind(&Server::handle_accept, this, new_session,
		boost::asio::placeholders::error));
	timer1.async_wait(boost::bind(&Server::tick, this, boost::asio::placeholders::error));
	
	
	if (debug)
	{
		_pDebugDraw = new Debug();
		if (!_pDebugDraw->init())
			cout << "ERROR, server::Constructor, failed to initialize Debug\n";
	}
}

	
void Server::handle_accept(session_ptr new_session, const boost::system::error_code& error)
{
	if (!error)
	{
		new_session->start();
		session_ptr new_session(new Session(io_service_, _room));
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&Server::handle_accept, this, new_session,
				boost::asio::placeholders::error));
	}
}

void Server::tick(const boost::system::error_code& e)
{
	// read messages from clients
	std::vector<std::string> messages = _room.read_messages();
	
	
	for (int i = 0, len = messages.size(); i < len; i++)
	{
		//cout << messages[i] << std::endl;
		_xmessage.parse_string(messages[i]);
		
		if (_xmessage.sAction() == "get_map_list")
		{
			cout << "server::tick(), get map list\n";
			_loader.get_map_list();
		}
		
		if (_xmessage.sAction() == "load_map")
		{
			std::cout << "server::tick(), load map, " << _xmessage.sMap_name() << std::endl;
			_loader.load_file(_xmessage.sMap_name());
			_world.setWorld(_loader.world());
			_world.setPlayerBodies(_loader.player_bodies());
			
			
			// add world pointer to debug draw
			if (is_debug && _pDebugDraw != NULL)
				_pDebugDraw->add_b2World(_loader.world());
			
			
			// send the level xml to each client
			string str;
			_loader.Print(str);
			_room.deliver(str);
			add_time();
			return;
		}
		
		if (_xmessage.sAction() == "shut_down")
		{
			cout << "received shut_down request\n";
			io_service_.stop();
			return;
		}
		
		
		if (_xmessage.sAction() == "player_accelerate")
		{
			double value = atof(_xmessage.sValue().data());
			_world.accelerate_player(0, value);
		}
		
		if (_xmessage.sAction() == "player_steer")
		{
			double value = atof(_xmessage.sValue().data());
			_world.steer_player(0, value);
		}
	}
	
	
	_world.step(_update_interval);
	
	/*
	// send data to clients
	
	if (s.length() > 0)
	{
		//s = "-------begin message--------\n" + s;
		_room.deliver(s);
	}
	*/
	
	
	if (is_debug && _pDebugDraw != NULL)
	{
		_pDebugDraw->debug_tick();
		
		if (_pDebugDraw->quit == true)
		{
			//delete m_world;
			io_service_.stop();
			return;
		}
	}
	
	
	add_time();
}

void Server::add_time()
{
	timer1.expires_at(timer1.expires_at() + boost::posix_time::millisec(_update_interval));
	timer1.async_wait(boost::bind(&Server::tick, this, boost::asio::placeholders::error));
}

void Server::send(std::string message)
{
	_room.deliver(message);
}

}; // namespace B2DRacing
