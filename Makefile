
SOURCES = io/GameRoom.cpp io/Session.cpp io/Server.cpp \
	debug/Debug.cpp debug/Render.cpp \
	xml/LevelLoader.cpp xml/XMLMessage.cpp \
	xml/tinyxml/tinyxml.cpp xml/tinyxml/tinystr.cpp \
	xml/tinyxml/tinyxmlerror.cpp xml/tinyxml/tinyxmlparser.cpp \
	Main.cpp
	
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = b2d_racing_server

CC = g++
CFLAGS =-Wall
LDFLAGS =-lBox2D -lboost_system -lSDL -lGL -lGLU
INCLUDES =-I xml/ -I io/ -I debug/

# note, relying on the tinyxml Makefile to actually build the tinyxml object files with
#	-DTIXML_USE_STL for now

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS) $(INCLUDES)

$(OBJECTS) :
#	$(CC) $(CFLAGS) -c $(SOURCES)


.PHONY : clean
clean:
	rm -f *.o io/*.o debug/*.o xml/*.o $(EXECUTABLE)
