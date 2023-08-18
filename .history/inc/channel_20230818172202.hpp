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
		void	setTopic(string);

		string&	getKey();
		void	setKey(string&);
		void	unsetKey();

		size_t&	getLimit();
		void	setLimit(string);

		string& getTopicNickname();
		void	setTopicNickname(string&);

		MODE

		map<string, int>&		getMap();
		MODES	getCMode();
		void	setCMode(char);
		void	removeCMode(char);

		void	addGuest(const string& nickname);
		void	removeGuest(const string& nickname);

		void	addUser(string&, int);
		void	removeUser(string&, int);
		string	findInvited(string& guest);
		bool	isUserInChannel(const string& username);
		bool	isInviteOnly(const string& nickname);
		bool	isEmpty();
		int		getSocket(string& );
		int*	getAllUsers();
		string	getName(int);

		void	broadcast(string msg);

	private :
		string				_topicNickname;	
		string				_name;
		string				_topic;
		string				_key;
		size_t				_limit;
		vector<string>		_invited;
		map<string, int>	_nameToSocket;
		map<int, string>	_socketToName;
		MODES				_chanMode;
};

#endif 