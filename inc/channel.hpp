#ifndef _CHANNEL_HPP_
#define _CHANNEL_HPP_

#include "includes.hpp"

class Channel{
	public : 
		Channel(string name);
		string	getName();
		void	setName();


	private :
		string _name;
		set<int> _users; //
};

#endif 