#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"
#include "client.hpp"


void Server::Invite(int socket, vector<string>& arg, Client cl) {
	(void)cl;
	string guest = arg[0];
	string channelName = arg[1];

	if (_channels[channelName].findInvited(guest) != guest) {
		_channels[channelName].addGuest(guest);
	}
	else
		_clients[socket].sendMessage(ERR_ALREADYREGISTRED(guest));
}