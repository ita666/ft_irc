#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <string>

int main(int ac, char **av)
{
	if (ac < 3)
	{
		std::cout << "not enough argument" << std::endl;
	}
	// create a socket
	int listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening < 0)
	{
		std::cerr << "can't create socket" << std::endl;
		return -1;
	}
	// bind the socket to an ip / port
	struct sockaddr_in hint = {};
	hint.sin_family = AF_INET;
	hint.sin_port = htons(540000);
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

	if (bind(listening, AF_INET, &hint, sizeof(hint)) < 0)
	{
		std::cerr "Can't bid to ip port" < std::endl;
		return -1;
	}

	// Mark the socket for listening in
	if (listen(listening, SOMAXCONN) < 0)
	{
		std::cerr << "Can't listen" << std::endl;
		return -1;
	}

	// Accept a call
	struct sockaddr_in client;
	socklen_t clientsize;
	char host[NI_MAXHOST];

	// close the listening socket
	// while receiving - display message, echo message
	// close the socket
	// terminate

	return (0);
}