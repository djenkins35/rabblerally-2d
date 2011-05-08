/**
 * GameRoom.h
 * ~~~~~~~~~~~~
 *
 */


#ifndef B2DRACING_GAMEROOM_H
#define B2DRACING_GAMEROOM_H

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "Session.h"


class Session;


typedef boost::shared_ptr<Session> session_ptr;


class GameRoom
{
public:
	void join(session_ptr s);
	void leave(session_ptr s);
	void deliver(std::string message);
	std::vector<std::string> read_messages();
	
private:
	std::vector<session_ptr> m_sessions;
	std::vector<std::string> m_messages;
};


#endif	// B2DRACING_GAMEROOM_H

