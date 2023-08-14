#include "channel.hpp"

Channel::Channel(){	
	_topic = "Elephant are pregnant for 20 month";
	}
Channel::Channel(string name) : _name(name){
	_topic = "Elephant are pregnant for 20 month";
}

Channel::~Channel(){}

string	Channel::getName() { return _name; }
void	Channel::setName(string& name){ _name = name; }

string	Channel::getTopic() { return _topic; }
void	Channel::setTopic(string& topic){ _topic = topic; }

string	Channel::getCMode(){
	string modes;
	if((_userMode & i) == i){ modes += 'i';}
	if((_userMode & t) == t){ modes += 't';}
	if((_userMode & k) == k){ modes += 'k';}
	if((_userMode & o) == o){ modes += 'o';}
	if((_userMode & l) == l){ modes += 'l';}
	return (modes);
}

void	Channel::setCMode(char c){
	switch (c) {
        case 'i': _userMode = static_cast<e_modes>(_userMode | i); break;
        case 't': _userMode = static_cast<e_modes>(_userMode | t); break;
        case 'k': _userMode = static_cast<e_modes>(_userMode | k); break;
        case 'o': _userMode = static_cast<e_modes>(_userMode | o); break;
        case 'l': _userMode = static_cast<e_modes>(_userMode | l); break;
        default: throw runtime_error("setting wrong mode as input"); break;
    }
}

void	Channel::removeCMode(char c){
	switch (c) {
        case 'i': _userMode = static_cast<e_modes>(_userMode & ~i); break;
        case 't': _userMode = static_cast<e_modes>(_userMode & ~t); break;
        case 'k': _userMode = static_cast<e_modes>(_userMode & ~k); break;
        case 'o': _userMode = static_cast<e_modes>(_userMode & ~o); break;
        case 'l': _userMode = static_cast<e_modes>(_userMode & ~l); break;
        default: throw runtime_error("setting wrong mode as input"); break;
    }
}

void	Channel::addUser(string& userName, int socket){
    _nameToSocket[userName] = socket;
    _socketToName[socket] = userName;
}

void	Channel::removeUser(string& userName, int socket){
    _nameToSocket.erase(userName);
    _socketToName.erase(socket);
}

int		Channel::getSocket(string& userName){
	if (_nameToSocket.find(userName) != _nameToSocket.end()){
		return (_nameToSocket[userName]);
	} else { throw runtime_error("Username not found in the channel."); }
}

bool Channel::isUserInChannel(const string& username) {
    return _nameToSocket.find(username) != _nameToSocket.end();
}

bool Channel::isEmpty(){
	return (!_nameToSocket.size());
}

string	Channel::getName(int socket){
	if (_socketToName.find(socket) != _socketToName.end()){
		return (_socketToName[socket]);
	} else { throw runtime_error("Socket not found in the channel."); }
} 