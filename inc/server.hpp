#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include	"includes.hpp"
#include	"command.hpp"
#include	"channel.hpp"

class Server: public Command{
	public : 
		Server(void);
		Server(char *, char *);
		~Server(void);
		void	setPort(char *);
		void	acceptClient();
		void	initServ();
		void	handleClient(int);
		// removeClient();
		// passwordAuth(int client_socket);
		void	runServ();

	//commands
		void	Invite();
		void	Join(int socket, string channel);
		void	Mode();
		void	Nick();
		void	Pass();
		void	Ping();
		void	Privmsg();
		void	Topic();
		void	Whois();

	private:
		int					_port;
		string				_password;
		int					_server_socket;
		struct sockaddr_in	_server_address;
		fd_set				_master_set;
		vector<int>			_client_sockets;
		std::map<std::string, Channel> _channels;

};

#endif