#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"


void 	Server::Kick(int socket, vector<string>& arg, Client cl){
	(void)cl;
	
	if (arg.empty()){
		return _clients[socket].sendMessage(ERR_NEEDMOREPARAMS(_clients[socket].getNickname(), "KICK"));
	}
	
	string currentClientNickname = _clients[socket].getNickname();
	string currentClientUsername = _clients[socket].getUser();
	string guest = arg[1];
	string channelName = arg[0];
	string comment = ":bad boy !";
	Client guestCl = _stringToClients[guest];


	// cout << arg.size() << "\n";
	// cout << "guest " << arg[1] << "\n";
	// cout  << "channelname " << arg[0] << "\n";
	// cout << "current client nick " << currentClientNickname << "\n";
	// cout << "current client user " << currentClientUsername << "\n";
	// cout << "current client right "<< _clients[socket].checkRight() << "\n";
	// cout << "current hostname " << _clients[socket].getRealhost() << "\n";

	if (_clients[socket].checkRight() == false) // check if the user is an operator
	{
		cout << "KICK CALLED\n";
		return _clients[socket].sendMessage(ERR_NOPRIVILEGES(currentClientNickname));
	}
	if (arg.size() < 2) // check if there is enough arguments
		{
			cout << "not enough arguments\n";
			return _clients[socket].sendMessage(ERR_NEEDMOREPARAMS(currentClientNickname, "/KICK"));
			}
	if (checkChannelName(channelName) == false) // check if the channel exists
		{
			cout << "channel doesn't exist\n";
			return _clients[socket].sendMessage(ERR_NOSUCHCHANNEL(currentClientNickname, channelName));
		}
	if (_channels[channelName].isUserInChannel(currentClientNickname) == false) // check if the user is in the channel, if not return an error
		{
			cout << "user not in channel\n";
			return _clients[socket].sendMessage(ERR_NOTONCHANNEL(currentClientNickname, channelName));
		}
	cout << "isUser = " << _channels[channelName].isUserInChannel(guest) << "\n";
	if (_channels[channelName].isUserInChannel(guest) == false) // check if the guest is in the channel, if yes return an error
		{
			cout << "guest not in channel\n";
		return _clients[socket].sendMessage(ERR_USERNOTINCHANNEL(currentClientNickname, channelName, guest));
		}
	//if (_channels[channelName].findInvited(guest) != guest) { // check if the guest is already invited, if not add him to the invited list
	if (arg[2].length() !=  1) { comment = arg[2]; }

	// string msg = ":" + currentClientNickname + "!~" + currentClientUsername + "@" + _clients[socket].getRealhost() + " KICK " + arg[0] + " " + arg[1] + "\r\n";
	guestCl.sendMessage(KICK(currentClientNickname, _clients[socket].getUser(), channelName, guest, comment));
	_channels[channelName].removeUser(guest, guestCl.getSocket());
	_channels[channelName].broadcast(KICK(currentClientNickname, _clients[socket].getUser(), channelName, guest, comment));
	return;
}
