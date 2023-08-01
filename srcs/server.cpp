#include "server.hpp"

Server::Server(){}

Server::~Server(){}

void Server::setPort(char *input){
	int port;
	stringstream ss(input);
	if (!(ss >> port) || !ss.eof()){
	throw std::runtime_error("Invalid port number.");
	}
	if (port > 1024 && port < 65536){
		_port = port;
	} else {
		throw std::runtime_error("Port number out of valid range.");
	}
}

Server::Server(char *port, char *pass){

	setPort(port);
	_password = string(pass);
	initServ();
}

void Server::initServ() {
    // Create a socket
    _server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_socket == -1) {
        throw std::runtime_error("Can't create a socket!");
    }
    
    // Bind the socket to a IP / port
    _server_address.sin_family = AF_INET;
    _server_address.sin_port = htons(_port);   // host to network short
    _server_address.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, "0.0.0.0", &_server_address.sin_addr);

    if (bind(_server_socket, (struct sockaddr *)&_server_address, sizeof(_server_address)) == -1) {
        throw std::runtime_error("Can't bind to IP/port");
    }

    // Mark the socket for listening in
    if (listen(_server_socket, SOMAXCONN) == -1) {
        throw std::runtime_error("Can't listen!");
    }

    // Initilize the master set to 0
    FD_ZERO(&_master_set); 
    FD_SET(_server_socket, &_master_set);
}


