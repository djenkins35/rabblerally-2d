/**
 * WorldWrapper.h
 * ~~~~~~~~~~~~~~
 *
 */


#ifndef B2DRACING_WORLDWRAPPER_H
#define B2DRACING_WORLDWRAPPER_H

#include <vector>
#include <deque>
#include <string>
#include <Box2D/Box2D.h>


namespace B2DRacing {

struct WrapperMessage
{
	WrapperMessage()	// initialize to default values
	{
		bodyIdentifier = "";
		x = 0.0;
		y = 0.0;
		rotation = 0.0;
	}
	
	// string id from b2Body->GetUserData()
	//	probably should use an index instead of a string
	std::string bodyIdentifier;
	float x;
	float y;
	float rotation;
};

class WorldWrapper
{
public :
	WorldWrapper();
	~WorldWrapper();
	
	void setWorld(b2World* world);
	void setPlayerBodies(std::vector<b2Body*> player_bodies);
	void step(float interval);
	void accelerate_player(const int playerid, const float value);
	void steer_player(const int playerid, const float value);
	int getMessageCount();
	const WrapperMessage popMessage();
	
private :
	b2World* _world;
	std::vector<b2Body*> _player_bodies;
	std::deque<WrapperMessage> _message_queue;
	WrapperMessage _currentMessage;
	
	
};	// class WorldWrapper

};	// namespace B2DRacing

#endif	// B2DRACING_WORLDWRAPPER_H

