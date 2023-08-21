#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


//  exemple /MODE NICK -i
int	Server::checkFlag(int socket, vector<string>& arg, int i, Client client){
	if (arg[0] == client.getNickname())
		return (i);
	map<string, int> map;
	map = _channels[arg[0]].getMap();
	cout << "looking in arg mode i " << arg[1][i] << "\n";
	int j = i + 1; //to be ahead and avoid the + or -
	cout << "looking in arg mode j " << arg[1][j] << "\n";
	for(; arg[1][j] && arg[1][j] != '+' && arg[1][j] != '-'; j++){
		cout << "looking in arg mode " << arg[1][j] << "\n";
		switch (arg[1][j]){
			case 'i' :
				if(arg[1][i] == '-'){
					_channels[arg[0]].removeCMode('i');
					client.sendMessage(MODE_CHANNEL(_clients[socket].getNickname(), _clients[socket].getUser(), arg[0], " -i"));
					}
				else if(arg[1][i] == '+') {
					_channels[arg[0]].setCMode('i'); 
					client.sendMessage(MODE_CHANNEL(_clients[socket].getNickname(), _clients[socket].getUser(), arg[0], " +i"));
				}
				break;
			case 't' :
				if(arg[1][i] == '-'){
					_channels[arg[0]].removeCMode('t');
					client.sendMessage(MODE_CHANNEL(_clients[socket].getNickname(), _clients[socket].getUser(), arg[0], " -t"));
					}
				else if(arg[1][i] == '+') {
					_channels[arg[0]].setCMode('t');
					client.sendMessage(MODE_CHANNEL(_clients[socket].getNickname(), _clients[socket].getUser(), arg[0], " +t"));
					}
				break;
			case 'k' :
				if(arg[1][i] == '-'){ 
					_channels[arg[0]].removeCMode('k'); 
					_channels[arg[0]].unsetKey();
					client.sendMessage(MODE_CHANNEL(_clients[socket].getNickname(), _clients[socket].getUser(), arg[0], " -k"));
				}
				else if(arg[1][i] == '+') { 
					_channels[arg[0]].setCMode('k');
					_channels[arg[0]].setKey(arg[2]);
					arg.erase(arg.begin() + 2);
					client.sendMessage(MODE_CHANNEL(_clients[socket].getNickname(), _clients[socket].getUser(), arg[0], " +k"));
				}
				break;
			case 'o' :
				if(arg[1][i] == '-'){ 
					if(_clients[socket].checkRight()){
						_clients[map[arg[2]]].unsetUMode();
						client.sendMessage(MODE_USER(_clients[socket].getNickname(), _clients[socket].getUser(), arg[2], " -o"));
					} else {
						cout << "MODE -O CALLED\n";
						_clients[socket].sendMessage(ERR_NOPRIVILEGES(_clients[socket].getNickname())); }
				}
				else if(arg[1][i] == '+') { 
					if(_clients[socket].checkRight()){
						_clients[map[arg[2]]].setUMode();
						client.sendMessage(MODE_USER(_clients[socket].getNickname(), _clients[socket].getUser(), arg[2], " +o"));
					} else {
						cout << "MODE +O CALLED\n";
						_clients[socket].sendMessage(ERR_NOPRIVILEGES(_clients[socket].getNickname()));
					}
					if (_channels[arg[0]].isUserInChannel(arg[2]) == false)
						client.sendMessage(ERR_USERNOTINCHANNEL(client.getNickname(), arg[0], arg[2]));
				}
				arg.erase(arg.begin() + 2);
				break;
			case 'l' :
				if(arg[1][i] == '-'){
					_channels[arg[0]].removeCMode('l');
					client.sendMessage(MODE_CHANNEL(_clients[socket].getNickname(), _clients[socket].getUser(), arg[0], " -l"));	
				}
				else if(arg[1][i] == '+') {
					_channels[arg[0]].setCMode('l');
					_channels[arg[0]].setLimit(arg[2]);
					arg.erase(arg.begin() + 2);
					client.sendMessage(MODE_CHANNEL(_clients[socket].getNickname(), _clients[socket].getUser(), arg[0], " +l"));
				}
				break;
		}
		cout << "\nverif\n" << _channels[arg[0]].getCMode()<<endl;
	}

	return (j-1); //avoid invalid of size

	cout << _channels[arg[0]].getLimit() << endl;
	cout  << "verif bis" << endl;
	for (size_t i = 0;  i < arg.size(); i++){ cout << arg[i] << "-"; }
	cout  << "\nend verif bis" << endl;
}


void Server::invisibleMode(int socket, vector<string>& arg, Client client){
	(void)socket;
	(void)client;
	cout << "invisible mode\n";
	for (size_t i = 0; i < arg.size(); i++){ cout << arg[i] << ","; }
	if (arg.size() < 2){
		client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));
		return ;
	}
	int targetSocket = _stringToClients[arg[0]].getSocket();
	string targetNickname = _stringToClients[arg[0]].getNickname();

	if (arg[0] == targetNickname){
		cout << "invisible mode enabled for target\n";
		_clients[targetSocket].setIMode();
		_stringToClients[targetNickname].setIMode();
		return ;
	}
	
}

void Server::Mode(int socket, vector<string>& arg, Client client){
	(void)socket;
	int i = 0;
	if(arg.size() < 2){
		client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname(), "MODE"));
		return ;
	}
	cout << "\nMODE VERIF\n";
	for (size_t i = 0; i < arg.size(); i++){ cout << arg[i] << ","; }
	for(; arg[1][i]; i++ ){//i is the index of the next sign + or -
		cout << "\nMode\n";
			cout <<  " looking in arg mode " << arg[1][i] << "\n";
		switch (arg[1][i]){
			case '-' :
				i = checkFlag(socket, arg, i, client); 
				cout << "index - = " << i << "\n";
				cout << "\nMode 1\n";
				break;
			case '+' : 
				i = checkFlag(socket, arg, i, client);
				cout << "index + = " << i << "\n";
				cout << "\nMode 2\n";
				break;
			default:
				cout << "\nMode 3\n";
				invisibleMode(socket, arg, client);
				break;
		}
	}

}