#include "server.hpp"
#include "channel.hpp"






void	Server::Join(int socket, vector<string>& arg, Client client){
	
	(void)socket;
	(void)client;
	if (_channels.find(arg[0]) == _channels.end()){
		_channels[arg[0]] = Channel (arg[0]);
		_channels[arg[0]].addUser(client.getUser(), client.getSocket());
		//add the channel to the map, add the user (socket) to the map channel).
	} else {
    if (!_channels[arg[0]].isUserInChannel(client.getUser())) {
        _channels[arg[0]].addUser(client.getUser(), client.getSocket());
    } else {
        string errorMsg = ERR_USERONCHANNEL(client.getUser(), arg[0], client.getUser());
		send(client.getSocket(), errorMsg.c_str(), errorMsg.length(), 0);
    	}
	}
}