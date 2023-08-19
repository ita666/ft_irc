#include "server.hpp"
#include "client.hpp"

void Server::Topic(int socket, vector<string>& arg, Client cl) {
	(void)cl;
	string currentClientNickname = _clients[socket].getNickname();
	string currentClientUsername = _clients[socket].getUser();
	string channelName = arg[0];
	Client currentClient = _clients[socket];
	
	string topic = "";
	for (size_t i = 1; i < arg.size(); i++) {
		topic += arg[i];
		if (i != arg.size() - 1)
			topic += " ";
	}
	if (arg.size() == 0){
		return _channels[channelName].broadcast(TOPIC(currentClientNickname, currentClientUsername, channelName, topic));
	}
	if (currentClient.checkRight() == false) {
		return currentClient.sendMessage(ERR_NOPRIVILEGES(currentClientNickname));
	}
	if ((_channels[channelName].getCMode() & t) != t) {
		return currentClient.sendMessage(ERR_NOPRIVILEGES(currentClientNickname));
	}
	else if (arg.size() == 1) {
		if (checkChannelName(channelName) == false) {
			return currentClient.sendMessage(ERR_NOSUCHCHANNEL(currentClientNickname, channelName));
		} else if (_channels[channelName].isUserInChannel(currentClientNickname) == false) {
			return currentClient.sendMessage(ERR_NOTONCHANNEL(currentClientNickname, channelName));
		} else {
			// _channels[channelName].setTopicNickname(currentClientNickname);
			_channels[channelName].broadcast(RPL_TOPIC(currentClientNickname, channelName, _channels[channelName].getTopic()));
		}
	} else if (arg.size() >= 2) {
		if (checkChannelName(channelName) == false) {
			return currentClient.sendMessage(ERR_NOSUCHCHANNEL(currentClientNickname, channelName));
		} else if (_channels[channelName].isUserInChannel(currentClientNickname) == false) {
			return currentClient.sendMessage(ERR_NOTONCHANNEL(currentClientNickname, channelName));
		} else {
			_channels[channelName].setTopic(topic);
			_channels[channelName].setTopicNickname(currentClientNickname);
			_channels[channelName].broadcast(TOPIC(currentClientNickname, currentClientUsername, channelName, topic));
		}
	}
}
