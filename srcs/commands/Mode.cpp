#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


// static bool	isValidMode(string mode){
// 	(void)mode;
// }


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
		client.sendMessage(ERR_UMODEUNKNOWNFLAG(arg[0]));
		return ;
	}

	switch (arg[1][1]){
		case 'i' :
			if(arg[1][0] == '-'){ client.removeMode('i'); }
			else if(arg[1][0] == '+') { client.setMode('i'); }
			break;
		case 't' :
			if(arg[1][0] == '-'){ client.removeMode('t'); }
			else if(arg[1][0] == '+') { client.setMode('t'); }
			break;
		case 'k' :
			if(arg[1][0] == '-'){ client.removeMode('k'); }
			else if(arg[1][0] == '+') { client.setMode('k'); }
			break;
		case 'o' :
			if(arg[1][0] == '-'){ client.removeMode('o'); }
			else if(arg[1][0] == '+') { client.setMode('o'); }
			break;
		case 'l' :
			if(arg[1][0] == '-'){ client.removeMode('l');}
			else if(arg[1][0] == '+') { client.setMode('l'); }
			break;
	}
}