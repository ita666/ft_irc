#include "server.hpp"
#include "command.hpp"
#include "client.hpp"

// comment

bool Server::nicknameAlreadyUsed(string name, Client cl) {
	map<int, Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++) {
		cout << "nickname used" << it->second.getNickname() << " \n";
		if (it->second.getNickname() == name && it->second.getSocket() != cl.getSocket())
			return true;
	}
	return false;
}

static bool isSpecialChar(char c)
{
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

void Server::Nick(int socket, vector<string>& arg, Client cl){
	
	map<int, Client>::iterator it;
	string currentNickname = cl.getNickname();
	string newNickname = arg[0];

	for (it = _clients.begin(); it != _clients.end(); it++) {
		if (it->second.getNickname() == currentNickname && it->second.getSocket() != cl.getSocket())
			newNickname = it->second.getNickname();
	}

	if (newNickname == currentNickname && _clients[socket].getIsWelcomed() == 1) {
   		cl.sendMessage(ERR_NICKNAMEINUSE(newNickname));
		return ;
	}

	if (isValidNickname(arg[0]) == false)
	{
   		if (send(socket, arg[0].c_str(), arg[0].length(), 0) < 0)
			throw(std::out_of_range("Error while sending"));
	}
	// to put in the define line too long

	if (_clients[socket].getIsWelcomed() == 1){
		string msg = string(":") + _clients[socket].getNickname() + "!" + _clients[socket].getNickname() + "@localhost NICK :" + arg[0] + "\r\n";
		send(socket, msg.c_str(), msg.length(), 0);
	}
	_clients[socket].setNickname(arg[0]);
	string user = _clients[socket].getUser();
	string host = _clients[socket].getHost();
	//std::string errMsg = "461 NICK :Not enough parameters\r\n";
     //   send(socket, errMsg.c_str(), errMsg.length(), 0);
}