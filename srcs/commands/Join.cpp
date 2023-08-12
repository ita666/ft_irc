#include "server.hpp"
#include "channel.hpp"





void	Server::Join(int socket, vector<string>& arg, Client client){
	
	(void)socket;
	(void)client;
	if (_channels.find(arg[0]) == _channels.end()){
		_channels[arg[0]] = Channel(arg[0]);
		//add the channel to the map, add the user (socket) to the map channel).
	} else {
		//check if the user is already in the channel
		//add user
	}

}