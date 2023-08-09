#include "server.hpp"
#include "command.hpp"

Server::Server(){}

Server::~Server(){}

Server::Server(char *port, char *pass){
	setPort(port);
    if (pass != NULL) {
        _password = string(pass);
    } else {
        throw runtime_error("Null password provided.");
    }
	//init map commands to do 
	_commands["NICK"] = &Server::Nick; // adding user for the command map
	_commands["USER"] = &Server::User; //adding User for the command map
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
    
    // Bind the socket to a IP / port
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

void Server::acceptClient(){
	int client_socket = accept(_server_socket, NULL, NULL);
    if (client_socket < 0) {
        throw runtime_error("Cannot accept client !");
    } else {
        FD_SET(client_socket, &_master_set);
        _clients[client_socket] = Client(client_socket);// add the new client to the map
    }
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
    			line.erase(line.length() - 1);
			}
		//get the command from the line and send it to handle command
		vector<string> command = getCommand(line);
		handleCommand(socket, command, *this);
		}

		cout <<"client " << _clients[socket].getNickname() << _clients[socket].getUser() << _clients[socket].getIsWelcomed() << '\n';

		if(_clients[socket].isReady() && !_clients[socket].getIsWelcomed()){
		_clients[socket].setIsWelcomed(true);
		string nickname = _clients[socket].getNickname();
		string user = _clients[socket].getUser();
		string host = _clients[socket].getHost();
		string welcome_msg = ":localhost 001 " + nickname + " :Welcome to IRC " + nickname + "!" + user + "@" + host + "\r\n";
		send(socket, welcome_msg.c_str(), welcome_msg.size(), 0);

		}
	}
		//cout << "error\n";
		//cout << message << endl;
}

void Server::runServ(){

	// struct timeval timeout;
	// timeout.tv_sec = 5;  // seconds

	//int j = 0;
	while (true){
		fd_set copy = _master_set;
		//cout  << j++ << "run\n";

		if(select(FD_SETSIZE + 1, &copy, NULL, NULL, NULL) < 0){
			throw std::runtime_error("Select error.");
		}
		for (int i = 0; i <= FD_SETSIZE; i++){
			//cout  << j++ << "run\n";
			if(FD_ISSET(i, &copy)){
				if(i == _server_socket){
					acceptClient();
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

void Server::User(int socket, vector<string>& arg){
	//to do handle error msg
	cout << "user " << arg[0] << '\n';
	_clients[socket].setUser(arg[0]);
	//std::string errMsg = "461 NICK :Not enough parameters\r\n";
     //   send(socket, errMsg.c_str(), errMsg.length(), 0);
}
