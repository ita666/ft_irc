#include "channel.hpp"

Channel::Channel(){	
	_topic	= "";
	_key	= "";
	_chanMode   = static_cast<MODES>(0);
	}
Channel::Channel(string name) : _name(name){
	_topic	= "";
	_key	= "";
	_chanMode   = static_cast<MODES>(0);
}

Channel::~Channel(){}

string	Channel::getName() { return _name; }
void	Channel::setName(string& name){ _name = name; }

string	Channel::getTopic() { return _topic; }
void	Channel::setTopic(string topic){ _topic = topic; }

size_t&	Channel::getLimit() { return _limit; }
void	Channel::setLimit(string limit) {
	
	size_t limitInt;
	istringstream iss(limit);
	iss >> limitInt;
	_limit = limitInt;
}


string& Channel::getKey(){ return (_key); }
void	Channel::setKey(string& key){ _key = key; }
void	Channel::unsetKey(){ _key = "" ;}

map<string, int>&	Channel::getMap() { return _nameToSocket; }

string&	Channel::getTopicNickname(){ return (_topicNickname); }
void	Channel::setTopicNickname(string& topicNickname){ _topicNickname = topicNickname; }

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
		return (_nameToSocket[userName]);
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
		cout << "NAME IN CHANNEL \n" << ot->first << " SOCKET IN CHANNEL " << ot->second << '\n';
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
		if (find(_invited.begin(), _invited.end(), nickname) != _invited.end()) { return false;}
		return true;
	}
	return false;
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
		return (_socketToName[socket]);
}

vector<string> Channel::getAllNickname() {
	vector<string> users;
	map<string, int>::iterator it;
	for (it = _nameToSocket.begin(); it != _nameToSocket.end(); it++) {
		users.push_back(it->first);
	}
	return users;
}

void Channel::broadcast(string msg) {
	int* usersInChannel = getAllUsers();
	for (int i = 0; i < (int)_nameToSocket.size(); i++) {
		send(usersInChannel[i], msg.c_str(), msg.length(), 0);
	}
}

void	Server::broadcastJoin(int socket, vector<string>& arg) {
	string channelName = arg[0];
	string currentClientNickname = _clients[socket].getNickname();
	string currentClientUsername = _clients[socket].getUser();
	std::vector<string> users = _channels[channelName].getAllNickname();

	//for loop to add '@' for every operators in the channel
	for (size_t i = 0; i < users.size(); i++) {
		if () {
			if (_channels[channelName].isUserInChannel(users[i])) {
				if (_clients[_channels[channelName].getSocket(users[i])].checkRight() == true) {
					users[i] = "@" + users[i];
				}
			}
		}
	}
}