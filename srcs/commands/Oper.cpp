#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"
#include "client.hpp"

void Server::Oper(int socket, vector<string>& arg, Client cl) {
	(void)cl;
	string currentClientNickname = _clients[socket].getNickname();
	string guest = arg[0];
	string pass = arg[1];


	if (arg.size() < 2)
		return _clients[socket].sendMessage(ERR_NEEDMOREPARAMS(currentClientNickname, "OPER"));
	if (_stringToClients.find(guest) == _stringToClients.end())
		return _clients[socket].sendMessage(ERR_NOSUCHNICK(currentClientNickname, guest));
	if (pass != OPERATOR_PASSWORD)
		return _clients[socket].sendMessage(ERR_PASSWDMISMATCH(currentClientNickname));
	if (pass == OPERATOR_PASSWORD) {
		_clients[socket].setUMode();
		_clients[socket].sendMessage(RPL_YOUROPER(currentClientNickname));
	}
}