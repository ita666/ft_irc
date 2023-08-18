#include "server.hpp"
#include "channel.hpp"
#include "define.hpp"

void	broadcastJoin(int socket, vector<string>& arg) {
	string channelName = arg[0];
	string currentClientNickname = _clients[socket].getNickname();
	string currentClientUsername = _clients[socket].getUser();
	_channels[channelName].getAll
}

void	Server::Join(int socket, vector<string>& arg, Client client){
	
	(void)socket;
	cout << "join " << arg[0] << " \n";
	cout << "SODFIJSOIDFJ " << client.getNickname() << "\n";
	cout << "FDOSIFJ BIS " << _clients[socket].getNickname() << "\n";

	

	//cout << "test join " << (_channels.find(arg[0]) == _channels.end()) << "\n";
	if (_channels.find(arg[0]) == _channels.end()){ // if the chan does not exist create it and add the user and give him the operator right
		_channels[arg[0]] = Channel (arg[0]);

		cout << " join name " << _channels[arg[0]].getName() << " \n";
		_channels[arg[0]].setName(arg[0]);
		_channels[arg[0]].addUser(client.getNickname(), client.getSocket());
		_clients[socket].setUMode();
		_clients[socket].sendMessage(RPL_NOTOPIC(_channels[arg[0]].getTopicNickname(), arg[0]));
		cout <<"channel user "<< client.getNickname() << "\n";
	} else {
		
		bool isInvite = (_channels[arg[0]].isInviteOnly(client.getNickname()) == true);
		bool isKey = (arg.size() < 2 && (_channels[arg[0]].getCMode() & k) == k && arg[1] != _channels[arg[0]].getKey());
		bool isLimit = ((_channels[arg[0]].getCMode() & l) == l && _channels[arg[0]].getMap().size() >= _channels[arg[0]].getLimit());

    if (!_channels[arg[0]].isUserInChannel(client.getUser())) { // if chan already exist and user is not in chan then check if there is a limit and if it's invite only
		if(isInvite && isLimit && isKey){
			
			cout << "isinviteonly value" << _channels[arg[0]].isInviteOnly(client.getNickname()) << "\n";
			cout << "islimit value" << _channels[arg[0]].getLimit() << "\n";
			cout << "iskey value" << _channels[arg[0]].getKey() << "\n";

			string errorMsgLim = ERR_CHANNELISFULL(client.getNickname(), arg[0]);
			send(client.getSocket(), errorMsgLim.c_str(), errorMsgLim.length(), 0);
			string errorMsgInv = ERR_INVITEONLYCHAN(client.getNickname(), arg[0]);
			send(client.getSocket(), errorMsgInv.c_str(), errorMsgInv.length(), 0);
			_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),arg[0]));
		} else if (isInvite && isLimit) {

			cout << "isinviteonly value" << _channels[arg[0]].isInviteOnly(client.getNickname()) << "\n";
			cout << "islimit value" << _channels[arg[0]].getLimit() << "\n";

			string errorMsgLim = ERR_CHANNELISFULL(client.getNickname(), arg[0]);
			send(client.getSocket(), errorMsgLim.c_str(), errorMsgLim.length(), 0);
			string errorMsgInv = ERR_INVITEONLYCHAN(client.getNickname(), arg[0]);
			send(client.getSocket(), errorMsgInv.c_str(), errorMsgInv.length(), 0);
		} else if (isInvite && isKey){

			cout << "isinviteonly value" << _channels[arg[0]].isInviteOnly(client.getNickname()) << "\n";
			cout << "iskey value" << _channels[arg[0]].getKey() << "\n";

			string errorMsgInv = ERR_INVITEONLYCHAN(client.getNickname(), arg[0]);
			send(client.getSocket(), errorMsgInv.c_str(), errorMsgInv.length(), 0);
			_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),arg[0]));
		
		 }else if(isLimit && isKey){

			cout << "islimit value" << _channels[arg[0]].getLimit() << "\n";
			cout  << "iskey value" << _channels[arg[0]].getKey() << "\n";

			string errorMsgLim = ERR_CHANNELISFULL(client.getNickname(), arg[0]);
			send(client.getSocket(), errorMsgLim.c_str(), errorMsgLim.length(), 0);
			_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),arg[0]));
		} else if (isLimit){ // check if arg is only digit

			cout << "islimit value" << _channels[arg[0]].getLimit() << "\n";

			string errorMsg = ERR_CHANNELISFULL(client.getNickname(), arg[0]);
			send(client.getSocket(), errorMsg.c_str(), errorMsg.length(), 0);

		} else if (isInvite) {

			cout << "isinviteonly value" << _channels[arg[0]].isInviteOnly(client.getNickname()) << "\n";

			string errorMsg = ERR_INVITEONLYCHAN(client.getNickname(), arg[0]);
			send(client.getSocket(), errorMsg.c_str(), errorMsg.length(), 0);
		} else if (isKey){ //arg[1] is the channel key

				cout << "need the chan key\n";

				_clients[socket].sendMessage(ERR_BADCHANNELKEY(_clients[socket].getNickname(),arg[0]));

		} else {
			_channels[arg[0]].setTopicNickname(client.getNickname());
			if (_channels[arg[0]].getTopic() == "")
				_clients[socket].sendMessage(RPL_NOTOPIC(_channels[arg[0]].getTopicNickname(), arg[0]));
			else
				_clients[socket].sendMessage(RPL_TOPIC(_channels[arg[0]].getTopicNickname(), arg[0], _channels[arg[0]].getTopic()));
        	_channels[arg[0]].addUser(client.getNickname(), client.getSocket());
			_channels[arg[0]].removeGuest(_clients[socket].getNickname());
			_channels[arg[0]].broadcast(JOIN(_clients[socket].getNickname(), _clients[socket].getUser(), arg[0]));
		}
    } else {
        string errorMsg = ERR_USERONCHANNEL(client.getNickname(), arg[0], client.getNickname());
		send(client.getSocket(), errorMsg.c_str(), errorMsg.length(), 0);
    	}
	}
}
