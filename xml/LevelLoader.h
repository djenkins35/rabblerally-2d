/**
 * LevelLoader.h
 * ~~~~~~~~~~~~~
 *
 */


#ifndef B2DRACING_LEVELLOADER_H
#define B2DRACING_LEVELLOADER_H

#include <cstdlib>
#include <iostream>
#include <Box2D/Box2D.h>
#include <cmath>

#define TIXML_USE_STL
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"


//namespace LevelLoader {

//static const b2Vec2 GRAVITY(0.0f, -10.0f);
//static const bool DO_SLEEP = true;


using std::string;


class LevelLoader
{
public :
	void load_file(string filename);
	string get_map_list();
	bool Print(string &str);
	b2World* world();

	
private :
	string _filename;
	b2World* m_world;
	float _scale;
	//TiXmlDocument _doc;
	//std::vector<TiXmlDocument*> _player_types;
	//std::vector<b2Body*> _player_bodies;
	
	
	b2Body* createRectangle(const string id, const float& x, const float& y,
		const float& w, const float& h, const float& rot, const b2BodyType type);
	b2Body* createPlayer(TiXmlElement* pPlayer);
	b2RevoluteJointDef createRevoluteJointDef(TiXmlElement* pxJoint);
	TiXmlDocument* get_player_type(const string &sType);
	b2Body* getBodyByName(string name);
};

//};	// namespace LevelLoader

#endif	// B2DRACING_LEVELLOADER_H
