#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


// static bool	isValidMode(string mode){
// 	(void)mode;
// }


//  exemple /MODE NICK -i
void	Server::checkFlag(int socket, vector<string>& arg, int i, Client client){
	if (arg[0] == client.getNickname())
		return ;
	map<string, int> map;
	map = _channels[arg[0]].getMap();

	cout << " ARG 2222222 " << arg[2] << endl;
	cout << "CHANNEL = " << arg[0] << endl;
	cout << "SOCKET = " << _channels[arg[0]].getMap()[arg[2]] << endl;
	
	for(int j = i; arg[1][j] && (arg[1][j] != '+' || arg[1][j] != '-'); j++){
		switch (arg[1][j]){
			case 'i' :
				if(arg[1][i] == '-'){ _channels[arg[0]].removeCMode('i'); }
				else if(arg[1][i] == '+') { _channels[arg[0]].setCMode('i'); }
				cout << "Mode i\n";
				break;
			case 't' :
				if(arg[1][i] == '-'){ _channels[arg[0]].removeCMode('t'); }
				else if(arg[1][i] == '+') { _channels[arg[0]].setCMode('t'); }
				cout << "Mode t\n";
				break;
			case 'k' :
				if(arg[1][i] == '-'){ _channels[arg[0]].removeCMode('k'); }
				else if(arg[1][i] == '+') { _channels[arg[0]].setCMode('k'); }
				cout << "Mode k\n";
				break;
			case 'o' :
				if(arg[1][i] == '-'){ _clients[socket].removeUMode(&_clients[map[arg[2]]]); }
				else if(arg[1][i] == '+') { _clients[socket].giveOMode(&_clients[map[arg[2]]]); }
				cout << "Mode o\n";
				break;
			case 'l' :
				if(arg[1][i] == '-'){ _channels[arg[0]].removeCMode('l');}
				else if(arg[1][i] == '+') { _channels[arg[0]].setCMode('l'); }
				cout << "Mode l\n";
				break;
		}
	}
}

void Server::Mode(int socket, vector<string>& arg, Client client){
	(void)socket;

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
	cout << "Mode\n";
		switch (arg[1][i])
		{
		case '-' :
			checkFlag(socket, arg, i, client);
			cout << "Mode 1\n";
			break;
		case '+' : 
			checkFlag(socket, arg, i, client);
			cout << "Mode 2\n";
			break;
		default:
			cout << "Mode 3\n";
			break;
		}
	}

}