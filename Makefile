# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 00:53:25 by onouakch          #+#    #+#              #
#    Updated: 2023/12/19 20:57:52 by aaoutem-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME	=	ircserv
CPP		=	c++
RM		=	rm -rf 
# FLAGS	=	-Wall -Wextra -Werror -std=c++98


INCLUDES	=	Server.hpp irc.hpp
SRCS	=	irc.cpp \
			Server.cpp

OBJS	=	$(SRCS:%.cpp=%.o)

all:	$(NAME)

$(NAME) : $(OBJS)
	$(CPP) $(OBJS) -o $@

%.o : %.cpp $(INCLUDES)
	$(CPP) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
