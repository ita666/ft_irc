#include "server.hpp"
#include "command.hpp"

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

void Server::Nick(int socket, vector<string>& arg){
	
	//to do handle error msg
	if (nicknameAlreadyUsed(arg[0], _clients[socket]) == true)
	{
    	string paquet = "CACA PIPI:";
   		if (send(socket, paquet.c_str(), paquet.length(), 0) < 0)
        	throw(std::out_of_range("Error while sending"));
	}
	if (isValidNickname(arg[0]) == false)
	{
		string paquet = "CACA PIPI:";
   		if (send(socket, paquet.c_str(), paquet.length(), 0) < 0)
			throw(std::out_of_range("Error while sending"));
	}

	_clients[socket].setNickname("test");
	_clients[socket].setNickname(arg[0]);
	string user = _clients[socket].getUser();
	string host = _clients[socket].getHost();
	string nickname_msg = ":localhost 001 " + arg[0] + " :Welcome to IRC " + arg[0] + "!" + user + "@" + host + "\r\n";
	send(socket, nickname_msg.c_str(), nickname_msg.size(), 0);
	//std::string errMsg = "461 NICK :Not enough parameters\r\n";
     //   send(socket, errMsg.c_str(), errMsg.length(), 0);
}