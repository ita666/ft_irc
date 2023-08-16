#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"
#include "client.hpp"


void Server::Invite(int socket, vector<string>& arg, Client cl) {
	(void)cl;
	string guest = arg[0];
	string channelName = arg[1];

	if (_clients[socket].checkRight() == false)
		return _clients[socket].sendMessage(ERR_CHANOPRIVSNEEDED(channelName, cl.getNickname()));
	if (arg.size() < 2)
		return _clients[socket].sendMessage(ERR_NEEDMOREPARAMS(cl.getNickname(), "INVITE"));
	if (_channels[channelName].findInvited(guest) != guest) {
		_channels[channelName].addGuest(guest);
	}
	else
		_clients[socket].sendMessage(ERR_USERONCHANNEL(cl.getNickname(), channelName, guest));
}