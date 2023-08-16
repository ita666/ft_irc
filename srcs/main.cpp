#include "server.hpp"

static bool running = true;

static void handler(int sig){
	(void)sig;
	running = false;
	std::cout << "running: " << running << '\n' << std::endl;	
	throw std::runtime_error("SIGINT received");
	exit(0);
}

int main (int ac, char **av){

	signal(SIGINT, handler);

	if (ac != 3){
		cerr << "not the right argument" << endl;
		return (-1);
	}
	
	try { Server ircserv(av[1], av[2]); }
	catch (const exception &e){cerr << e.what(); }
}