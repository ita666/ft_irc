#include "server.hpp"
#include "command.hpp"

// comment

bool Server::nicknameAlreadyUsed(string name, Client cl) {
	map<int, Client>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it++) {
		if (it->second.getNickname() == name && it->second.getSocket() != cl.getSocket())
			return true;
	}
	return false;
}

static bool isSpecialChar(char c)
{
	switch (c)
	{
		case '-':
		case '[':
		case ']':
		case '\\':
		case '`':
		case '_':
		case '^':
		case '{':
		case '}':
		case '|':
			return true;
		default:
			return false;
	}
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
		if (it->second.getNickname() == newNickname && it->second.getSocket() != cl.getSocket())
			currentNickname = it->second.getNickname();
	}
	if (newNickname == currentNickname) {
   		cl.sendMessage(ERR_NICKNAMEINUSE(newNickname));
		return ;
	}
	if (isValidNickname(arg[0]) == false)
	{
   		if (send(socket, arg[0].c_str(), arg[0].length(), 0) < 0)
			throw(std::out_of_range("Error while sending"));
	}

	_clients[socket].setNickname(arg[0]);
	string user = _clients[socket].getUser();
	string host = _clients[socket].getHost();
	string nickname_msg = ":localhost 001 " + arg[0] + " :Welcome to IRC " + arg[0] + "!" + user + "@" + host + "\r\n";
	send(socket, nickname_msg.c_str(), nickname_msg.size(), 0);
	//std::string errMsg = "461 NICK :Not enough parameters\r\n";
     //   send(socket, errMsg.c_str(), errMsg.length(), 0);
}