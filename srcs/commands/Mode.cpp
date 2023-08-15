#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


// static bool	isValidMode(string mode){
// 	(void)mode;
// }


//  exemple /MODE NICK -i
void	Server::checkFlag(vector<string>& arg, int i, Client client){
	if (arg[0] == client.getNickname())
		return ;
	for(int j = i; arg[1][j] != '+' || arg[1][j] != '-'; j++){
		switch (arg[1][j]){
			case 'i' :
				if(arg[1][i] == '-'){ _channels[arg[0]].removeCMode('i'); }
				else if(arg[1][i] == '+') { _channels[arg[0]].setCMode('i'); }
				break;
			case 't' :
				if(arg[1][i] == '-'){ _channels[arg[0]].removeCMode('t'); }
				else if(arg[1][i] == '+') { _channels[arg[0]].setCMode('t'); }
				break;
			case 'k' :
				if(arg[1][i] == '-'){ _channels[arg[0]].removeCMode('k'); }
				else if(arg[1][i] == '+') { _channels[arg[0]].setCMode('k'); }
				break;
			case 'o' :
				if(arg[1][i] == '-'){ client.removeUMode('o'); }
				else if(arg[1][i] == '+') { client.setUMode('o'); }
				break;
			case 'l' :
				if(arg[1][i] == '-'){ _channels[arg[0]].removeCMode('l');}
				else if(arg[1][i] == '+') { _channels[arg[0]].setCMode('l'); }
				break;
		}
	}
}

void Server::Mode(int socket, vector<string>& arg, Client client){
	(void)socket;

	cout << "Mode-" << arg[0] << "-" << arg[1] << "\n";
	if(arg.size() < 2){
		client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));
		return ;
	}
	//to remove implement a isvalid mode instead
	if (arg[1].length() != 2){
		cout << "taille\n";
		client.sendMessage(ERR_UMODEUNKNOWNFLAG(arg[0]));
		return ;
	}
	for(int i = 0; arg[1][i]; i++ ){
		switch (arg[1][i])
		{
		case '-' :
				checkFlag(arg, i, client);
			break;
		case '+' : 
				checkFlag(arg, i, client);
			break;
		default:
			break;
		}
	}

}