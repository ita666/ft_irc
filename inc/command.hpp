#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include "includes.hpp"
#include "client.hpp"

class Server; 

class Command{
	public :
		Command();
		virtual ~Command();
		vector<string> getCommand(string);
		void	handleCommand(int socket, vector<string> split, Server& server);
		void	initMap();
	protected :
		typedef void (Server::*commandFunc)(int, vector<string>&); // go to chatgpt
		map<string, commandFunc> _commands; //same


};


#endif