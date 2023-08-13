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