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

void Server::Nick(int socket, vector<string>& arg){
	
	//to do handle error msg
	if (nicknameAlreadyUsed(arg[0], _clients[socket]) == true)
	{
    	string paquet = "CACA PIPI:";
   		if (send(socket, paquet.c_str(), paquet.length(), 0) < 0)
        	throw(std::out_of_range("Error while sending"));
	}
	cout << "nick " << arg[0] << '\n';
	_clients[socket].setNickname("test");
	cout << "nick " << arg[0] << '\n';
	
	_clients[socket].setNickname(arg[0]);
	string user = _clients[socket].getUser();
	string host = _clients[socket].getHost();
	string nickname_msg = ":localhost 001 " + arg[0] + " :Welcome to IRC " + arg[0] + "!" + user + "@" + host + "\r\n";
	send(socket, nickname_msg.c_str(), nickname_msg.size(), 0);
	//std::string errMsg = "461 NICK :Not enough parameters\r\n";
     //   send(socket, errMsg.c_str(), errMsg.length(), 0);
}