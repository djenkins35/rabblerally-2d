/**
 * GameRoom.cpp
 * ~~~~~~~~~~~~
 *
 */


#include "GameRoom.h"


void GameRoom::join(session_ptr s)
{
	m_sessions.push_back(s);
	std::cout << "GameRoom::join(), adding session"
		<< ", new size: " << m_sessions.size() << std::endl;
}

void GameRoom::leave(session_ptr s)
{
	for (int i = 0, len = m_sessions.size(); i < len; i++)
	{
		if (m_sessions[i] == s) {
		
			m_sessions.erase(m_sessions.begin()+i);
			std::cout << "GameRoom::leave(), erasing session"
				<< ", new size: " << m_sessions.size() << std::endl;
		}
	}
}

void GameRoom::deliver(std::string message)
{
	for (int i = 0, len = m_sessions.size(); i < len; i++)
	{
		m_sessions[i]->send(message);
	}
}

std::vector<std::string> GameRoom::read_messages()
{
	// clear any previous messages
	m_messages.erase(m_messages.begin(), m_messages.end());
	
	for (int i = 0, len = m_sessions.size(); i < len; i++)
	{
		if (m_sessions[i]->data()[0] != '\0')
		{
			char buffer_copy[Session::max_length];
			std::strncpy(buffer_copy, m_sessions[i]->data(), Session::max_length);
			m_messages.push_back(std::string(buffer_copy));
			// clear the buffer
			std::memset(m_sessions[i]->data(), '\0', Session::max_length);
		}
	}
	
	return m_messages;
}

