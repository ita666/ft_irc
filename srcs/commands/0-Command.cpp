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