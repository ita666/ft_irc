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
   // string partingMessage =  arg[0] + _clients[socket].getNickname() + " has left the channel";
    //cout << "parting message " << partingMessage << "\n";
    //_channels[arg[0]].broadcast(partingMessage);
    _channels[arg[0]].removeUser(_clients[socket].getNickname(), _clients[socket].getSocket());
   // _clients[socket].sendMessage(ERR_NOTONCHANNEL(_clients[socket].getNickname(), arg[0]));
    string msg = ":" + _clients[socket].getNickname() + "!" + _clients[socket].getUser() + "@" + _clients[socket].getRealhost() +" PART " + arg[0] + "\r\n";
    cout << msg << "\n";
    if (send(socket, msg.c_str(), msg.length(), 0)< 0)
        cout << "error send\n";

    // Broadcast parting message to all channel members
    //channel[arg[1]].broadcastMessage(partingMessage);

    // If the channel is empty, destroy it
    if (_channels[arg[1]].isEmpty()) {
		_clients[socket].sendMessage(ERR_NOUSERLEFT(client.getNickname(), arg[0]));
        _channels.erase(arg[0]); 
    }
}


// msg = ":" + users[cfd].nick + "!" + users[cfd].user;
// 			msg += "@localhost PART " + cmd[1] + "\r\n";



// #include "Server.hpp"

// int	Server::part(User *user, std::vector<std::string> args)
// {
// 	std::vector<std::string> canals;
// 	Canal	*canal;
// 	std::string	message = "";


// 	if (args.size() < 2)
// 	{
// 		user->send_code(ERR_NEEDMOREPARAMS, ":Usage: /part <channel>");
// 		return 1;
// 	}
// 	if (args.size() >= 3)
// 	{
// 		message = " ";
// 		for (unsigned int i = 2; i < args.size(); i++)
// 		{
// 			message = message + args[i];
// 		}
// 	}
// 	canals = split(args[1], ',');
// 	for (std::vector<std::string>::iterator it = canals.begin(); it != canals.end(); it++)
// 	{
// 		canal = get_canal(*it);
// 		if (!canal)
// 		{
// 			user->send_code(ERR_NOSUCHCHANNEL, ":This channel doesn't exist.");
// 			continue;
// 		}
// 		if (canal->checkUser(user->getFd()) == 0)
// 		{
// 			user->send_code(ERR_NOTONCHANNEL, ":You are not on this channel.");
// 			continue;
// 		}
// 		canal->broadcast(user, "PART " + *it + message);
// 		canal->removeUser(*user);
// 	}
// 	return 0;
// }