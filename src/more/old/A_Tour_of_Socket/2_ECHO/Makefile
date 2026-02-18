CC = g++
CFLAGS = -std=c++23

all: clean server

server: SOURCES/Tool.cpp SOURCES/SockAddr.cpp SOURCES/Accepter.cpp SOURCES/Event.cpp main.cpp
	$(CC) $(CFLAGS) -o server SOURCES/Tool.cpp SOURCES/SockAddr.cpp SOURCES/Accepter.cpp SOURCES/Event.cpp main.cpp

clean:
	rm -f server