#ifndef _CHANNEL_HPP_
#define _CHANNEL_HPP_

#include "includes.hpp"

class Channel{
	public : 
		Channel(string name);
		void	addUser(int);

	private :
		string _name;
		set<int> _users;
};

#endif