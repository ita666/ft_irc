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
		//void handleCommand(int socket, vector<string>& split, Server& server, map<int, Client>& clients);
		void	handleCommand(int socket, vector<string> split, Server& server);
		void	initMap();
	protected :
		//map<string, void (*)(int, vector<string>)> _commands;
		//map<string, void (*)(int, std::vector<std::string>&, Server& server)> _commands;
		// In Command.hpp
		typedef void (Server::*commandFunc)(int, vector<string>&);
		map<string, commandFunc> _commands;


};


#endif