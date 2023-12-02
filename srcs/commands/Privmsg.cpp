#include "server.hpp"

bool Server::isNicknamePresent(string nickName) {
	map<int, Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++) {
		if (it->second.getNickname() == nickName)
			return true;
	}
	return false;
}

void Server::Privmsg(int socket, vector<string> &arg, Client cl) {

	string channelName = arg[0];
	vector<int> users = _channels[channelName].getAllUsers();
	string message = "";

	//put to check if channel #
	 for (size_t i = 1; i < arg.size(); i++) { 
        message += " " + arg[i];
	}
	if (channelName[0] == '#') {
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i] != socket) {
				string msg = string(":") + cl.getNickname() + "!" + cl.getUser() + "@localhost PRIVMSG " + channelName + " :" + message + "\r\n";
				send(users[i], msg.c_str(), msg.length(), 0);
			}
		}
		return ;
	}

	string clientReceiverNick = arg[0];
	string temp = _stringToClients[clientReceiverNick].getNickname();
	Client clientReceiver = _stringToClients[clientReceiverNick];
	string msg = string(":") + _clients[socket].getNickname() + "!" + _clients[socket].getUser() + "@" + cl.getRealhost() + " PRIVMSG " + arg[0] + message + "\r\n";
	if (clientReceiverNick == temp)
		return clientReceiver.sendMessage(msg);
}