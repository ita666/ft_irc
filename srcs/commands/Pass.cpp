#include "server.hpp"
#include "define.hpp"



bool	Server::passwordAuth(int socket) {
	if (_clients[socket].getPassword() == _password){ return true; }
	if (_clients[socket].getPassword() == OPERATOR_PASSWORD ){ return true; }
	return (false);
}

void	Server::welcome(int socket) {
	if(_clients[socket].isReady() && !_clients[socket].getIsWelcomed() && passwordAuth(socket)) {
		_clients[socket].setIsWelcomed(true);
		string nickname = _clients[socket].getNickname();
		string user = _clients[socket].getUser();
		string host = _clients[socket].getHost();
		string welcome_msg = (string)":" + SERVER_NAME " 001 " + nickname + " :Welcome to IRC " + nickname + "!" + user + "@" + host + "\r\n";
		send(socket, welcome_msg.c_str(), welcome_msg.size(), 0);
		string msgBot = "AnimalFacts is the bot channel, join it to get some facts about animals!\r\n";
		send(socket, msgBot.c_str(), msgBot.size(), 0);
		}
}

void	Server::Pass(int socket, vector<string>& arg, Client client) {
	(void)socket;
	(void)client;
	//check if pass is operator password if so grant operator mode to the client
	// and let him through 
	if(!arg[0].compare(OPERATOR_PASSWORD)) {
		_clients[socket].setPassword(arg[0]);
		_clients[socket].sendMessage(RPL_YOUROPER());
		_clients[socket].setUMode();
		cout << "\nOPERATOR MODE GRANTED\n";
		return ;
	}

	if(!arg[0].compare(_password)) {
		_clients[socket].setPassword(arg[0]);
		cout << _clients[socket].getPassword() << " \n";
		return ;
	}
	//send error message avoid sending the welcom msg;
	// delete the socket;
	_clients[socket].sendMessage(ERR_PASSWDMISMATCH());
}