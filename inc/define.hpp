#pragma once

// GENERAL
#define	SERVER_NAME "localhost"
#define OPERATOR_PASSWORD "oper"
#define MAX_EVENTS 10
#define VERSION "1"

/*--------------------------------------------COLORS--------------------------------------------*/

# define RESET "\e[0m"

//Regular text
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"

//Regular bold text
# define BRED "\e[1;31m"
# define BGRN "\e[1;32m"
# define BYEL "\e[1;33m"
# define BBLU "\e[1;34m"
# define BMAG "\e[1;35m"
# define BCYN "\e[1;36m"
# define BWHT "\e[1;37m"

/*----------------------------------------------------------------------------------------------*/

typedef enum e_modes
{ 
	i = 1 << 0, // 000001
	t = 1 << 1, // 000010
	k = 1 << 2, // 000100
	o = 1 << 3, // 001000
	l = 1 << 4, // 010000
}	MODES; // i + o -> 000110
//to set MODES userMode = i | o; add one : userModes |= r; remove userModes &= ~i; to check : if (userModes & o);

#define REPLY_FORMAT(num_rply_numb, nickname) (std::string(":") + SERVER_NAME + " " + num_rply_numb + " " + nickname + " ")
#define CLIENT_ID(nickname, username, command) (":" + nickname + "!" + username + "@" + SERVER_NAME + " " + command + " ")

// 000
#define RPL_WELCOME(nickname) (std::string(":") + SERVER_NAME + " 001 " + nickname + " :Welcome to the  " + SERVER_NAME  + " Server " + nickname + "\r\n")

// 200
#define RPL_UMODEIS(nickname, mode) (std::string(":") + SERVER_NAME + " 221 " + nickname + " " + mode + "\r\n")

// 300
#define RPL_WHOISUSER(nickname, username, hostname, realname) (std::string(":") + SERVER_NAME + " 311 " + nickname + " " + username + " " + hostname + " * :" + realname + "\r\n")
#define RPL_WHOISSERVER(nickname, servername, serverinfo) (std::string(":") + SERVER_NAME + " 312 " + nickname + " " + servername + " :" + serverinfo + "\r\n")
#define RPL_ENDOFWHOIS(nickname) (std::string(":") + SERVER_NAME + " 318 " + nickname + " :End of /WHOIS list" + "\r\n")
#define RPL_NOTOPIC(nickname, channel) (std::string(":") + SERVER_NAME + " 332 " + nickname + " " + channel + " :No topic is set" + "\r\n")
#define RPL_TOPIC(nickname, channel, topic) (std::string(":") + SERVER_NAME + " 332 " + nickname + " " + channel + " " + topic + "\r\n")
#define RPL_TOPICWHOTIME(nickname, channel, concerned_client_nickname, time) (std::string(":") + SERVER_NAME + " 333 " + nickname + " " + channel + " " + concerned_client_nickname + " " + time + "\r\n")
#define RPL_INVITING(nickname, target, channel) (std::string(":") + SERVER_NAME + " 341 " + nickname + " " + target + " " + channel + "\r\n")
#define RPL_NAMREPLY(nickname, channel, list_client) (std::string(":") + SERVER_NAME + " 353 " + nickname + " = " + channel + " :" + list_client  + "\r\n")
#define RPL_ENDOFNAMES(nickname, channel) (std::string(":") + SERVER_NAME + " 366 " + nickname + " " + channel + " :End of /NAMES list" + "\r\n")
#define RPL_INFO(nickname) (std::string(":") + SERVER_NAME + " 371 " + nickname + " :" + SERVER_NAME + "\r\n" + \
							":" + SERVER_NAME + " 371 " + nickname + " :" + "written by FKY" + "\r\n" + \
							":" + SERVER_NAME + " 371 " + nickname + " :" + "version 1.0" + "\r\n")
#define RPL_ENDOFINFO(nickname) (std::string(":") + SERVER_NAME + " 374 " + nickname + " " + ":End of /INFO list. " + "\r\n")
#define RPL_YOUROPER(nickname) (std::string(":") + SERVER_NAME + " 381 * "  + nickname  + " :is now an IRC operator" + "\r\n")

// 400
#define ERR_NOSUCHNICK(nickname, other_nickname) (std::string(":") + SERVER_NAME + " 401 " + nickname + " " + other_nickname  + " :No such nick\r\n" )
#define ERR_NOSUCHSERVER(nickname) (REPLY_FORMAT(" 402", nickname) + SERVER_NAME + " :" + "\r\n")
#define ERR_NOSUCHCHANNEL(nickname, channel) (std::string(":") + SERVER_NAME + " 403 " + nickname + " " + channel  + " :No such channel" + "\r\n" )
#define ERR_NOUSERLEFT(nickname, channel) (std::string(":") + SERVER_NAME + " 403 " + nickname + " " + channel  + " :No user left" + "\r\n" )
#define ERR_NOORIGIN(nickname) (std::string(":") + SERVER_NAME + " 409 " + nickname  + " :No origin\r\n")
#define ERR_NONICKNAMEGIVEN(nickname) (std::string(":") + SERVER_NAME + " 431 *" + nickname  + " :No nickname given\r\n")
#define ERR_ERRONEUSNICKNAME(nickname) (std::string(":") + SERVER_NAME + " 432 *" + nickname  +" Erroneus nickname\r\n")
#define ERR_NICKNAMEINUSE(nickname) ( std::string(":") + SERVER_NAME + " 433 * "  + nickname  + "\r\n")
#define ERR_USERNOTINCHANNEL(nickname, channel, concerned_client_nickname) (std::string(":") + SERVER_NAME + " 441 " + nickname + " " + concerned_client_nickname + " " + channel  + " :They aren't on that channel" + "\r\n" )
#define ERR_NOTONCHANNEL(nickname, channel) (std::string(":") + SERVER_NAME + " 442 " + nickname + " " + channel  + " :You're not on that channel" + "\r\n")
#define ERR_USERONCHANNEL(nickname, channel, concerned_client_nickname) (std::string(":") + SERVER_NAME + " 443 " + nickname + " " + concerned_client_nickname + " #" + channel  + " :is already on channel" + "\r\n" )
#define ERR_NOTREGISTERED(nickname, command) (std::string(":") + SERVER_NAME + " 451 " + nickname + " " + command  +" :You have not registered" + "\r\n" )
#define ERR_INVITEONLYCHAN(nickname, channel) (std::string(":") + SERVER_NAME + " 473 " + nickname + " " + channel  +" :Cannot join channel (+i)" + "\r\n" )
#define ERR_NEEDMOREPARAMS(nickname, command) (std::string(":") + SERVER_NAME + " 461 " + nickname + " " + command  + " :Not enough parameters\r\n" )
#define ERR_ALREADYREGISTRED(nickname) (std::string(":") + SERVER_NAME + " 462 " + nickname  + " :Already registred\r\n" )
#define ERR_PASSWDMISMATCH(nickname) (std::string(":") + SERVER_NAME + " 464 " + nickname  + " :Password incorrect" + "\r\n" )
#define ERR_CHANNELISFULL(nickname, channel) (REPLY_FORMAT("471", nickname) + channel  + " :Cannot join channel (+l)" + "\r\n" )
#define ERR_UNKNOWNMODE(command, message) (REPLY_FORMAT("472", command) + message  +" :is unknown mode char to me" + "\r\n" )

#define ERR_BADCHANNELKEY(nickname, channel) (REPLY_FORMAT("475", nickname) + channel  + " :Cannot join channel (+k)" + "\r\n" )
#define ERR_NOPRIVILEGES(nickname) (std::string(":") + SERVER_NAME + " 481 " + nickname  + " :Permission Denied - You're not an IRC operator" + "\r\n" )
#define ERR_CHANOPRIVSNEEDED(channel, nickname) (std::string(":") + SERVER_NAME + " 481 " + nickname + " " + channel  + " :channel has not this right" + "\r\n" )

#define ERR_UMODEUNKNOWNFLAG(nickname) (string(":") + SERVER_NAME + " 501 " + nickname  + " :Unknown MODE flag" + "\r\n" )
#define ERR_USERSDONTMATCH(nickname) (std::string(":") + SERVER_NAME + " 502 " + nickname  +" :Cant change mode for other users\r\n" )

// COMMANDS MACRO
#define PONG(nickname) (std::string(":") + SERVER_NAME + " PONG " + SERVER_NAME + " :" + SERVER_NAME + "\r\n")
#define NICK(nickname, username, new_nickname) (CLIENT_ID(nickname, username, "NICK") + ":"  + new_nickname  + "\r\n")
#define NOTICE(nickname, username, dest, msg) (CLIENT_ID(nickname, username, "NOTICE") + dest + " :" + msg + "\r\n")
#define TOPIC(nickname, username, channel, topic) (CLIENT_ID(nickname, username, "TOPIC") + channel + " "  + topic  + "\r\n")
#define PRIVMSG(nickname, username, dest, msg) (CLIENT_ID(nickname, username, "PRIVMSG") + dest + " :"  + msg  + "\r\n")
#define JOIN(nickname, username, channel) (CLIENT_ID(nickname, username, "JOIN") + ":" + channel  + "\r\n")
#define QUIT(nickname, username, message) (CLIENT_ID(nickname, username, "QUIT") + ":" + message + "\r\n")
#define KICK(nickname, username, channel, target, message) (CLIENT_ID(nickname, username, "KICK") + channel + " "  + target  + " :" + message + "\r\n")
#define PART(nickname, username, channel, message) (CLIENT_ID(nickname, username, "PART") + channel + " :" + message + "\r\n")
#define INVITE(nickname, username, target, channel) (CLIENT_ID(nickname, username, "INVITE") + target + " :" + channel + "\r\n")
#define MODE_USER(nickname, username, target, mode) (CLIENT_ID(nickname, username, "MODE") + target + " " + mode + "\r\n")
#define MODE_CHANNEL(nickname, username, channel, mode) (CLIENT_ID(nickname, username, "MODE") + channel + " " + mode + "\r\n")