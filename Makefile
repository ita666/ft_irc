# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fwong <fwong@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/06 15:45:58 by yanthoma          #+#    #+#              #
#    Updated: 2023/08/09 21:36:00 by fwong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS	=   commands/0-Command.cpp client.cpp commands/Nick.cpp commands/Privmsg.cpp server.cpp main.cpp

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
				mkdir -p $(dir $@)
				${CC} ${CFLAGS} ${CINC} -c $< -o $@

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}${OBJDIR}

fclean:		
			${RM} ${OBJS} ${OBJDIR}
			${RM} ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re


