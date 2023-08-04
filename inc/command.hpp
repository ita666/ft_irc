#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include "includes.hpp"

class Command{
	public :
		Command();
		virtual ~Command();
		vector<string>& getCommand(string);
		void	handleCommand(int socket, vector<string>&);
		void	initMap();
	protected :
		//map<string, void (*)(int, vector<string>)> _commands;
		map<string, void (*)(int, std::vector<std::string>&)> _commands;
		

};


#endif