#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


void	Server::Ping(int socket, vector<string>& arg, Client){
	string	message = ":" + _clients[socket].getRealhost() + " PONG " + arg[0] + "\r\n";
	_clients[socket].sendMessage(message);
}