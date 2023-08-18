# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanthoma <yanthoma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 15:45:58 by yanthoma          #+#    #+#              #
#    Updated: 2023/08/18 17:00:33 by yanthoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS	=   commands/0-Command.cpp client.cpp channel.cpp commands/Nick.cpp commands/Pass.cpp\
 			commands/Join.cpp commands/Mode.cpp commands/Part.cpp commands/Privmsg.cpp\
			commands/Kick.cpp\
			commands/Invite.cpp commands/Topic.cpp\
			 server.cpp main.cpp\


SRCDIR		= srcs/
OBJDIR 		= objs
OBJS		= ${addprefix ${OBJDIR}/, ${SRCS:.cpp=.o}}
INC			= inc/
CINC		= -I ./inc/ -I ./inc/commands/

# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */

CC		= c++
CFLAGS	= -g -Wall -Wextra -Werror -std=c++98
NAME	= ircserv	
RM		= rm -rf

all:		${NAME}

${OBJDIR}/%.o : ${SRCDIR}%.cpp ${INC}
				@echo "\e[1;32mFT_IRC [COMPILING...]\e[0m"
				@mkdir -p $(dir $@)
				@${CC} ${CFLAGS} ${CINC} -c $< -o $@

${NAME}:	${OBJS}
			@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
			@echo "\e[1;34mFT_IRC [READY]\e[0m"

clean:
			@${RM} ${OBJS}${OBJDIR}
			@echo "\e[1;31mFT_IRC [CLEAN]\e[0m"

fclean:		
			@${RM} ${OBJS} ${OBJDIR}
			@${RM} ${NAME}
			@echo "\e[1;31mFT_IRC [ALL CLEAN]\e[0m"

re:			fclean all

.PHONY: 	all clean fclean re


