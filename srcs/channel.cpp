#include "channel.hpp"


Channel::Channel(string name) : _channel(name){}

string	Channel::getName() { return _name; }
void	Channel::setName(string& name){ _name = name }

bool	Channel::findUser(int socket) { return (_users.find(socket) != _users.end()); }



