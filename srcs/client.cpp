#include "client.hpp"

Client::Client(int socket) : _socket(socket) {
	_nickname = "";
	_username = "";
	_hostname = "IRC_HELL";
	_realhost = "";
	_iswelcomed = false;
	_userMode   = static_cast<MODES>(0);
}


Client::Client() : _socket(-1) {
	_nickname = "";
	_username = "";
	_hostname = "IRC_HELL";
	_realhost = "";
	_iswelcomed = false;
	_userMode   = static_cast<MODES>(0);
}

Client::~Client(){}


Client& Client:: operator=(Client const &other) {
	this->_socket = other._socket;
	this->_nickname = other._nickname;
	this->_username = other._username;
	this->_hostname = other._hostname;
	this->_realhost = other._realhost;
	this->_iswelcomed = other._iswelcomed;
	this->_password = other._password;
	this->_userMode = other._userMode;
	return (*this);
}

void			Client::setUser(string user) { _username = user; }
void			Client::setNickname(string nickname) { _nickname = nickname; }
void			Client::setHost(string host) { _realhost = host; }
void			Client::setPassword(string password) { _password = password ; }
void			Client::setIsWelcomed(bool info) { _iswelcomed = info; }
void			Client::setUMode() { _userMode = static_cast<e_modes>(_userMode | o); }
void			Client::setIMode() { _userMode = static_cast<e_modes>(_userMode | i); }

int				Client::getSocket() { return _socket; }
const string	Client::getNickname() const { return _nickname; }
const string	Client::getUser() const { return _username; }
const string	Client::getHost() const {return _hostname; }
const string	Client::getRealhost() const {return _realhost; }
const string	Client::getPassword() const {return _password; }
bool			Client::getIsWelcomed() { return _iswelcomed; }
const string	Client::getUMode() const {
	string modes;
	if((_userMode & i) == i){ modes += 'i';}
	if((_userMode & t) == t){ modes += 't';}
	if((_userMode & k) == k){ modes += 'k';}
	if((_userMode & o) == o){ modes += 'o';}
	if((_userMode & l) == l){ modes += 'l';}
	return (modes);
}
bool	Client::checkRight() { return (_userMode & o) == o; }

void	Client::unsetUMode() { _userMode = static_cast<e_modes>(_userMode & ~o); }

bool	Client::isReady() { return (!_nickname.empty() && !_username.empty()); }

void	Client::sendMessage(const string& message) {
	if (send(_socket, message.c_str(), message.length(), 0) < 0)
		throw(std::out_of_range("Error while sending"));
}