
#include <cstdlib>
#include <iostream>
#include "io/server.hpp"


namespace {

	const int UPDATE_INTERVAL = 1000 / 60; /* fps */
	boost::asio::io_service io_service;
	server* server1;
}


int main(int argc, char* argv[])
{
	using namespace std;
	
	try
	{
		if (argc != 2)
		{
			cerr << "Usage: " << argv[0] << " <port>\n";
			return 1;
		}
		
		
		//initBox2D();
		//m_xmessage = new xml_message();
		
		/// start up io service
		server1 = new server(io_service, atoi(argv[1]), UPDATE_INTERVAL);
		//timer1.async_wait(tick);
		cout << "starting server on port " << argv[1] << endl;
		io_service.run();
		
		
		// When the world destructor is called, all bodies and joints are freed. This can
		// create orphaned pointers, so be careful about your world management.
		//delete m_world;
		//m_world = NULL;
	}
	catch (std::exception& e)
	{
		cerr << "Exception: " << e.what() << "\n";
	}
	
	return 0;
}

