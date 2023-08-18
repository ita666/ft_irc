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
//	int* users = _channels[channelName].getAllUsers();
	string message = "";
    for (size_t i = 1; i < arg.size(); i++) { 
        message += " " + arg[i];

	}
	//add the verification for user in channel
	// for (size_t i = 0; i < sizeof(users); i++) {
	// 	if (users[i] != socket) {
	// 		string msg = string(":") + cl.getNickname() + "!" + cl.getUser() + "@" + cl.getRealhost() + " PRIVMSG " + channelName + " :" + message + "\r\n";
	// 		send(users[i], msg.c_str(), msg.length(), 0);
	// 	}
	// }
	// delete users;
	(void)socket;
	map<string, Client>::iterator it;
	for (it = _stringToClients.begin(); it != _stringToClients.end(); it++) {
		cout << "nick: " << it->second.getNickname() << endl;}
	if (_stringToClients.find(arg[0]) != _stringToClients.end()) {
		{
			cout << "private message\n" << endl;
			string msg = string(":") + cl.getNickname() + "!" + cl.getUser() + "@" + cl.getRealhost() + " PRIVMSG " + arg[0] + " :" + message + "\r\n";
			send(_stringToClients[arg[0]].getSocket(), msg.c_str(), msg.length(), 0);
		}
	}
}