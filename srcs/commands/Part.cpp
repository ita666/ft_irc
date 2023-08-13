#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"

void Server::Part(int socket, vector<string>& arg, Client client){
    (void)socket;

	cout << " part " << arg[0] << " \n";
	cout << "part name " << _channels[arg[0]].getName() << " \n";

	if (arg.size() < 2) {
        client.sendMessage(ERR_NEEDMOREPARAMS(client.getNickname(), "PART"));
        return;
    }

    if (_channels.find(arg[0]) == _channels.end()) {
        client.sendMessage(ERR_NOSUCHCHANNEL(client.getNickname(), arg[0]));
        return;
    }

    if (!_channels[arg[0]].isUserInChannel(client.getUser())) { 
        client.sendMessage(ERR_NOTONCHANNEL(client.getNickname(), arg[0]));
        return;
    }

    string partingMessage = (arg.size() == 3) ? arg[0] : client.getNickname() + " has left the channel";

    _channels[arg[0]].removeUser(client.getUser(), client.getSocket());

    // Broadcast parting message to all channel members
    //channel[arg[1]].broadcastMessage(partingMessage);

    // If the channel is empty, destroy it
    if (_channels[arg[1]].isEmpty()) {
        _channels.erase(arg[0]); 
    }
}