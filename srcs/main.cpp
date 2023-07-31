#include "server.hpp"


int main(int ac, char **av){
	if (ac < 3){cout << "not enough arguments";};

	std::cout << av[1] << std::endl; 
}