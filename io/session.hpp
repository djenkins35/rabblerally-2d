//
// session.cpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "game_room.hpp"


using boost::asio::ip::tcp;


class session
	: public v_session,
	public boost::enable_shared_from_this<session>
{
public:
	// max_length inherited from v_session
	//enum { max_length = 1024 };
	
	session(boost::asio::io_service& io_service, game_room& room)
		: socket_(io_service), _room(room)
	{
	}
	
	~session()
	{
		std::cout << "session::~session(), I quit!" << std::endl;
	}
	
	tcp::socket& socket()
	{
		return socket_;
	}
	
	char * data()
	{
		return data_;
	}
	
	void start()
	{
		_room.join(shared_from_this());
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
			boost::bind(&session::handle_read, shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error)
		{
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&session::handle_read, shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
			
			//std::cout << "session::handle_read(), value of data_: " << data_ << std::endl;
		}
		else
		{
			_room.leave(shared_from_this());
		}
	}
	
	void send(std::string message)
	{
		boost::asio::async_write(socket_, 
			boost::asio::buffer(message, message.length()),
			boost::bind(&session::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

private:
	tcp::socket socket_;
	char data_[max_length];
	game_room& _room;
};

typedef boost::shared_ptr<session> session_ptr;
