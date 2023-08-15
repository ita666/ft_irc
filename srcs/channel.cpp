#include "channel.hpp"

Channel::Channel(){	
	_topic	= "Elephant are pregnant for 20 month";
	_key	= "";
	}
Channel::Channel(string name) : _name(name){
	_topic	= "Elephant are pregnant for 20 month";
	_key	= "";
}

Channel::~Channel(){}

string	Channel::getName() { return _name; }
void	Channel::setName(string& name){ _name = name; }

string	Channel::getTopic() { return _topic; }
void	Channel::setTopic(string& topic){ _topic = topic; }

size_t&	Channel::getLimit() { return _limit; }
void	Channel::setLimit(int limit) { _limit = limit; }

map<string, int>&	Channel::getMap() { return _nameToSocket; }

MODES Channel::getCMode(){ return (_userMode); }

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
int*	Channel::getAllUsers() {
	map<string, int>::iterator it;
	int *users = new int[_nameToSocket.size()];
	int i = 0;

	for (it = _nameToSocket.begin(); it != _nameToSocket.end(); it++) {
		users[i] = it->second;
		i++;
	}


	map<string, int>::iterator ot;
	for (ot = _nameToSocket.begin(); ot != _nameToSocket.end(); ot++) {
		cout << "name " << ot->first << " socket " << ot->second << '\n';
	}
	return users;
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