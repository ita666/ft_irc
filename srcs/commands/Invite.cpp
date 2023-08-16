#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"
#include "client.hpp"


void Server::Invite(int socket, vector<string>& arg, Client cl) {
	(void)cl;
	string currentClientNickname = _clients[socket].getNickname();
	string currentClientUsername = _clients[socket].getUser();
	string guest = arg[0];
	string channelName = arg[1];
	Client guestCl = _stringToClients[guest];

	if (_clients[socket].checkRight() == false)
		return _clients[socket].sendMessage(ERR_CHANOPRIVSNEEDED(channelName, cl.getNickname()));
	if (arg.size() < 2)
		return _clients[socket].sendMessage(ERR_NEEDMOREPARAMS(currentClientNickname, "INVITE"));
	if (checkChannelName(channelName) == false)
		return _clients[socket].sendMessage(ERR_NOSUCHCHANNEL(currentClientNickname, channelName));
	if (_channels[channelName].isUserInChannel(currentClientNickname) == false)
		return _clients[socket].sendMessage(ERR_NOTONCHANNEL(currentClientNickname, channelName));
	if (_channels[channelName].isUserInChannel(guest) == false)
		return _clients[socket].sendMessage(ERR_USERNOTINCHANNEL(currentClientNickname, channelName, guest));
	if (_channels[channelName].findInvited(guest) != guest) {
		_channels[channelName].addGuest(guest);
		_clients[socket].sendMessage(RPL_INVITING(currentClientNickname, guest, channelName));
		guestCl.sendMessage(INVITE(currentClientNickname, _clients[socket].getUser(), guest, channelName));
	}
}