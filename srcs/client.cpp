#include "client.hpp"

Client::Client(int socket) : _socket(socket) {
	_nickname = "";
	_username = "";
	_hostname = "IRC_HELL";
	_iswelcomed = false;
	_userMode   = static_cast<MODES>(0);
}

Client::~Client(){}

int		Client::getSocket(){ return _socket; }
string&	Client::getNickname(){ return _nickname; }
string&	Client::getUser(){ return _username; }
string&	Client::getHost() {return _hostname; }
string&	Client::getPassword(){return _password; }
bool	Client::getIsWelcomed(){ return _iswelcomed; }
string	Client::getMode(){
	string modes;
	if((_userMode & i) == i){ modes += 'i';}
	if((_userMode & t) == t){ modes += 't';}
	if((_userMode & k) == k){ modes += 'k';}
	if((_userMode & o) == o){ modes += 'o';}
	if((_userMode & l) == l){ modes += 'l';}
	return (modes);
}

void	Client::setUser(string user) { _username = user; }
void	Client::setNickname(string nickname) { _nickname = nickname; }
void	Client::setPassword(string password) { _password = password ; }
void	Client::setIsWelcomed(bool info) { _iswelcomed = info; }
void	Client::setMode(char c){
	switch (c) {
        case 'i': _userMode = static_cast<e_modes>(_userMode | i); break;
        case 't': _userMode = static_cast<e_modes>(_userMode | t); break;
        case 'k': _userMode = static_cast<e_modes>(_userMode | k); break;
        case 'o': _userMode = static_cast<e_modes>(_userMode | o); break;
        case 'l': _userMode = static_cast<e_modes>(_userMode | l); break;
        default: throw runtime_error("setting wrong mode as input"); break;
    }
}

void	Client::removeMode(char c){
	switch (c) {
        case 'i': _userMode = static_cast<e_modes>(_userMode & ~i); break;
        case 't': _userMode = static_cast<e_modes>(_userMode & ~t); break;
        case 'k': _userMode = static_cast<e_modes>(_userMode & ~k); break;
        case 'o': _userMode = static_cast<e_modes>(_userMode & ~o); break;
        case 'l': _userMode = static_cast<e_modes>(_userMode & ~l); break;
        default: throw runtime_error("setting wrong mode as input"); break;
    }
}

bool	Client::isReady() { return (!_nickname.empty() && !_username.empty());}

void	Client::sendMessage(const string& message) {
	if (send(_socket, message.c_str(), message.length(), 0) < 0)
		throw(std::out_of_range("Error while sending"));
}