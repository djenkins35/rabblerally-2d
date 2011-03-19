
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>



class v_session
{
public:
	enum { max_length = 1024 };
	virtual void send(std::string message) = 0;
	virtual char * data() = 0;
};

typedef boost::shared_ptr<v_session> v_session_ptr;


class game_room
{
public:
	void join(v_session_ptr s)
	{
		m_sessions.push_back(s);
		std::cout << "game_room::join(), adding session"
			<< ", new size: " << m_sessions.size() << std::endl;
	}
	
	void leave(v_session_ptr s)
	{
		for (int i = 0, len = m_sessions.size(); i < len; i++)
		{
			if (m_sessions[i] == s) {
			
				m_sessions.erase(m_sessions.begin()+i);
				std::cout << "game_room::leave(), erasing session"
					<< ", new size: " << m_sessions.size() << std::endl;
			}
		}
	}
	
	void deliver(std::string message)
	{
		for (int i = 0, len = m_sessions.size(); i < len; i++)
		{
			m_sessions[i]->send(message);
		}
	}
	
	std::vector<std::string> read_messages()
	{
		// clear any previous messages
		m_messages.erase(m_messages.begin(), m_messages.end());
		
		for (int i = 0, len = m_sessions.size(); i < len; i++)
		{
			if (m_sessions[i]->data()[0] != '\0')
			{
				char buffer_copy[v_session::max_length];
				std::strncpy(buffer_copy, m_sessions[i]->data(), v_session::max_length);
				m_messages.push_back(std::string(buffer_copy));
				// clear the buffer
				std::memset(m_sessions[i]->data(), '\0', v_session::max_length);
			}
		}
		
		return m_messages;
	}
	
private:
	std::vector<v_session_ptr> m_sessions;
	std::vector<std::string> m_messages;
};

