#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


void	Server::Ping(int socket, vector<string>& arg, Client){
	

	cout << "ping\n" << arg[0] << "\n";
	string	message = ":localhost PONG " + arg[0] + "\r\n";
	_clients[socket].sendMessage(PONG(_clients[socket].getNickname()));
	_clients[socket].sendMessage(message);
}