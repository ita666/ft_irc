#include "server.hpp"


static void handler(int sig)
{
	(void)sig;
	throw runtime_error("EXIT CTRL + C");
	for (iterator it = _clients.begin(); it != _clients.end();) {
            int clientSocket = it->first;
            close(clientSocket); // Close the client socket
            it = _clients.erase(it); // Remove client from the map
	}
	exit(0);
}

int main (int ac, char **av){

	signal(SIGINT, ircserv::handler);
	signal(SIGPIPE, SIG_IGN);

	if (ac != 3){
		cerr << "not the right argument" << endl;
		return (-1);
	}
	
	try { Server ircserv(av[1], av[2]); }
	catch (const exception &e){cerr << e.what(); }
}