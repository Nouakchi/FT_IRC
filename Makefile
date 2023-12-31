# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 00:53:25 by onouakch          #+#    #+#              #
#    Updated: 2023/12/30 16:35:22 by onouakch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME	=	ircserv
CPP		=	c++
RM		=	rm -rf
FLAGS	=	-Wall -Wextra -Werror -std=c++98

INCLUDES	=	includes/irc.h		\
				models/Client.hpp	\
				models/Channel.hpp	\

SRCS	=	main.cpp					\
			server/server.cpp			\
			server/authentication.cpp	\
			server/check_authInfo.cpp	\
			server/events.cpp			\
			utils/utils.cpp				\
			models/Client.cpp			\
			models/Channel.cpp			\
			commands/cmds.cpp			\
			commands/join.cpp			\

OBJS	=	$(SRCS:%.cpp=%.o)

all:	$(NAME)

$(NAME) : $(OBJS)
	$(CPP) $(FLAGS) $(OBJS) -o $@

%.o : %.cpp $(INCLUDES)
	$(CPP) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
