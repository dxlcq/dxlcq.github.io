CC = g++
CFLAGS = -std=c++23

all: clean server

server: Sources/Tool.cpp Sources/SockAddr.cpp Sources/Sock.cpp Sources/Epoll.cpp server.cpp
	$(CC) $(CFLAGS) -o server Sources/Tool.cpp Sources/SockAddr.cpp Sources/Sock.cpp Sources/Epoll.cpp server.cpp

clean:
	rm -f server