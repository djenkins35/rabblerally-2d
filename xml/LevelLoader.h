/**
 * LevelLoader.h
 * ~~~~~~~~~~~~~
 *
 */


#ifndef B2DRACING_LEVELLOADER_H
#define B2DRACING_LEVELLOADER_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <Box2D/Box2D.h>

#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"


//namespace LevelLoader {

//static const b2Vec2 GRAVITY(0.0f, -10.0f);
//static const bool DO_SLEEP = true;


using std::string;
using std::vector;


class LevelLoader
{
public :
	static const bool DO_SLEEP = true;
	
	void load_file(string filename);
	string get_map_list();
	bool Print(string &str);
	b2World* world();
	void accelerate_player(const int playerid, const float value);
	void steer_player(const int playerid, const float value);
	
	
private :
	string _filename;
	b2World* m_world;
	float _scale;
	TiXmlDocument _doc;
	vector<TiXmlDocument*> _player_types;
	vector<b2Body*> _player_bodies;
	
	
	b2Body* createRectangle(const string id, const float& x, const float& y,
		const float& w, const float& h, const float& rot, const b2BodyType type);
	b2Body* createPlayer(TiXmlElement* pPlayer);
	b2RevoluteJointDef createRevoluteJointDef(TiXmlElement* pxJoint);
	TiXmlDocument* get_player_type(const string &sType);
	b2Body* getBodyByName(string name);
};

//};	// namespace LevelLoader

#endif	// B2DRACING_LEVELLOADER_H

