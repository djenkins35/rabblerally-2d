/**
 * LevelLoader.cpp
 * ~~~~~~~~~~~~~~~
 *
 */

 
#include "LevelLoader.h"


using std::string;
using std::cout;
using std::endl;


void LevelLoader::LevelLoader::load_file(string filename)
{
	/*
	_filename = filename;
	cout << "level_loader::load_file(), loading filename: " << filename << endl;
	
	_doc = TiXmlDocument( "testData/" + _filename );
	_doc.LoadFile();
	
	
	if (_doc.Error())
	{
		cout << "ERROR, level_loader::load_file(), error: " << _doc.ErrorDesc() << endl;
		return;
	}
	
	
	// init box2d world
	
	b2Vec2 gravity(0.0f, -10.0f);
	bool doSleep = true;
	m_world = new b2World(gravity, doSleep);
	//m_world = new b2World(LevelLoader::GRAVITY, LevelLoader::DO_SLEEP);
	
	
	// init objects from level file
	
	TiXmlHandle hRoot(&_doc);
	// set scale
	hRoot.FirstChild("map").ToElement()->QueryFloatAttribute("scale", &_scale);
	
	
	// create static box2d objects
	
	float rect_x, rect_y, rect_width, rect_height, rect_rotation;
	string item_id;
	TiXmlElement* pStatics = 
		hRoot.FirstChild("map").FirstChild("static-objects").Child(0).ToElement();
	
	for (pStatics; pStatics; pStatics=pStatics->NextSiblingElement())
	{
		// make a box
		if (pStatics->ValueStr() == "rectangle")
		{
			pStatics->QueryFloatAttribute("x", &rect_x);
			pStatics->QueryFloatAttribute("y", &rect_y);
			pStatics->QueryFloatAttribute("width", &rect_width);
			pStatics->QueryFloatAttribute("height", &rect_height);
			pStatics->QueryFloatAttribute("rotation", &rect_rotation);
			pStatics->QueryStringAttribute("id", &item_id);
			createRectangle(item_id, rect_x, rect_y, rect_width, rect_height,
				rect_rotation, b2_staticBody);
		}
	}
	
	
	// create dynamic bodies
	TiXmlElement* pDynamics =
		hRoot.FirstChild("map").FirstChild("dynamic-objects").Child(0).ToElement();
	
	for (pDynamics; pDynamics; pDynamics=pDynamics->NextSiblingElement())
	{
		if (pDynamics->ValueStr() == "rectangle")
		{
			pDynamics->QueryFloatAttribute("x", &rect_x);
			pDynamics->QueryFloatAttribute("y", &rect_y);
			pDynamics->QueryFloatAttribute("width", &rect_width);
			pDynamics->QueryFloatAttribute("height", &rect_height);
			pDynamics->QueryFloatAttribute("rotation", &rect_rotation);
			pDynamics->QueryStringAttribute("id", &item_id);
			createRectangle(item_id, rect_x, rect_y, rect_width, rect_height,
				rect_rotation, b2_dynamicBody);
		}
	}
	
	// create player objects
	
	TiXmlElement* pPlayers =
		hRoot.FirstChild("map").FirstChild("player-objects").Child(0).ToElement();
	
	for (pPlayers; pPlayers; pPlayers=pPlayers->NextSiblingElement())
	{
		_player_bodies.push_back(createPlayer(pPlayers));
	}
	*/
}

string LevelLoader::LevelLoader::get_map_list()
{
	const string s = "hey";
	
	return s;
}

bool LevelLoader::LevelLoader::Print(string &str)
{
	/*
	if (_doc.Error() && _player_types.size() < 1)
		return false;
	
	
	TiXmlPrinter p;
	p.SetStreamPrinting();
	
	for (int i = 0, len = _player_types.size(); i < len; i++)
	{
		cout << "level_loader::Print(), adding type to xml\n";
		_player_types[i]->Accept(&p);
	}
	
	
	_doc.Accept(&p);
	str = p.Str();
	*/
	return true;
}

b2World* LevelLoader::LevelLoader::world()
{
	return m_world;
}
	
b2Body* LevelLoader::LevelLoader::createRectangle(const string id, const float& x, const float& y,
	const float& w, const float& h, const float& rot, const b2BodyType type)
{
	// Define the body.
	b2BodyDef bd;
	b2PolygonShape ps;
	bd.type = type;
	bd.position.Set(x, y);
	bd.angle = rot * M_PI / 180;
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* pBody = m_world->CreateBody(&bd);

	// Define the ground box shape.
	// The extents are the half-widths of the box.
	ps.SetAsBox(w / 2, h / 2);
	
	// static bodies have '0' density
	if (type == 0)
	{
		// Add the ground fixture to the ground body.
		pBody->CreateFixture(&ps, 0.0f);
	}
	
	// dynamic, or kinematic
	else
	{
		b2FixtureDef fd;
		fd.shape = &ps;
		fd.density = 1.0f;
		fd.friction = 0.3f;
		pBody->CreateFixture(&fd);
	}
	
	string* s = new string(id);
	pBody->SetUserData(s);
	/*
	string sType;
	if (type == 0)
		sType = "b2_staticBody";
	if (type == 1)
		sType = "b2_kinematicBody";
	if (type == 2)
		sType = "b2_dynamicBody";
	
	cout << "level_loader::createRectangle(), id: " << id
		<< ", x/y: " << x << "/" << y
		<< ", w/h: " << w << "/" << h
		<< ", rot: " << rot << ", type: " << sType << endl;
	*/
	
	return pBody;
}

b2Body* LevelLoader::LevelLoader::createPlayer(TiXmlElement* pPlayer)
{
	// get the type description
	
	string sType;
	pPlayer->QueryStringAttribute("type", &sType);
	TiXmlDocument* pCar_type = get_player_type(sType);
	TiXmlHandle hLoop(pCar_type);
	
	
	// debug
	/*
	cout << "pPlayer->Attribute(\"id\"): " << pPlayer->Attribute("id");
	cout << ", type: " << pPlayer->Attribute("type");
	cout << ", position x/y: " << pPlayer->Attribute("x") << ", " 
		<< pPlayer->Attribute("y");
	cout << ", rotation: " << pPlayer->Attribute("rotation") << endl;
	//*/
	/*
	TiXmlPrinter p;
	p.SetStreamPrinting();
	pCar_type->Accept(&p);
	cout << p.Str() << endl;
	//*/
	
	
	// create the bodies
	
	TiXmlElement* pxBody = 
		hLoop.FirstChild("player-object").FirstChild("bodies").Child(0).ToElement();
	TiXmlElement* pShape;
	float rect_x, rect_y, rect_width, rect_height, rect_rotation;
	float body_x, body_y, player_x, player_y;
	string item_id, player_id;
	b2Body* pPlayerBody, *pTemp;
	
	// get the player offset
	pPlayer->QueryFloatAttribute("x", &player_x);
	pPlayer->QueryFloatAttribute("y", &player_y);
	b2Vec2 offset(player_x, player_y);
	pPlayer->QueryStringAttribute("id", &player_id);
	
	
	while (pxBody)
	{
		pShape = pxBody->FirstChildElement("shape");
		pShape->QueryFloatAttribute("x", &rect_x);
		pShape->QueryFloatAttribute("y", &rect_y);
		pShape->QueryFloatAttribute("w", &rect_width);
		pShape->QueryFloatAttribute("h", &rect_height);
		pShape->QueryFloatAttribute("rot", &rect_rotation);
		pxBody->QueryStringAttribute("id", &item_id);
		pxBody->QueryFloatAttribute("x", &body_x);
		pxBody->QueryFloatAttribute("y", &body_y);
		
		/*
		cout << "rect_x, rect_y: " << rect_x << ", " << rect_y
			<< "\nrect_width, rect_height: " << rect_width << ", " << rect_height
			<< "\nrect_rotation, item_id: " << rect_rotation << ", " << item_id << endl;
		//*/
		pTemp = createRectangle(player_id + item_id, rect_x, rect_y, rect_width, rect_height,
			rect_rotation, b2_dynamicBody);
		const b2Vec2 pos = pTemp->GetPosition();
		pTemp->SetTransform(b2Vec2(pos.x + body_x + player_x, pos.y + body_y + player_y), 0);
		//void SetTransform(const b2Vec2& position, float32 angle);
		//const b2Transform& GetTransform() const;
		
		// return the root body
		if (item_id == "root")
			pPlayerBody = pTemp;
		
		pxBody = pxBody->NextSiblingElement();
	}
	
	
	// create the joints
	
	TiXmlElement* pxJoint =
		hLoop.FirstChild("player-object").FirstChild("joints").Child(0).ToElement();
	string joint_type, body_a, body_b;
	float anchor_x, anchor_y;
	b2RevoluteJointDef rjd;
	
	
	while (pxJoint)
	{
		pxJoint->QueryStringAttribute("type", &joint_type);
		pxJoint->QueryStringAttribute("bodyA", &body_a);
		pxJoint->QueryStringAttribute("bodyB", &body_b);
		pxJoint->QueryFloatAttribute("anchorX", &anchor_x);
		pxJoint->QueryFloatAttribute("anchorY", &anchor_y);
		
		// apply the offset
		anchor_x += offset.x;
		anchor_y += offset.y;
		const b2Vec2 anchor(anchor_x, anchor_y);
		
		b2Body* bodyA = getBodyByName(player_id + body_a);
		b2Body* bodyB = getBodyByName(player_id + body_b);
		
		
		if (!bodyA || !bodyB)
		{
			cout << "ERROR: level_loader::createPlayer()"
				<< ", unmatched body identifier\n";
			pxJoint = pxJoint->NextSiblingElement();
			continue;
		}
		
		
		if (joint_type == "b2RevoluteJointDef")
		{
			rjd = createRevoluteJointDef(pxJoint);
			rjd.Initialize(bodyA, bodyB, anchor);
			m_world->CreateJoint(&rjd);
		}
		
		pxJoint = pxJoint->NextSiblingElement();
	}
	
	
	return pPlayerBody;
}

b2RevoluteJointDef LevelLoader::LevelLoader::createRevoluteJointDef(TiXmlElement* pxJoint)
{
	string body_a, body_b, anchor_coords;
	float max_torque, lower_angle, upper_angle;
	
	pxJoint->QueryStringAttribute("bodyA", &body_a);
	pxJoint->QueryStringAttribute("bodyB", &body_b);
	pxJoint->QueryFloatAttribute("maxMotorTorque", &max_torque);
	pxJoint->QueryFloatAttribute("lowerAngle", &lower_angle);
	pxJoint->QueryFloatAttribute("upperAngle", &upper_angle);
	
	/*
	cout << ", body_a: " << body_a
		<< ", body_b: " << body_b
		<< ", max_torque: " << max_torque
		<< ", lower_angle: " << lower_angle
		<< ", upper_angle: " << upper_angle
		<< endl;
	*/
	
	b2RevoluteJointDef jd;
	jd.enableMotor = true;
	jd.maxMotorTorque = max_torque;
	jd.enableLimit = true;
	jd.lowerAngle = lower_angle;
	jd.upperAngle = upper_angle;
	
	
	return jd;
}

/**
 * search for the type in the stored array and load definition file if not found
 */
TiXmlDocument* LevelLoader::LevelLoader::get_player_type(const string &sType)
{
	/*
	TiXmlDocument* pCar_type = NULL;
	string sLoop;
	
	
	for (int i = 0, len = _player_types.size(); i < len; i++)
	{
		TiXmlHandle hLoop(_player_types[i]);
		hLoop.FirstChild("player-object").ToElement()->QueryStringAttribute("type", &sLoop);
		
		if (sLoop == sType)
			return _player_types[i];
	}
	
	
	// load the player-object definition from file
	
	pCar_type = new TiXmlDocument("testData/" + sType + ".xml");
	pCar_type->LoadFile();
	
	if (pCar_type->Error())
	{
		cout << "ERROR, level_loader::createPlayer(), error: " << pCar_type->ErrorDesc() << endl;
		return NULL;
	}
	
	
	// add type to stored array
	
	TiXmlHandle hRoot(pCar_type);
	string sObjType;
	hRoot.FirstChild("player-object").ToElement()->QueryStringAttribute("type", &sObjType);
	cout << "level_loader::createPlayer(), adding object type: " << sObjType << endl;
	_player_types.push_back(pCar_type);
	
	
	return pCar_type;
	*/
	return NULL;
}

b2Body* LevelLoader::LevelLoader::getBodyByName(string name)
{
	b2Body* pB = m_world->GetBodyList();
	string* s;
	
	while (pB)
	{
		s = static_cast<string*>(pB->GetUserData());     
		
		if (*s == name)
			return pB;
		
		pB = pB->GetNext();
	}
	
	
	return NULL;
}

