#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


void 	Server::Kick(int socket, vector<string>& arg, Client cl){
	(void)cl;
	string currentClientNickname = _clients[socket].getNickname();
	string currentClientUsername = _clients[socket].getUser();
	string guest = arg[1];
	string channelName = arg[0];
	string comment = " bad boy !";
	Client guestCl = _stringToClients[guest];

	if (_clients[socket].checkRight() == false) // check if the user is an operator
		return _clients[socket].sendMessage(ERR_NOPRIVILEGES(currentClientNickname));
	if (arg.size() < 2) // check if there is enough arguments
		return _clients[socket].sendMessage(ERR_NEEDMOREPARAMS(currentClientNickname, "KICK"));
	if (checkChannelName(channelName) == false) // check if the channel exists
		return _clients[socket].sendMessage(ERR_NOSUCHCHANNEL(currentClientNickname, channelName));
	if (_channels[channelName].isUserInChannel(currentClientNickname) == false) // check if the user is in the channel, if not return an error
		return _clients[socket].sendMessage(ERR_NOTONCHANNEL(currentClientNickname, channelName));
	if (_channels[channelName].isUserInChannel(guest) == false) // check if the guest is in the channel, if yes return an error
		return _clients[socket].sendMessage(ERR_USERNOTINCHANNEL(currentClientNickname, channelName, guest));
	//if (_channels[channelName].findInvited(guest) != guest) { // check if the guest is already invited, if not add him to the invited list
	if (!arg[2].empty()) { comment = arg[2]; }
	_channels[channelName].addGuest(guest);
		//_clients[socket].sendMessage(RPL_INVITING(currentClientNickname, guest, channelName));
	guestCl.sendMessage(KICK(currentClientNickname, _clients[socket].getUser(), channelName, guest, comment));
}


	
	//}