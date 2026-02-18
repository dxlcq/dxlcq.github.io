CC = g++
CFLAGS = -std=c++23

all: clean server client

server: Sources/Tool.cpp Sources/SockAddr.cpp Sources/Sock.cpp Sources/Epoll.cpp server.cpp
	$(CC) $(CFLAGS) -o server Sources/Tool.cpp Sources/SockAddr.cpp Sources/Sock.cpp Sources/Epoll.cpp server.cpp

client: Sources/Tool.cpp Sources/SockAddr.cpp Sources/Sock.cpp client.cpp
	$(CC) $(CFLAGS) -o client Sources/Tool.cpp Sources/SockAddr.cpp Sources/Sock.cpp client.cpp

clean:
	rm -f server client