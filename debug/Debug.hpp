

#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

#include <cstdlib>
#include <Box2D/Box2D.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Render.cpp"


using std::cout;
using std::endl;


class Debug
{
public:
	bool quit;
	
	
//- Constructor ------------------------------------------------------------------------------------

	Debug()
		: quit(false), _pWorld(0) {};


//- Destructor -------------------------------------------------------------------------------------
	
	~Debug() {};


//- Interface Methods ------------------------------------------------------------------------------

	bool init()
	{
		if (!init_SDL())
			return false;
		
		if (!init_opengl())
			return false;
		
		
		////////////
		////////////
		
		// Clear the screen before drawing
		glClear( GL_COLOR_BUFFER_BIT );
		glClearColor(0.1, 0.1, 0.1, 0.0);
		
		////////////
		////////////
		
		test();
		
		
		return true;
	}
	
	void add_b2World(b2World* world)
	{
		cout << "Debug::add_b2World, world added\n";
		_pWorld = world;
		_pWorld->SetDebugDraw(&_draw);
	}
	
	void debug_tick()
	{
		Uint8 *keystate;
		
		
		// Update SDL's internal input state information.
		SDL_PumpEvents();
			
		// Grab a snapshot of the keyboard.
		keystate = SDL_GetKeyState(NULL);
			
		// Respond to input.
		if (keystate[SDLK_q] || keystate[SDLK_ESCAPE])
		{
			quit = true;
			return;
		}
		
		
		// draw a new frame
		
		if (_pWorld != NULL)
		{
			glClear( GL_COLOR_BUFFER_BIT );
			glClearColor(0.1, 0.1, 0.1, 0.0);
			
			glPushMatrix();
			glScalef(10.0,10.0,1.0);
			
			uint32 flags = 0;
			flags += 1 * b2DebugDraw::e_shapeBit;
			flags += 1 * b2DebugDraw::e_jointBit;
			flags += 0 * b2DebugDraw::e_aabbBit;
			flags += 0 * b2DebugDraw::e_pairBit;
			flags += 0 * b2DebugDraw::e_centerOfMassBit;
			_draw.SetFlags(flags);
			
			//////
			_pWorld->DrawDebugData();
			//////
			
			glPopMatrix();
			SDL_GL_SwapBuffers();
		}
	}
	
	
	void test()
	{
		glClear( GL_COLOR_BUFFER_BIT );
		glClearColor(0.1, 0.1, 0.1, 0.0);
		
		
		b2Vec2 vertices[3] =
		{
			b2Vec2(0,1),
			b2Vec2(1,1),
			b2Vec2(1,0)
		};
		
		
		glClear( GL_COLOR_BUFFER_BIT );
		glClearColor(0.1, 0.1, 0.1, 0.0);
		glPushMatrix();
		glScalef(28.0,28.0,1.0);
		glTranslatef(0,0,1);
		glRotatef(45 * 180 / M_PI, 0.0, 0.0, 1.0);
		
		/////
		_draw.DrawSolidPolygon(vertices, 3, b2Color(0.5f, 0.5f, 0.3f));
		/////
		glPopMatrix();
		
		
		SDL_GL_SwapBuffers();
	}
	
	
private:
	DebugDraw _draw;
	b2World* _pWorld;
	
	
	bool init_SDL()
	{
		cout << "Debug::init_SDL()\n";
		
		Uint32 subsystem_init = SDL_WasInit(SDL_INIT_VIDEO);
		int error;
		
		if(!subsystem_init&SDL_INIT_VIDEO)
			error = SDL_Init(SDL_INIT_VIDEO);
		
		atexit(SDL_Quit);
		
		if (error != 0)
		{	
			cout << "Debug::init_SDL(), SDL_GetError(): " << SDL_GetError() << endl;
			return false;
		}
		
		
		return true;
	}
	
	bool init_opengl()
	{
		// Create a 640 x 480, 16 bit window with support for OpenGL rendering.
		//	Unfortunately, we won't know whether this is hardware accelerated

		if (SDL_SetVideoMode(640, 480, 0, SDL_OPENGL) == NULL) {

			//printf("Error: %s\n", SDL_GetError());
			//exit(EXIT_FAILURE);
			cout << "Debug::init_opengl(), SDL_GetError(): " << SDL_GetError() << endl;
			return false;
		}
		
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		// Set the colour depth
		//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);	// z-buffer
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		
		
		// Set the window title
		SDL_WM_SetCaption("Box2D Racing Server Debug", "OpenGL");

		// We can now use any OpenGL rendering commands
		glDisable(GL_DEPTH_TEST);	// disable z-buffering
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-133.0, 133.0, -100.0, 100.0);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glPushMatrix();
		
		glClearColor(0.0, 0.0, 0.0, 1.0);  // black
		SDL_GL_SwapBuffers();
		
		
		return true;
	}
};


#endif
