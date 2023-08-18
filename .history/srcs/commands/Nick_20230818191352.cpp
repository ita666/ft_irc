#include "server.hpp"
#include "client.hpp"

bool Server::nicknameAlreadyUsed(string name, Client cl) {
	map<int, Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++) {
		if (it->second.getNickname() == name && it->second.getSocket() != cl.getSocket())
			return true;
	}
	return false;
}

static bool isSpecialChar(char c) {
    const string specialChars = "-[]\\`_^{}|";
    return (specialChars.find(c) != string::npos);
}

static bool isValidNickname(string nickname) {
	if (nickname.length() > 9)
		return false;
	if (nickname[0] == '-' || (nickname[0] >= '0' && nickname[0] <= '9'))
		return false;
	for (int i = 0; i < (int)nickname.length(); i++) {
		if (isalnum(nickname[i]) == false && isSpecialChar(nickname[i]) == false)
			return false;
	}
	return true;
}

void Server::Nick(int socket, vector<string>& arg, Client cl) {
	
	map<int, Client>::iterator it;
	string currentNickname = cl.getNickname();

	stringstream ss;
	string str;
	ss << socket;
	ss >> str;
	string newNickname = arg[0] + str;

	if (arg.size() == 0)
		return cl.sendMessage(ERR_NONICKNAMEGIVEN());
	for (it = _clients.begin(); it != _clients.end(); it++) {
		if (it->second.getNickname() == currentNickname && it->second.getSocket() != cl.getSocket())
			newNickname = it->second.getNickname();
	}
	if (newNickname == currentNickname && _clients[socket].getIsWelcomed() == 1) {
   		cl.sendMessage(ERR_NICKNAMEINUSE(newNickname));
		return ;
	}
	if (isValidNickname(newNickname) == false)
   		return cl.sendMessage(ERR_ERRONEUSNICKNAME(currentNickname));
	if (_clients[socket].getIsWelcomed() == 1){
		string msg = string(":") + _clients[socket].getNickname() + "!" + _clients[socket].getNickname() + "@localhost NICK :" + arg[0] + "\r\n";
		send(socket, msg.c_str(), msg.length(), 0);
	}
	// change value of key of map _stringToClients
	_stringTo
	_clients[socket].setNickname(newNickname);
	_stringToClients[newNickname] = _clients[socket]; // NEED TO CODE OVERLOAD OPERATOR
	string user = _clients[socket].getUser();
	string host = _clients[socket].getHost();
}