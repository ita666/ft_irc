#ifndef _CHANNEL_HPP_
#define _CHANNEL_HPP_

#include "includes.hpp"
#include "client.hpp"

class Channel{
	public : 
		Channel(string name);
		~Channel();

		string	getName();
		void	setName(string&);

		string	getTopic();
		void	setTopic(string& );

		void	addUser(string&, int);
		void	removeUser(string&, int);
		int		getSocket(string& );
		string	getName(int);	

	private :
		string _name;
		string _topic;
		map<string, int> _nameToSocket;
		map<int, string> _socketToName;
};

#endif 