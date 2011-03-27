CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lBox2D -lboost_system -lSDL -lGL -lGLU -I xml/ -I io/ -I debug/
#LDFLAGS=-lBox2D -lboost_system -lSDL -I xml/ -I io/ -I debug/
SOURCES=b2d_racing_server.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=b2d_racing_server

all:
	g++ -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS)

clean:
	rm -f *.o $(EXECUTABLE)
