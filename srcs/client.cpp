#include "client.hpp"

Client::Client(int socket) : _socket(socket) {
	_nickname = "";
	_username = "";
	_hostname = "IRC_HELL";
	_iswelcomed = false;
	_userMode   = static_cast<MODES>(0);
}

Client::~Client(){}


Client& Client:: operator=(Client const &other){
	this->_socket = other._socket;
	this->_nickname = other._nickname;
	this->_username = other._username;
	this->_hostname = other._hostname;
	this->_iswelcomed = other._iswelcomed;
	this->_userMode = other._userMode;
	return (*this);
}

int		Client::getSocket(){ return _socket; }
string&	Client::getNickname(){ return _nickname; }
string&	Client::getUser(){ return _username; }
string&	Client::getHost() {return _hostname; }
string&	Client::getPassword(){return _password; }
bool	Client::getIsWelcomed(){ return _iswelcomed; }
string	Client::getUMode(){
	string modes;
	if((_userMode & i) == i){ modes += 'i';}
	if((_userMode & t) == t){ modes += 't';}
	if((_userMode & k) == k){ modes += 'k';}
	if((_userMode & o) == o){ modes += 'o';}
	if((_userMode & l) == l){ modes += 'l';}
	return (modes);
}
bool	Client::checkRight() {return (_userMode & o) == o;}


void	Client::setUser(string user) { _username = user; }
void	Client::setNickname(string nickname) { _nickname = nickname; }
void	Client::setPassword(string password) { _password = password ; }
void	Client::setIsWelcomed(bool info) { _iswelcomed = info; }
void	Client::setUMode() { _userMode = static_cast<e_modes>(_userMode | o); }
void	Client::setIMode() { _userMode = static_cast<e_modes>(_userMode | o); }

void	Client::unsetUMode() { _userMode = static_cast<e_modes>(_userMode & ~o); }

bool	Client::isReady() { return (!_nickname.empty() && !_username.empty());}

void	Client::sendMessage(const string& message) {
	if (send(_socket, message.c_str(), message.length(), 0) < 0)
		throw(std::out_of_range("Error while sending"));
}