#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include "includes.hpp"
#include "define.hpp"

class Client {
	public : 
		Client();
		Client(int socket);
		~Client();
		Client&	operator=(Client const &other);

		// setters
		void			setUser(string user);
		void			setNickname(string nickname);
		void			setHost(string host);
		void			setIsWelcomed(bool);
		void			setPassword(string);
		void			setUMode();
		void			unsetUMode();
		void			setIMode();

		// getters
		int				getSocket();
		const string	getNickname() const;
		const string	getUser() const;
		const string	getHost() const;
		const string	getRealhost() const;
		const string	getPassword() const;
		const string	getUMode() const;
		bool			getIsWelcomed();

		// methods
		bool	isReady();
		void	sendMessage(const string& message);
		bool	checkRight();

	private	:
		int		_socket;
		bool	_iswelcomed;
		string 	_nickname;
		string	_username;
		string	_hostname;
		string	_realhost;
		string	_password;
		MODES   _userMode;
};

#endif