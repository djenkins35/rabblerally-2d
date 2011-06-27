/**
 * WorldWrapper.cpp
 * ~~~~~~~~~~~~~~~~
 *
 */


#include "WorldWrapper.h"
#include <cmath>
#include <iostream>


namespace B2DRacing {


using std::cout;
using std::endl;


WorldWrapper::WorldWrapper()
{
	//
}

WorldWrapper::~WorldWrapper()
{
	//
}

void WorldWrapper::setWorld(b2World* world)
{
	_world = world;
}

void WorldWrapper::setPlayerBodies(std::vector<b2Body*> player_bodies)
{
	_player_bodies = player_bodies;
}

void WorldWrapper::step(float interval)
{
	if (_world == NULL)
		return;
	
	
	_world->Step(interval / 1000, 6, 2);
	b2Body* b = _world->GetBodyList();
	
	while (b)
	{
		if (b->GetType() != b2_staticBody
			&& b->IsAwake())
		{
			cout << "WorldWrapper::step(), adding new WrapperMessage to _message_queue"
				<< ", _message_queue.size(): " << int(_message_queue.size()) << endl;
			
			// b2Body::GetUserData() returns a void pointer, so cast to whatever is 
			//	stored there to be able to dereference it
			std::string* pStr = static_cast<std::string*>(b->GetUserData());
			
			WrapperMessage wm;
			wm.bodyIdentifier = *pStr;
			wm.x = b->GetWorldCenter().x;
			wm.y = b->GetWorldCenter().y;
			wm.rotation = b->GetAngle() * 180 / M_PI;
			_message_queue.push_back(wm);
		}
		
		b = b->GetNext();
	}
}

void WorldWrapper::accelerate_player(const int playerid, const float value)
{
	if (playerid > _player_bodies.size())
	{
		cout << "playerid: " << playerid << " out of bounds\n";
		return;
	}
	
	
	int force = 100;
	float angle = _player_bodies[playerid]->GetAngle();
	if (value < 0) angle += 3.14159265;
	float dx = -1 * sin(angle) * 100;
	float dy = cos(angle) * 100;
	
	
	_player_bodies[playerid]->ApplyForce(b2Vec2(dx, dy),
		_player_bodies[playerid]->GetWorldCenter());
}

void WorldWrapper::steer_player(const int playerid, const float value)
{
	if (playerid > _player_bodies.size())
	{
		cout << "playerid: " << playerid << " out of bounds\n";
		return;
	}
	
	
	_player_bodies[playerid]->ApplyTorque(-1 * value * 10);
}

int WorldWrapper::getMessageCount()
{
	return _message_queue.size();
}

const WrapperMessage WorldWrapper::popMessage()
{
	if (_message_queue.size() == 0)
		_currentMessage = WrapperMessage();
	
	else
	{
		_currentMessage = _message_queue.front();
		_message_queue.pop_front();
	}
	
	return _currentMessage;
}

}	// namespace B2DRacing

