#include <iostream>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> // for closing the connection
#include <string.h> // for memset


int main (int ac, char **av){
	
	if (ac < 3){
		std::cout << "Not enough argument" << std::endl;
		return (-1);
	}

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in my_address = {};

	int portno = std::stoi(av[1]);
	std::string Password = av[2];

	my_adress.sin_familly = AF_INET;
	my_address.sin_port = htons(23);
	my_address.sin_addr.s_addr = INADDR_ANY;

	if(bind(sock, my_address, (struct sockaddr_in *)&my_address, Sizeof(my_address)) < 0){
		std::cer << "Could not bind to socket" << std::endl;
		return (-1);
	}

	listen(socl, 5);

	struct sockaddr_in client_adress = {};
	socklen_t client_size = sizeof(client_adress);
	
	int new_sock = accept(sock, (struct sockaddr_in *)&client_address, &client_size);
	if (new_sock  < 0){
		std::cer << "Could not connect to the client" << std::endl;
		return (-1);
	}

	char buffer[256] {};

	int n = read(new_sock, buffer, 255);
	if (n < 0) {
    	std::cerr << "Error: Could not read from socket" << std::endl;
    	return -1;
	}

	close(sock);
	close(new_sock);

}	