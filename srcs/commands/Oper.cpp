#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"
#include "client.hpp"

void Server::Oper(int socket, vector<string>& arg, Client cl) {
	(void)cl;
	string currentClientNickname = _clients[socket].getNickname();
	string guest = arg[0];
	string pass = arg[1];


	if (arg.size() < 2) // check if there is enough arguments
		return _clients[socket].sendMessage(ERR_NEEDMOREPARAMS(currentClientNickname, "OPER"));
	if (_stringToClients.find(guest) == _stringToClients.end()) // check if the guest exists
		return _clients[socket].sendMessage(ERR_NOSUCHNICK(currentClientNickname, guest));
	if (pass != OPERATOR_PASSWORD) // check if the channel exists
		return _clients[socket].sendMessage(ERR_PASSWDMISMATCH(currentClientNickname));
	if (pass == OPERATOR_PASSWORD) { // check if the guest is already invited, if not add him to the invited list
		_clients[socket].setUMode();
		_clients[socket].sendMessage(RPL_YOUROPER(currentClientNickname));
	}
}