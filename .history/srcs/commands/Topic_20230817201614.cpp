#include "server.hpp"
#include "command.hpp"
#include "client.hpp"

void Server::Topic(int socket, vector<string>& arg, Client cl) {
	(void)cl;
	string currentClientNickname = _clients[socket].getNickname();
	string currentClientUsername = _clients[socket].getUser();
	string channelName = arg[0];
	string topic = arg[1];
	Client currentClient = _clients[socket];

	if (arg.size() == 0)
		return currentClient.sendMessage(ERR_NEEDMOREPARAMS(currentClientNickname, "TOPIC"));
	else if (arg.size() == 1) {
		if (checkChannelName(channelName) == false) {
			return currentClient.sendMessage(ERR_NOSUCHCHANNEL(currentClientNickname, channelName));
		} else if (_channels[channelName].isUserInChannel(currentClientNickname) == false) {
			return currentClient.sendMessage(ERR_NOTONCHANNEL(currentClientNickname, channelName));
		} else {
			_channels[channelName].setTopic("");
			_channels[channelName].broadcast(RPL_TOPIC(currentClientNickname, channelName, topic));
			int* usersInChannel = _channels[channelName].getAllUsers();
			for (int i = 0; i < sizeof(usersInChannel); i++) {
				string concernedClientNickname = _channels[channelName].getName(usersInChannel[i]);
				string msg = RPL_TOPIC(concernedClientNickname, channelName, currentClientNickname, time);
				send(usersInChannel[i], msg.c_str(), msg.length(), 0);
			}
		}
	} else if (arg.size == 2) {
		if (checkChannelName(channelName) == false) {
			return currentClient.sendMessage(ERR_NOSUCHCHANNEL(currentClientNickname, channelName));
		} else if (_channels[channelName].isUserInChannel(currentClientNickname) == false) {
			return currentClient.sendMessage(ERR_NOTONCHANNEL(currentClientNickname, channelName));
		}
		else {
			_channels[channelName].setTopic(topic);
			_channels[channelName].broadcast(RPL_TOPIC(currentClientNickname, channelName, topic));
			int* usersInChannel = _channels[channelName].getAllUsers();
			for (int i = 0; i < sizeof(usersInChannel); i++) {
				string concernedClientNickname = _channels[channelName].getName(usersInChannel[i]);
				string msg = RPL_TOPIC(concernedClientNickname, channelName, currentClientNickname, time);
				send(usersInChannel[i], msg.c_str(), msg.length(), 0);
			}
		}
	}
}
// RPL_TOPIC
// RPL_NOTOPIC
RPL_TOPICWHOTIME
ERR_NOPRIVILEGES
// ERR_NEEDMOREPARAMS
ERR_NOTONCHANNEL
// ERR_NOSUCHCHANNEL