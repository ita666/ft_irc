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
		
		// setters
		void					setName(string&);
		void					setTopic(string);
		void					setLimit(string);
		void					setTopicNickname(const string);
		void					setKey(string&);
		void					unsetKey();
		void					setCMode(char);
		void					removeCMode(char);

		// getters
		const string			getName() const;
		const string			getKey() const;
		const string			getTopic() const;
		const string			getTopicNickname() const;
		size_t					getLimit();
		int						getSocket(string& );
		vector<int>				getAllUsers();
		vector<string>			getAllNickname();
		string					getName(int);
		map<string, int>		getMap();
		MODES					getCMode();

		// methods
		void					addGuest(const string& nickname);
		void					removeGuest(const string& nickname);
		void					addUser(const string, int);
		void					removeUser(const string, int);
		string					findInvited(string& guest);
		bool					isUserInChannel(const string& username);
		bool					isInviteOnly(const string& nickname);
		bool					isEmpty();
		void					broadcast(string msg);

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