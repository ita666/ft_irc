#include "server.hpp"
#include "client.hpp"

void Server::Topic(int socket, vector<string>& arg, Client cl) {
	(void)cl;
	string currentClientNickname = _clients[socket].getNickname();
	string currentClientUsername = _clients[socket].getUser();
	string channelName = arg[0];
	Client currentClient = _clients[socket];
	
	string topic = arg[1];
	if (arg.size() == 0){
		cout << "TOPIC current client needmore param\n";
		return _channels[channelName].broadcast(TOPIC(currentClientNickname, currentClientUsername, channelName, topic));
	}
	if (currentClient.checkRight() == false) {
		cout << "TOPIC current client right\n";
		return currentClient.sendMessage(ERR_NOPRIVILEGES(currentClientNickname));
	}
	if ((_channels[channelName].getCMode() & t) != t) {
		cout << "TOPIC current client -T not activated\n";
		return currentClient.sendMessage(ERR_NOPRIVILEGES(currentClientNickname));
	}
	else if (arg.size() == 1) {
		if (checkChannelName(channelName) == false) {
			cout << "TOPIC clean no such channel \n";
			return currentClient.sendMessage(ERR_NOSUCHCHANNEL(currentClientNickname, channelName));
		} else if (_channels[channelName].isUserInChannel(currentClientNickname) == false) {
			cout << "TOPIC clean not on channel \n";
			return currentClient.sendMessage(ERR_NOTONCHANNEL(currentClientNickname, channelName));
		} else {
			cout << "TOPIC clean sending to all user \n";
			// _channels[channelName].setTopicNickname(currentClientNickname);
			_channels[channelName].broadcast(RPL_TOPIC(currentClientNickname, channelName, _channels[channelName].getTopic()));
		}
	} else if (arg.size() == 2) {
		if (checkChannelName(channelName) == false) {
			cout << "TOPIC SEND no such channel\n";
			return currentClient.sendMessage(ERR_NOSUCHCHANNEL(currentClientNickname, channelName));
		} else if (_channels[channelName].isUserInChannel(currentClientNickname) == false) {
			cout << "TOPIC SEND not on channel\n";
			return currentClient.sendMessage(ERR_NOTONCHANNEL(currentClientNickname, channelName));
		} else {
			cout << "TOPIC SEND to all user\n";
			_channels[channelName].setTopic(topic);
			_channels[channelName].setTopicNickname(currentClientNickname);
			_channels[channelName].broadcast(TOPIC(currentClientNickname, currentClientUsername, channelName, topic));
		}
	}
}
