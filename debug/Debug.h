

#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

#include <cstdlib>
#include <Box2D/Box2D.h>
#include "Render.h"


class Debug
{
public:
	bool quit;
	
	
	Debug();
	~Debug();
	bool init();
	void add_b2World(b2World* world);
	void debug_tick();
	void test();
	
	
private:
	DebugDraw _draw;
	b2World* _pWorld;
	
	
	bool init_SDL();
	bool init_opengl();
};


#endif	// DEBUG_DRAW_H
