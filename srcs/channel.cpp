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

void			Channel::setName(string& name){ _name = name; }
const string	Channel::getName() const { return _name; }

void			Channel::setTopic(string topic){ _topic = topic; }
const string	Channel::getTopic() const { return _topic; }

void			Channel::setLimit(string limit) {
	size_t limitInt;
	istringstream iss(limit);
	iss >> limitInt;
	_limit = limitInt;
}
size_t			Channel::getLimit() { return _limit; }
	
void			Channel::setKey(string& key) { _key = key; }
void			Channel::unsetKey() { _key = "" ; }
const string	Channel::getKey() const { return (_key); }

map<string, int>	Channel::getMap() { return _nameToSocket; }

void			Channel::setTopicNickname(const string topicNickname) { _topicNickname = topicNickname; }
const string	Channel::getTopicNickname() const { return (_topicNickname); }

void	Channel::setCMode(char c){
	switch (c) {
        case 'i': _chanMode = static_cast<e_modes>(_chanMode | i);
		break;
        case 't': _chanMode = static_cast<e_modes>(_chanMode | t); break;
        case 'k': _chanMode = static_cast<e_modes>(_chanMode | k); break;
        case 'o': _chanMode = static_cast<e_modes>(_chanMode | o); break;
        case 'l': _chanMode = static_cast<e_modes>(_chanMode | l); break;
        default: cerr << "setting wrong mode as input"; break;
    }
}
MODES	Channel::getCMode() { return (_chanMode); }

void	Channel::removeCMode(char c){
	switch (c) {
        case 'i': _chanMode = static_cast<e_modes>(_chanMode & ~i); break;
        case 't': _chanMode = static_cast<e_modes>(_chanMode & ~t); break;
        case 'k': _chanMode = static_cast<e_modes>(_chanMode & ~k); break;
        case 'o': _chanMode = static_cast<e_modes>(_chanMode & ~o); break;
        case 'l': _chanMode = static_cast<e_modes>(_chanMode & ~l); break;
        default: cerr << "setting wrong mode as input"; break;
    }
}

void	Channel::addUser(const string userName, int socket){
    _nameToSocket[userName] = socket;
    _socketToName[socket] = userName;
}

void	Channel::removeUser(const string userName, int socket){
    _nameToSocket.erase(userName);
    _socketToName.erase(socket);
}

int		Channel::getSocket (string& userName){
		return (_nameToSocket[userName]);
}

vector<int>	Channel::getAllUsers() {
	map<string, int>::iterator it;
	vector<int> users;
	int i = 0;

	for (it = _nameToSocket.begin(); it != _nameToSocket.end(); it++) {
		users.push_back(it->second);
		i++;
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

bool	Channel::isEmpty(){
	return (!_nameToSocket.size());
}

string	Channel::getName(int socket) {
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

void	Channel::broadcast(string msg) {
	vector<int> usersInChannel = getAllUsers();
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
		if (_stringToClients[users[i]].checkRight() == true) {
			users[i] = "@" + users[i];
		}
	}
	string usersList = "";
	for (size_t i = 0; i < users.size(); i++) {
		usersList += users[i];
		if (i != users.size() - 1)
			usersList += " ";
	}
	_clients[socket].sendMessage(RPL_NAMREPLY(currentClientNickname, usersList, channelName));
}
