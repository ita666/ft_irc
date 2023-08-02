#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include "includes.hpp"

class Command{
	public :
		Command();
		~Command();
		vector<string> getCommand(string);
	private :
		map<string, void (*)(int, string)>;

};


#endif