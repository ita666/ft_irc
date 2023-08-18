#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"



void	Server::Join(int socket, vector<string>& arg, Client client){
	
	(void)socket;
	string channelName = arg[0];
	cout << "join " << arg[0] << " \n";
	cout << "SODFIJSOIDFJ " << client.getNickname() << "\n";
	cout << "FDOSIFJ BIS " << _clients[socket].getNickname() << "\n";
	

	//cout << "test join " << (_channels.find(arg[0]) == _channels.end()) << "\n";
	if (_channels.find(channelName) == _channels.end()){ // if the chan does not exist create it and add the user and give him the operator right
		_channels[channelName] = Channel (channelName);

		cout << " join name " << _channels[channelName].getName() << " \n";
		_channels[channelName].setName(channelName);
		_channels[channelName].addUser(client.getNickname(), client.getSocket());
		_clients[socket].setUMode();
		_clients[socket].sendMessage(RPL_NOTOPIC(_channels[channelName].getTopicNickname(), channelName));
		cout <<"channel user "<< client.getNickname() << "\n";
	} else {

	bool isInvite = (_channels[channelName].isInviteOnly(client.getNickname()) == true);
	bool isKey = (arg.size() < 2 && (_channels[channelName].getCMode() & k) == k && arg[1] != _channels[channelName].getKey());
	bool isLimit = ((_channels[channelName].getCMode() & l) == l && _channels[channelName].getMap().size() >= _channels[channelName].getLimit());

    if (!_channels[channelName].isUserInChannel(client.getUser())) { // if chan already exist and user is not in chan then check if there is a limit and if it's invite only
		if(isInvite && isLimit && isKey){
			
			cout << "isinviteonly value" << _channels[channelName].isInviteOnly(client.getNickname()) << "\n";
			cout << "islimit value" << _channels[channelName].getLimit() << "\n";
			cout << "iskey value" << _channels[channelName].getKey() << "\n";

			string errorMsgLim = ERR_CHANNELISFULL(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgLim.c_str(), errorMsgLim.length(), 0);
			string errorMsgInv = ERR_INVITEONLYCHAN(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgInv.c_str(), errorMsgInv.length(), 0);
			_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),channelName));
		} else if (isInvite && isLimit) {

			cout << "isinviteonly value" << _channels[channelName].isInviteOnly(client.getNickname()) << "\n";
			cout << "islimit value" << _channels[channelName].getLimit() << "\n";

			string errorMsgLim = ERR_CHANNELISFULL(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgLim.c_str(), errorMsgLim.length(), 0);
			string errorMsgInv = ERR_INVITEONLYCHAN(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgInv.c_str(), errorMsgInv.length(), 0);
		} else if (isInvite && isKey){

			cout << "isinviteonly value" << _channels[channelName].isInviteOnly(client.getNickname()) << "\n";
			cout << "iskey value" << _channels[channelName].getKey() << "\n";

			string errorMsgInv = ERR_INVITEONLYCHAN(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgInv.c_str(), errorMsgInv.length(), 0);
			_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),channelName));
		
		 }else if(isLimit && isKey){

			cout << "islimit value" << _channels[channelName].getLimit() << "\n";
			cout  << "iskey value" << _channels[channelName].getKey() << "\n";

			string errorMsgLim = ERR_CHANNELISFULL(client.getNickname(), channelName);
			send(client.getSocket(), errorMsgLim.c_str(), errorMsgLim.length(), 0);
			_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),channelName));
		} else if (isLimit){ // check if arg is only digit

			cout << "islimit value" << _channels[channelName].getLimit() << "\n";

			string errorMsg = ERR_CHANNELISFULL(client.getNickname(), channelName);
			send(client.getSocket(), errorMsg.c_str(), errorMsg.length(), 0);

		} else if (isInvite) {

			cout << "isinviteonly value" << _channels[channelName].isInviteOnly(client.getNickname()) << "\n";

			string errorMsg = ERR_INVITEONLYCHAN(client.getNickname(), channelName);
			send(client.getSocket(), errorMsg.c_str(), errorMsg.length(), 0);
		} else if (isKey){ //arg[1] is the channel key

				cout << "need the chan key\n";

				_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),channelName));
		} else {
			_channels[channelName].setTopicNickname(client.getNickname());
			if (_channels[channelName].getTopic() == "")
				_clients[socket].sendMessage(RPL_NOTOPIC(_channels[channelName].getTopicNickname(), channelName));
			else
				_clients[socket].sendMessage(RPL_TOPIC(_channels[channelName].getTopicNickname(), channelName, _channels[channelName].getTopic()));
        	_channels[channelName].addUser(client.getNickname(), client.getSocket());
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
