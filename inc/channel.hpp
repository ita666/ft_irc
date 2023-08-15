#ifndef _CHANNEL_HPP_
#define _CHANNEL_HPP_

#include "includes.hpp"
#include "client.hpp"
#include "server.hpp"

class Channel {
	public : 
		
		Channel();
		Channel(string name);
		~Channel();

		vector<string> ban;
		
		string	getName();
		void	setName(string&);

		string	getTopic();
		void	setTopic(string& );

		string&	getKey();
		void	setKey(string&);

		int&	getLimit();
		void	setLimit(int);

		string	getCMode();
		void	setCMode(char);
		void	removeCMode(char);

		void	addUser(string&, int);
		void	removeUser(string&, int);
		bool	isUserInChannel(const string& username);
		bool	isEmpty();
		int		getSocket(string& );
		int*	getAllUsers();
		string	getName(int);	
	private :
		string				_name;
		string				_topic;
		string				_key;
		int					_limit;
		map<string, int>	_nameToSocket;
		map<int, string>	_socketToName;
		MODES				_userMode;
};

#endif 