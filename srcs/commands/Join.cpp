#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"

void	Server::Join(int socket, vector<string>& arg, Client client){
	
	(void)socket;
	cout << "join " << arg[0] << " \n";
	if (_channels.find(arg[0]) == _channels.end()){ // if the chan does not exist create it and add the user and give him the operator right
		_channels[arg[0]] = Channel (arg[0]);

		cout << " join name " << _channels[arg[0]].getName() << " \n";
		_channels[arg[0]].setName(arg[0]);
		_channels[arg[0]].addUser(client.getNickname(), client.getSocket());
		_clients[socket].setUMode();
		cout <<"channel user "<< client.getNickname() << "\n";
	} else {
    if (!_channels[arg[0]].isUserInChannel(client.getUser())) { // if chan already exist and user is not in chan then check if there is a limit and if it's invite only
		if ((_channels[arg[0]].getCMode() & l) == l && _channels[arg[0]].getMap().size() < _channels[arg[0]].getLimit() && _channels[arg[0]].isInviteOnly(client.getNickname())){
        	_channels[arg[0]].addUser(client.getNickname(), client.getSocket());
			_channels[arg[0]].removeGuest(_clients[socket].getNickname());
		}
    } else {
        string errorMsg = ERR_USERONCHANNEL(client.getNickname(), arg[0], client.getNickname());
		send(client.getSocket(), errorMsg.c_str(), errorMsg.length(), 0);
    	}
	}
}