#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


static bool	isValidMode(string mode){
	(void)mode;
}


//  exemple /MODE NICK -i
void Server::Mode(int socket, vector<string>& arg, Client client){
	(void)socket;

	cout << "Mode-" << arg[0] << "-" << arg[1] << "\n";
	if(arg.size() < 2){
		client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));
		return ;
	}


	if (arg[1].length() != 2){
		cout << "taille\n";
		client.sendMessage(ERR_UNKNOWNMODE(arg[1][0], "Mode"));
		return ;
	}

	switch (arg[1][1]){
		case 'i' :
			if(arg[1][0] == '-'){

			} else if(arg[1][0] == '+') {

			}
		case 't' :
			if(arg[1][0] == '-'){

			} else if(arg[1][0] == '+') {

			}
		case 'k' :
			if(arg[1][0] == '-'){

			} else if(arg[1][0] == '+') {

			}
		case 'o' :
			if(arg[1][0] == '-'){

			} else if(arg[1][0] == '+') {

			}
		case 'l' :
			if(arg[1][0] == '-'){

			} else if(arg[1][0] == '+') {

			}

	}
}