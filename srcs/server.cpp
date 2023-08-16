#include "server.hpp"
#include "command.hpp"

static bool running = true;

Server::Server(): _port(0), _password(""), _server_socket(-1), _server_address() {}

Server::~Server(){}

Server::Server(char *port, char *pass){
    _server_socket = -1;
	setPort(port);
    if (pass != NULL) {
        _password = string(pass);
    } else {
        throw runtime_error("Null password provided.");
    }
	_commands["NICK"] = &Server::Nick; // adding Nick for the command map
	_commands["USER"] = &Server::User; //adding User for the command map
	_commands["JOIN"] = &Server::Join; //adding Join for the command map
	_commands["PART"] = &Server::Part; //adding Part for the command map
	_commands["MODE"] = &Server::Mode; //adding Mode for the command map
	_commands["PASS"] = &Server::Pass; //adding Mode for the command map
	_commands["PRIVMSG"] = &Server::Privmsg; //adding Privmsg for the command map

	map<string, void (Server::*)(int, vector<string>&)>::iterator it;
	initServ(); // INIT SERV DUH
	runServ();  // RUN THE SERV =)
}

void Server::setPort(char *input){
	//convert the char * port to an int go cpp0 if you are an idiot
	int port;
	stringstream ss(input);
	if (!(ss >> port) || !ss.eof()){
	throw runtime_error("Invalid port number.");
	}
	if (port > 1024 && port < 65536){
		_port = port;
	} else {
		throw runtime_error("Port number out of valid range.");
	}
}


void Server::initServ() {
    // Create a socket
    _server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_server_socket == -1) {
        throw runtime_error("Can't create a socket!");
    }

	    int opt = 1;
    if (setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        throw runtime_error("setsockopt(SO_REUSEADDR) failed");
    }
    
    // Bind the socket to an IP / port
    _server_address.sin_family = AF_INET;
    _server_address.sin_port = htons(_port);   // host to network short
    _server_address.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, "0.0.0.0", &_server_address.sin_addr);

    if (bind(_server_socket, (struct sockaddr *)&_server_address, sizeof(_server_address)) == -1) {
        throw runtime_error("Can't bind to IP/port");
    }

    // Mark the socket for listening in
    if (listen(_server_socket, SOMAXCONN) == -1) {
        throw runtime_error("Can't listen!");
    }

    // Initilize the master set to 0
    FD_ZERO(&_master_set); 
    FD_SET(_server_socket, &_master_set);
}

int Server::acceptClient(){

	sockaddr_storage client_addr;
	socklen_t addr_len = sizeof(client_addr);

	int client_socket = accept(_server_socket, (struct sockaddr *)&client_addr, &addr_len);
    if (client_socket < 0) {
        throw runtime_error("Cannot accept client !");
    }
	cout << "CLIENT SOCKET= " << client_socket << endl;
        FD_SET(client_socket, &_master_set);
        _clients[client_socket] = Client(client_socket);// add the new client to the map
	return (client_socket);
}

void Server::handleClient(int socket){
	char	client_input[2048] = {0};
	int		bytes_received = recv(socket, client_input, sizeof(client_input) - 1, 0);

	if(bytes_received <= 0){
		FD_CLR(socket, &_master_set);
		_clients.erase(socket);
		close(socket); 
	} else {
		client_input[bytes_received] = '\0'; //make it a proper string
		string message = client_input; //info received from the client to the server
//CAP\r\nLS\r\nPASS 123\r\nNICK yanou\r\nUSER yanou yanou localhost :yanou\r\n
//this is how we receive message from the client uppon connection
		istringstream ss(message); 
		string line;
// at each \n we need to get the command and pass to the next it works uppon connection and after if only one command is sent
		while(getline(ss, line, '\n')){
			if (!line.empty()) {
    			line.erase(line.length());
			}
		//get the command from the line and send it to handle command
		vector<string> command = getCommand(line);
		handleCommand(socket, command, *this, _clients[socket]);
		}
		//cout <<"client " << _clients[socket].getNickname() << " " <<  _clients[socket].getUser() << _clients[socket].getIsWelcomed() << '\n';
		welcome(socket);
		
		//cout << "error\n";
		//cout << message << endl;
	}
}

static void handler(int sig){
	(void)sig;
	running = false;
}

void Server::eraseClient(int socket){
	for (map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		_clients.erase(socket);
		close(socket); 
	}
}

void Server::runServ(){

	// struct timeval timeout;
	// timeout.tv_sec = 5;  // seconds
	int maxFD = _server_socket;
	while (true){
		fd_set copy = _master_set;
		std::cout << "running: " << running << '\n' << std::endl;
		signal(SIGINT, handler);
		std::cout << "running: " << running << '\n' << std::endl;
		if (running == false)
		{
			throw runtime_error("Signal error.");
			eraseClient(_server_socket);
			exit(0);
		}
		//cout  << j++ << "run\n";

		if(select(maxFD + 1, &copy, NULL, NULL, NULL) < 0){
			throw runtime_error("Select error.");
		}
		for (int i = 0; i <= maxFD; i++){
			//cout  << j++ << "run\n";
			if(FD_ISSET(i, &copy)){
				if(i == _server_socket){
					int newSocket = acceptClient();
					if (maxFD < newSocket) { maxFD = newSocket; }
				}else{
					handleClient(i);
				}
			}
		}
		//         // Print active file descriptors
        // cout << "Active file descriptors: ";
        // for(int i = 0; i < FD_SETSIZE; i++) {
        //     if(FD_ISSET(i, &_master_set)) {
        //         cout << i << " ";
        //     }
        // }
        // cout << endl;
	}
}

void Server::User(int socket, vector<string>& arg, Client cl){
	//to do handle error msg
	(void)cl;
	cout << "user " << arg[0] << '\n';
	_clients[socket].setUser(arg[0]);
	//std::string errMsg = "461 NICK :Not enough parameters\r\n";
     //   send(socket, errMsg.c_str(), errMsg.length(), 0);
}

