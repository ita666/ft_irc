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
	
	char	timestamp[20];
	time_t rawtime;
	time(&rawtime);

	if (currentClient.checkRight() == false){
		cout << "TOPIC current client right\n";
		return currentClient.sendMessage(ERR_NOPRIVILEGES(currentClientNickname));
	}
	else {
		if (arg.size() == 0){
			cout << "TOPIC current client needmore param\n";
			return currentClient.sendMessage(ERR_NEEDMOREPARAMS(currentClientNickname, "TOPIC"));
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
				struct tm* timeinfo = localtime(&rawtime);
				strftime(timestamp, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
				_channels[channelName].setTimestamp(timestamp);
				_channels[channelName].setTopic("");
				_channels[channelName].setTopicNickname(currentClientNickname);
				_channels[channelName].broadcast(RPL_TOPIC(currentClientNickname, channelName, topic));
				int* usersInChannel = _channels[channelName].getAllUsers();
				for (int i = 0; i < sizeof(usersInChannel); i++) {
					string concernedClientNickname = _channels[channelName].getName(usersInChannel[i]);
					string msg = RPL_TOPIC(concernedClientNickname, channelName, topic);
					send(usersInChannel[i], msg.c_str(), msg.length(), 0);
				}
				for (int i = 0; i < sizeof(usersInChannel); i++) {
					string concernedClientNickname = _channels[channelName].getName(usersInChannel[i]);
					string msg = RPL_TOPICWHOTIME(concernedClientNickname, channelName, currentClientNickname, _channels[channelName].getTimestamp());
					send(usersInChannel[i], msg.c_str(), msg.length(), 0);
				}
			}
		} else if (arg.size == 2) {
			if (checkChannelName(channelName) == false) {
				cout << "TOPIC SEND no such channel\n";
				return currentClient.sendMessage(ERR_NOSUCHCHANNEL(currentClientNickname, channelName));
			} else if (_channels[channelName].isUserInChannel(currentClientNickname) == false) {
				cout << "TOPIC SEND not on channel\n";
				return currentClient.sendMessage(ERR_NOTONCHANNEL(currentClientNickname, channelName));
			} else {

				cout << "TOPIC SEND to all user\n";
				struct tm* timeinfo = localtime(&rawtime);
				strftime(_channels[channelName]._timestamp, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
				_channels[channelName].setTimestamp((string)timestamp);
				_channels[channelName].setTopic(topic);
				_channels[channelName].setTopicNickname(currentClientNickname);
				_channels[channelName].broadcast(RPL_TOPIC(currentClientNickname, channelName, topic));
				int* usersInChannel = _channels[channelName].getAllUsers();
				for (int i = 0; i < sizeof(usersInChannel); i++) {
					string concernedClientNickname = _channels[channelName].getName(usersInChannel[i]);
					string msg = RPL_TOPIC(concernedClientNickname, channelName, topic);
					send(usersInChannel[i], msg.c_str(), msg.length(), 0);
				}
				for (int i = 0; i < sizeof(usersInChannel); i++) {
					string concernedClientNickname = _channels[channelName].getName(usersInChannel[i]);
					string msg = RPL_TOPICWHOTIME(concernedClientNickname, channelName, currentClientNickname, _channels[channelName].getTimestamp());
					send(usersInChannel[i], msg.c_str(), msg.length(), 0);
				}
			}
		}
	}
}