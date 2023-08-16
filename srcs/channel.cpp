#include "channel.hpp"

Channel::Channel(){	
	_topic	= "Elephant are pregnant for 20 month";
	_key	= "";
	_chanMode   = static_cast<MODES>(0);
	}
Channel::Channel(string name) : _name(name){
	_topic	= "Elephant are pregnant for 20 month";
	_key	= "";
	_chanMode   = static_cast<MODES>(0);
}

Channel::~Channel(){}

string	Channel::getName() { return _name; }
void	Channel::setName(string& name){ _name = name; }

string	Channel::getTopic() { return _topic; }
void	Channel::setTopic(string& topic){ _topic = topic; }

size_t&	Channel::getLimit() { return _limit; }
void	Channel::setLimit(int limit) { _limit = limit; }

map<string, int>&	Channel::getMap() { return _nameToSocket; }

MODES Channel::getCMode(){ return (_chanMode); }

void	Channel::setCMode(char c){
	switch (c) {
        case 'i': _chanMode = static_cast<e_modes>(_chanMode | i);
					cout << "set i mode" << endl;
		 break;
        case 't': _chanMode = static_cast<e_modes>(_chanMode | t); break;
        case 'k': _chanMode = static_cast<e_modes>(_chanMode | k); break;
        case 'o': _chanMode = static_cast<e_modes>(_chanMode | o); break;
        case 'l': _chanMode = static_cast<e_modes>(_chanMode | l); break;
        default: throw runtime_error("setting wrong mode as input"); break;
    }
}

void	Channel::removeCMode(char c){
	switch (c) {
        case 'i': _chanMode = static_cast<e_modes>(_chanMode & ~i); break;
        case 't': _chanMode = static_cast<e_modes>(_chanMode & ~t); break;
        case 'k': _chanMode = static_cast<e_modes>(_chanMode & ~k); break;
        case 'o': _chanMode = static_cast<e_modes>(_chanMode & ~o); break;
        case 'l': _chanMode = static_cast<e_modes>(_chanMode & ~l); break;
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

void	Channel::addGuest(const string& nickname) {
	_invited.push_back(nickname);
}

void	Channel::removeGuest(const string& nickname) {
	vector<string>::iterator it;
	for (it = _invited.begin(); it != _invited.end(); it++) {
		if (nickname == *it) {
			_invited.erase(it);
			return;
		}
	}
}

bool Channel::isUserInChannel(const string& username) {
    return _nameToSocket.find(username) != _nameToSocket.end();
}

bool Channel::isInviteOnly(const string& nickname) {
	vector<string>::iterator it;
	if ((_chanMode & i) == i) {
		if (std::find(_invited.begin(), _invited.end(), nickname) != _invited.end()) { return true;}
		return false;
	}
	return true;
}

string Channel::findInvited(string& guest) {
	vector<string>::iterator it;
	for (it = _invited.begin(); it != _invited.end(); it++) {
		if (guest == *it)
			return *it;
	}
	return "";
}

bool Channel::isEmpty(){
	return (!_nameToSocket.size());
}

string	Channel::getName(int socket){
	if (_socketToName.find(socket) != _socketToName.end()){
		return (_socketToName[socket]);
	} else { throw runtime_error("Socket not found in the channel."); }
} 