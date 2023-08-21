#include "server.hpp"

bool running = false;

static void handler(int sig){
	(void)sig;
	running = true;
	cout << BRED << "CTRL + C received" << RESET << endl;
}

int main (int ac, char **av){

	if (ac != 3){
		cerr << "not the right argument" << endl;
		return (-1);
	}
	signal(SIGINT, handler);
	signal(SIGTSTP, SIG_IGN);
	try { Server ircserv(av[1], av[2]);}
	catch (const exception &e){cerr << e.what(); }
}