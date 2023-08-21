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

	(void)socket;
	string channelName = arg[0];
	vector<int> users = _channels[channelName].getAllUsers();
	string message = "";

    for (size_t i = 1; i < arg.size(); i++) { 
        message += " " + arg[i];
		cout << "MESSAGE: " << arg[i] << endl;
	}
	//put to check if channel #
	if (channelName[0] == '#') {
		for (size_t i = 0; i < users.size(); i++) {
			if (users[i] != socket) {
		cout << "CALLLED PRIVMSG\n";
				string msg = string(":") + cl.getNickname() + "!" + cl.getUser() + "@localhost PRIVMSG " + channelName + " :" + message + "\r\n";
				send(users[i], msg.c_str(), msg.length(), 0);
			}
		}
		return ;
	}

	string clientReceiverNick = arg[0];
	for (size_t i = 0; i < arg.size(); i++)
		cout << "ARG[" << i << "] " << arg[i] << endl;
	string temp = _stringToClients[clientReceiverNick].getNickname();
	cout << "TEMP= " << temp << endl;
	Client clientReceiver = _stringToClients[clientReceiverNick];
	string msg = string(":") + _clients[socket].getNickname() + "!" + _clients[socket].getUser() + "@" + cl.getRealhost() + " PRIVMSG " + arg[0] + message + "\r\n";
	if (clientReceiverNick == temp)
		return clientReceiver.sendMessage(msg);
}