#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"

void Server::Part(int socket, vector<string>& arg, Client client){
    (void)socket;

    for(size_t i = 0; i < arg.size(); i++) {cout << "arg[" << i << "] = " << arg[i] << "\n";}
	if (arg.size() < 1) {
        _clients[socket].sendMessage(ERR_NEEDMOREPARAMS(client.getNickname(), "PART"));
        return;
    }

    if (_channels.find(arg[0]) == _channels.end()) {
        cout << " no sush channel\n";
		_clients[socket].sendMessage(ERR_NOSUCHCHANNEL(_clients[socket].getNickname(), arg[0]));
        return;
    }

    if (!_channels[arg[0]].isUserInChannel(_clients[socket].getNickname())) { 
        cout << " not on channel\n";
        _clients[socket].sendMessage(ERR_NOTONCHANNEL(_clients[socket].getNickname(), arg[0]));
        return;
    }
    _channels[arg[0]].removeUser(_clients[socket].getNickname(), _clients[socket].getSocket());
    string msg = ":" + _clients[socket].getNickname() + "!" + _clients[socket].getUser() + "@" + _clients[socket].getRealhost() +" PART " + arg[0] + "\r\n";
    cout << msg << "\n";
    if (send(socket, msg.c_str(), msg.length(), 0)< 0)
        cout << "error send\n";

    // Broadcast parting message to all channel members
    //channel[arg[1]].broadcastMessage(partingMessage);

    // If the channel is empty, destroy it
    if (_channels[arg[0]].isEmpty()) {
		_clients[socket].sendMessage(ERR_NOUSERLEFT(client.getNickname(), arg[0]));
        _channels.erase(arg[0]); 
    }
}