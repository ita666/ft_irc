#ifndef _CHANNEL_HPP_
#define _CHANNEL_HPP_
#include "includes.hpp"
#includes "user.hpp"

struct Channel
{
	private
		bool						mode_inv;
		bool						mode_topic;
		size_t						mode_limit;
		std::string					chan_key;
		std::string					chan_topic;
		std::vector<User*>			chan_users;
		std::vector<int>			chan_operators;
		std::vector<std::string>	chan_invitees;
};

#endif