#include "server.hpp"

void	Server::Join(int socket, vector<string>& arg){
	
	(void)socket;
	if (_channels.find(arg[0]) == _channels.end()){
		//create the channel 
		//add the channel to the map, add the user (socket) to the map channel).
	} else {
		//check if the user is already in the channel
		//add user
	}

}