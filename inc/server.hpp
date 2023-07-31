#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include  "includes.hpp"

class Server{
	public: 

	int	get_sock();
	int get_port();
	string get_password();
	

	private: 
		int sock;
		int port;
		string password;
		//map<int, ClientInfo> clients;
};

#endif