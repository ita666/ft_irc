#include "command.hpp"


Command::Command(){
	//init the map with all the functions;
};

Command::~Command(){};

vector<string> Command::getCommand(string input_client){

	string tok;
	vector<string> split;
	
	stringstream ss(input_client);
	while(getline(ss, tok, ' ')){ split.push_back(tok);	}
	cout  << "verif" << endl;
	for (size_t i = 0;  i < split.size(); i++){ cout << split[i] << endl; }
	return (split);
}

void	Command::handleCommand(int socket, vector<string> split){
	
	string errmsg; // variable if the command is not found int the map

	//421	ERR_UNKNOWNCOMMAND	RFC1459	<command> :<reason>	Returned when the given command is unknown to the server (or hidden because of lack of access rights)
	//421 + <command> <msg to explain the error \r\n
	string command = split[0];
	split.erase(split.begin()); // delete first index to keep the args
	//string command = split[0]; //store first index which is the command
	cout << "handle command\n";

	if (_commands.find(command) != _commands.end()){ // to check if the command exist in the map
		_commands[command](socket, split);
	} else {
		errmsg = "421 " + command + " was not coded =)\r\n"; // /r/n = Carriage Return Line Feed
		send(socket, errmsg.c_str(), errmsg.size(), 0); //c_str to convert to a const
	}

}