#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include	"includes.hpp"
#include	"command.hpp"
#include	"channel.hpp"
#include	"client.hpp"

class Server: public Command{
	public : 
		Server(void);
		Server(char *, char *);
		~Server(void);
		void	setPort(char *);
		void	acceptClient();
		void	initServ();
		void	handleClient(int);
		bool	nicknameAlreadyUsed(string name, Client cl);
		// removeClient();
		// passwordAuth(int client_socket);
		void	runServ();

	//commands
		void	Invite();
		void	Join(int socket, string channel);
		void	Mode();
		void	Pass();
		void	Ping();
		void	Privmsg();
		void	Topic();
		void	Whois();
		void	Nick(int socket, vector<string>& arg);
    	void	User(int socket, vector<string>& arg);

	private:
		int					_port;
		string				_password;
		int					_server_socket;
		struct sockaddr_in	_server_address;
		fd_set				_master_set;
		map<int, Client>	_clients; // a map of client with their info to handle them the key is the socket
		map<std::string, Channel> _channels; // to store the future channel name and check if they already exist

};

#endif