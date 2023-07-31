#ifndef _USER_HPP_
#define _USER_HPP_

#include "includes.hpp"

struct User
{
	private:
		int			cfd;
		bool		g_oper;
		std::string	user;
		std::string	nick;
		std::string	host;
};

#endif
