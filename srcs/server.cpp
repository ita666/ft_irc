#include "server.hpp"
#include "command.hpp"

Server::Server(){}

Server::~Server(){}

Server::Server(char *port, char *pass){

	setPort(port);
	_password = string(pass);
	_commands["NICK"] = &Server::Nick;
	initServ();
	runServ();
}

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

void Server::acceptClient(){
	int client_socket = accept(_server_socket, NULL, NULL);
    if (client_socket < 0) {
        // You might want to handle the error case here
    } else {
        FD_SET(client_socket, &_master_set);
        _client_sockets.push_back(client_socket); // add the new client to your vector
    }
}

void Server::handleClient(int socket){
	char	client_input[2048] = {0};
	int		bytes_received = recv(socket, client_input, sizeof(client_input) - 1, 0);

	if(bytes_received <= 0){
		FD_CLR(socket, &_master_set);
		_client_sockets.erase(remove(_client_sockets.begin(), _client_sockets.end(), socket), _client_sockets.end());
	} else {
		client_input[bytes_received] = '\0'; //make it a proper string
		string message = client_input;
		vector<string> command = getCommand(message);
		handleCommand(socket, command);
		cout << message << endl;

	}
}

void Server::runServ(){
	while (true){
		fd_set copy = _master_set;

		if(select(FD_SETSIZE, & copy, NULL, NULL, NULL) < 0){
			throw std::runtime_error("Select error.");
		}
		for (int i = 0; i < FD_SETSIZE; i++){
			if(FD_ISSET(i, &copy)){
				if(i == _server_socket){
					acceptClient();
				}else{
					handleClient(i);
				}
			}
		}
	}
}

void Server::Nick(int socket, vector<string> arg){
	
	(void)arg;
	std::string errMsg = "461 NICK :Not enough parameters\r\n";
        send(socket, errMsg.c_str(), errMsg.length(), 0);
}