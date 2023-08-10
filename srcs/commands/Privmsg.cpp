#include "server.hpp"
#include "command.hpp"

bool Server::isNicknamePresent(string nickName) {
	map<int, Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++) {
		if (it->second.getNickname() == nickName)
			return true;
	}
	return false;
}

void Server::Privmsg(int socket, vector<string> &arg) {

	string message;
	string test;

	if (arg.size() < 2)
		return;
	if (isNicknamePresent(arg[0]) == false)
		return;
	else {
		for (unsigned int i = 0; i < arg.size(); i++)
			message += arg[i];
		message += "\r\n";
		test = ":" + _clients[socket].getNickname() +  " PRIVMSG " + arg[0] + " :" + message;
		std::cout << test << std::endl;
		send(socket, test.c_str(), test.size(), 0);
	}
}