#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include "includes.hpp"

class Command{
	public :
		Command();
		virtual ~Command();
		vector<string> getCommand(string);
	protected :
		map<string, void (*)(int, string)> Commands;

};


#endif