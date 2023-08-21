#include "server.hpp"

Server::Server(): _port(0), _password(""), _server_socket(-1), _server_address() {}

Server::~Server(){
	if (running == true){
		for (map<int, Client>::iterator it = _clients.begin(); it != _clients.end(); it++){
			close(it->first);
		}
		close(_server_socket);
	}
}

void	Server::initMap(){
	
	map<string, void (Server::*)(int, vector<string>&)>::iterator it;
	_commands["CAP"] = &Server::Cap; //adding Cap for the command map
	_commands["OPER"] = &Server::Oper;
	_commands["NICK"] = &Server::Nick;
	_commands["USER"] = &Server::User;
	_commands["JOIN"] = &Server::Join;
	_commands["PART"] = &Server::Part;
	_commands["MODE"] = &Server::Mode;
	_commands["PASS"] = &Server::Pass;
	_commands["INVITE"] = &Server::Invite; 
	_commands["KICK"] = &Server::Kick;
	_commands["PING"] = &Server::Ping;
	_commands["TOPIC"] = &Server::Topic;
	_commands["WHOIS"] = &Server::Whois; 
	_commands["PRIVMSG"] = &Server::Privmsg; 
}

Server::Server(char *port, char *pass){
    _server_socket = -1;
	setPort(port);
    if (pass != NULL) {
        _password = string(pass);
    } else {
        throw runtime_error("Null password provided.");
    }
	initMap();
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
		_stringToClients[_clients[client_socket].getNickname()] = _clients[client_socket];
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
		vector<string> command = getCommand(line);
		handleCommand(socket, command, *this, _clients[socket]);
		}
		welcome(socket);
	}
}

void Server::runServ(){

	int maxFD = _server_socket;
	while (running == false){
		fd_set copy = _master_set;
		if(select(maxFD + 1, &copy, NULL, NULL, NULL) < 0){
			break ;
		}
		for (int i = 0; i <= maxFD; i++){
			if(FD_ISSET(i, &copy)){
				if(i == _server_socket){
					int newSocket = acceptClient();
					if (maxFD < newSocket) { maxFD = newSocket; }
				}else{
					handleClient(i);
				}
			}
		}
	}
}

void Server::User(int socket, vector<string>& arg, Client cl){
	//to do handle error msg
	(void)cl;
	cout << "user test" << arg[0] << '\n';
	_clients[socket].setUser(arg[0]);
	_clients[socket].setHost(arg[2]);
	//std::string errMsg = "461 NICK :Not enough parameters\r\n";
     //   send(socket, errMsg.c_str(), errMsg.length(), 0);
}

bool Server::checkChannelName(string channelName) {
	map<string, Channel>::iterator it;

	for (it = _channels.begin(); it != _channels.end(); it++) {
		if (channelName == it->first) {
			return true;
		}
	}
	return false;
}

vector<string> Server::getCommand(string input_client){

	string tok;
	vector<string> split;

	if (!input_client.empty() && input_client[input_client.size() - 1] == '\r') {
    	input_client.erase(input_client.size() - 1);
	}

	stringstream ss(input_client);
	while(getline(ss, tok, ' ')){ split.push_back(tok);	}
	cout  << "verif" << endl;
	for (size_t i = 0;  i < split.size(); i++){ cout << split[i] << "-"; }
	cout  << "\nend verif" << endl;
	return (split);
}

void	Server::handleCommand(int socket, vector<string> split, Server& server, Client cl){
	
	string errmsg; // variable if the command is not found int the map

	//421	ERR_UNKNOWNCOMMAND	RFC1459	<command> :<reason>	Returned when the given command is unknown to the server (or hidden because of lack of access rights)
	//421 + <command> <msg to explain the error \r\n
	string command = split[0];
	split.erase(split.begin()); // delete first index to keep the args
	//string command = split[0]; //store first index which is the command
	if (_commands.find(command) != _commands.end()){ // to check if the command exist in the map
		 (server.*_commands[command])(socket, split, cl); //this killed me copy paste in chat gpt and learned it yourself

	} else {
		errmsg = "421 " + command + " was not coded =)\r\n"; // /r/n = Carriage Return Line Feed
		send(socket, errmsg.c_str(), errmsg.size(), 0); //c_str to convert to a const
	}
}