#include "client.hpp"

Client::Client(int socket) : _socket(socket) {
	_nickname = "";
	_username = "";
	_hostname = "IRC_HELL";
	_iswelcomed = false;

}

Client::~Client(){}

int		Client::getSocket(){ return _socket; }
string&	Client::getNickname(){ return _nickname; }
string&	Client::getUser(){ return _username; }
string&	Client::getHost(){ return _hostname; }
bool	Client::getIsWelcomed(){ return _iswelcomed; }


void	Client::setUser(string user) { _username = user; }
void	Client::setNickname(string nickname) { _nickname = nickname; }
void	Client::setIsWelcomed(bool info) { _iswelcomed = info; }
bool	Client::isReady() { return (!_nickname.empty() && !_username.empty());}

void	Client::sendMessage(const string& message) {
	if (send(_socket, message.c_str(), message.length(), 0) < 0)
		throw(std::out_of_range("Error while sending"));
}