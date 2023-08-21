#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


void	Server::Ping(int socket, vector<string>& arg, Client){
	(void)arg;
	_clients[socket].sendMessage(PONG(_clients[socket].getNickname()));
}