CC=g++
CFLAGS=-c -Wall
LDFLAGS=-lBox2D -lboost_system -I xml/ -I io/
SOURCES=b2d_racing_server.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=b2d_racing_server

all:
	g++ -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS)

clean:
	rm -f *.o $(EXECUTABLE)
