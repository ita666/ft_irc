#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include "includes.hpp"
#include "define.hpp"

class Client{
	public : 
		Client() : _socket(-1), _nickname(""), _username(""), _hostname("IRC_HELL"), _iswelcomed(false){}
		Client(int socket);
		~Client();

		int		getSocket();
		string&	getNickname();
		string&	getUser();
		string& getHost();
		bool	getIsWelcomed();
		string& getPassword();
		string	getUMode();

		void	setUser(string user);
		void	setNickname(string nickname);
		void	setIsWelcomed(bool);
		void	setPassword(string);
		void	setUMode(char);
		
		void	removeUMode(char);
		bool	isReady();
		void	sendMessage(const string& message);

	private	:
		int		_socket;
		string 	_nickname;
		string	_username;
		string	_hostname;
		string	buffer;
		string	_password;
		bool	_iswelcomed;
		MODES   _userMode;
};
#endif