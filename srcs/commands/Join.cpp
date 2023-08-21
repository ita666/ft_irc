#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"



void	Server::Join(int socket, vector<string>& arg, Client client){
	
	(void)socket;
	string channelName = arg[0];
	if (arg.size() < 1)
		return _clients[socket].sendMessage(ERR_NEEDMOREPARAMS(_clients[socket].getNickname(), "JOIN"));

	if (_channels.find(channelName) == _channels.end()){ // if the chan does not exist create it and add the user and give him the operator right
		_channels[channelName] = Channel (channelName);

		_channels[channelName].setName(channelName);
		_channels[channelName].addUser(client.getNickname(), client.getSocket());
		_clients[socket].setUMode();
		_clients[socket].sendMessage(RPL_NOTOPIC(_channels[channelName].getTopicNickname(), channelName));
	} else {

	bool isInvite = (_channels[channelName].isInviteOnly(client.getNickname()) == true);
	bool isKey = (arg.size() < 2 && (_channels[channelName].getCMode() & k) == k && arg[1] != _channels[channelName].getKey());
	bool isLimit = ((_channels[channelName].getCMode() & l) == l && _channels[channelName].getMap().size() >= _channels[channelName].getLimit());

    if (!_channels[channelName].isUserInChannel(_clients[socket].getNickname())) { // if chan already exist and user is not in chan then check if there is a limit and if it's invite only
		if(isInvite && isLimit && isKey){
			string errorMsgLim = ERR_CHANNELISFULL(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgLim.c_str(), errorMsgLim.length(), 0);
			string errorMsgInv = ERR_INVITEONLYCHAN(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgInv.c_str(), errorMsgInv.length(), 0);
			_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),channelName));
		} else if (isInvite && isLimit) {
			string errorMsgLim = ERR_CHANNELISFULL(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgLim.c_str(), errorMsgLim.length(), 0);
			string errorMsgInv = ERR_INVITEONLYCHAN(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgInv.c_str(), errorMsgInv.length(), 0);
		} else if (isInvite && isKey){
			string errorMsgInv = ERR_INVITEONLYCHAN(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgInv.c_str(), errorMsgInv.length(), 0);
			_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),channelName));
		
		 }else if(isLimit && isKey){
			string errorMsgLim = ERR_CHANNELISFULL(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgLim.c_str(), errorMsgLim.length(), 0);
			_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),channelName));
		} else if (isLimit){ // check if arg is only digit
			string errorMsg = ERR_CHANNELISFULL(client.getNickname(), channelName);
			send(client.getSocket(), errorMsg.c_str(), errorMsg.length(), 0);

		} else if (isInvite) {
			string errorMsg = ERR_INVITEONLYCHAN(client.getNickname(), channelName);
			send(client.getSocket(), errorMsg.c_str(), errorMsg.length(), 0);
		} else if (isKey){ //arg[1] is the channel key
				_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),channelName));
		} else {
			_channels[channelName].setTopicNickname(_clients[socket].getNickname());
			if (_channels[channelName].getTopic() == "")
				_clients[socket].sendMessage(RPL_NOTOPIC(_channels[channelName].getTopicNickname(), channelName));
			else
				_clients[socket].sendMessage(RPL_TOPIC(_channels[channelName].getTopicNickname(), channelName, _channels[channelName].getTopic()));
        	_channels[channelName].addUser(_clients[socket].getNickname(), socket);
			_channels[channelName].removeGuest(_clients[socket].getNickname());
			_channels[channelName].broadcast(JOIN(_clients[socket].getNickname(), _clients[socket].getUser(), channelName));
			broadcastJoin(socket, arg);
		}
    } else {
        string errorMsg = ERR_USERONCHANNEL(client.getNickname(), channelName, client.getNickname());
		send(client.getSocket(), errorMsg.c_str(), errorMsg.length(), 0);
    	}
	}
}
