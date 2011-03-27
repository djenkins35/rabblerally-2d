
#include <cstdlib>
#include <iostream>
#include "io/server.hpp"


namespace {

	const int UPDATE_INTERVAL = 1000 / 60; /* fps */
	boost::asio::io_service io_service;
	server* server1;
	const bool DEBUG_BUILD = true;
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
		
		
		/// start up io service
		server1 = new server(io_service, atoi(argv[1]), UPDATE_INTERVAL, DEBUG_BUILD);
		cout << "starting server on port " << argv[1] << endl;
		io_service.run();
	}
	catch (std::exception& e)
	{
		cerr << "Exception: " << e.what() << "\n";
	}
	
	return 0;
}

