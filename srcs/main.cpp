#include "server.hpp"

int main (int ac, char **av){

	if (ac != 3){
		cerr << "not the right argument" << endl;
		return (-1);
	}
	
	Server ircserv(av[1], av[2]);
}