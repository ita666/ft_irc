#include "server.hpp"
#include "define.hpp"


void	Server::Pass(int socket, vector<string>& arg, Client client){
	(void)client;
	(void)arg;
	(void)socket;

	//check if pass is operator password if so grant operator mode to the client
	// and let him through 
	if(!arg[0].compare(OPERATOR_PASSWORD)){
		client.sendMessage(RPL_YOUROPER());
		return ;
	}

	if(!arg[0].compare(_password)){ return ; }

	//send error message avoid sending the welcom msg;
	// delete the socket;
	client.sendMessage(ERR_PASSWDMISMATCH());
}