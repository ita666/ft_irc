#include "command.hpp"

// comment
Command::Command(){
	//init the map with all the functions;
};

Command::~Command(){};

vector<string> Command::getCommand(string input_client){

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

void	Command::handleCommand(int socket, vector<string> split, Server& server, Client cl){
	
	string errmsg; // variable if the command is not found int the map

	//421	ERR_UNKNOWNCOMMAND	RFC1459	<command> :<reason>	Returned when the given command is unknown to the server (or hidden because of lack of access rights)
	//421 + <command> <msg to explain the error \r\n
	string command = split[0];
	cout << "SPLIT 000000: " << split[0] << endl;
	cout << "SPLIT SIZE 0000: " << split.size() << endl;
	split.erase(split.begin()); // delete first index to keep the args
	cout << "SPLIT SIZE 1111: " << split.size() << endl;
	cout << "SPLIT 111111: " << split[0] << endl;
	//string command = split[0]; //store first index which is the command
	if (_commands.find(command) != _commands.end()){ // to check if the command exist in the map
		 (server.*_commands[command])(socket, split, cl); //this killed me copy paste in chat gpt and learned it yourself
	} else {
		errmsg = "421 " + command + " was not coded =)\r\n"; // /r/n = Carriage Return Line Feed
		send(socket, errmsg.c_str(), errmsg.size(), 0); //c_str to convert to a const
	}
}