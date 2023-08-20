#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


void	Server::Ping(int socket, vector<string>& arg, Client){
	
	// std::string	message = ":localhost PONG " + arg[0] + "\r\n";
	_clients[socket].sendMessage(PONG(_clients[]));
}