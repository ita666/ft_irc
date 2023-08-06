#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include "includes.hpp"

class Client{
	public : 
		Client() : _socket(-1), _nickname(""), _username(""), _hostname("IRC_HELL") {}
		Client(int socket);
		~Client();

		int		getSocket();
		string&	getNickname();
		string&	getUser();
		string& getHost();
		bool	getIsWelcomed();
		void	setUser(string user);
		void	setNickname(string nickname);
		void	setIsWelcomed(bool);

		bool	isReady();

	private	:
		int		_socket;
		string 	_nickname;
		string	_username;
		string	_hostname;
		string	buffer;
		bool	_iswelcomed;
};
#endif