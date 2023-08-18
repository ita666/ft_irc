#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include	"includes.hpp"
//#include	"command.hpp"
#include	"channel.hpp"
#include	"client.hpp"

extern bool running;

class Channel;

class Server{
	public : 
		Server(void);
		Server(char *, char *);
		~Server(void);


		void	setPort(char *);
		int		acceptClient();
		void	initServ();
		void	handleClient(int);
		bool	nicknameAlreadyUsed(string name, Client cl);
		bool	isNicknamePresent(string nickName);
		// removeClient();
		bool	passwordAuth(int socket);
		void	welcome(int socket);
		void	runServ();

		vector<string> getCommand(string);
		void	handleCommand(int socket, vector<string> split, Server& server, Client cl);
		void	initMap();

	//commands
		void	Invite(int socket, vector<string>& arg, Client);
		void	Join(int socket, vector<string>& arg, Client);
		void	Part(int socket, vector<string>& arg, Client);
		void	Mode(int socket, vector<string>& arg, Client);
		void	Pass(int socket, vector<string>& arg, Client);
		void 	Kick(int socket, vector<string>& arg, Client);
		void	Ping(int socket, vector<string>& arg, Client);
		void	Privmsg(int socket, vector<string>& arg, Client);
		void	Topic(int socket, vector<string>& arg, Client);
		void	Whois(int socket, vector<string>& arg, Client);
		void	Nick(int socket, vector<string>& arg, Client);
    	void	User(int socket, vector<string>& arg, Client);

		void	checkFlag(int socket, vector<string>& arg, int i, Client);
		bool	checkChannelName(string channelName);
		broadcastJoin(int socket, vector<string>& arg)

	private:
		int							_port;
		string						_password;
		int							_server_socket;
		struct sockaddr_in			_server_address;
		fd_set						_master_set;
		map<int, Client>			_clients; // a map of client with their info to handle them the key is the socket
		map<string, Client>			_stringToClients;
		map<string, Channel>		_channels; // to store the future channel name and check if they already exist
		typedef void (Server::*commandFunc)(int, vector<string>&, Client); // go to chatgpt
		map<string, commandFunc> _commands; //same
};

#endif