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
string	Client::getUMode(){
	string modes;
	if((_userMode & i) == i){ modes += 'i';}
	if((_userMode & t) == t){ modes += 't';}
	if((_userMode & k) == k){ modes += 'k';}
	if((_userMode & o) == o){ modes += 'o';}
	if((_userMode & l) == l){ modes += 'l';}
	return (modes);
}

void	Client::giveOMode(Client client){
	
	
	cout << "CLIENT RIGHTS: " << client.getUMode() << endl;
	if ((_userMode & o) == o) {
		cout << "AVANT SET " << client.getUMode() << endl;
        client.setUMode();
		cout << "APRES SET " << client.getUMode() << endl;
		cout << "HAS PRIVILEGE" << endl;
	} else {
        sendMessage(ERR_NOPRIVILEGES(_nickname));
		cout << "NO PRIVILEGE" << endl;
	}
}

void	Client::giveOMode(Client* client){
	
	cout << "CLIENT RIGHTS: " << _userMode << endl;
	if ((_userMode & o) == o) {
		cout << "AVANT SET " << client->getUMode() << endl;
        client->setUMode();
		cout << "APRES SET " << client->getUMode() << endl;
		cout << "HAS PRIVILEGE" << endl;
	} else {
        sendMessage(ERR_NOPRIVILEGES(_nickname));
		cout << "NO PRIVILEGE" << endl;
	}
}

void	Client::setUser(string user) { _username = user; }
void	Client::setNickname(string nickname) { _nickname = nickname; }
void	Client::setPassword(string password) { _password = password ; }
void	Client::setIsWelcomed(bool info) { _iswelcomed = info; }
void	Client::setUMode() { _userMode = static_cast<e_modes>(_userMode | o); }

void	Client::removeUMode(Client* client) {
	if ((_userMode & o) == o) {
		client->_userMode = static_cast<e_modes>(_userMode & ~o);
		cout << "HAS PRIVILEGE TO REMOVE" << endl;
	} else {
        sendMessage(ERR_NOPRIVILEGES(_nickname));
		cout << "NO PRIVILEGE TO REMOVE" << endl;
	}
}

bool	Client::isReady() { return (!_nickname.empty() && !_username.empty());}

void	Client::sendMessage(const string& message) {
	if (send(_socket, message.c_str(), message.length(), 0) < 0)
		throw(std::out_of_range("Error while sending"));
}