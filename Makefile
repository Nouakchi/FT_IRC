# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 00:53:25 by onouakch          #+#    #+#              #
#    Updated: 2023/12/27 03:16:00 by aaoutem-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME	=	serv
CPP		=	c++
RM		=	rm -rf 
# FLAGS	=	-Wall -Wextra -Werror -std=c++98


INCLUDES	=	Server.hpp irc.hpp
SRCS	=	irc.cpp Server.cpp ServerUtils.cpp UserAuth.cpp utils_kadigh.cpp \
			IRCEntities/Client.cpp 

# OBJS	=	$(SRCS:%.cpp=%.o)
all : $(SRCS)
	$(CPP) $(SRCS) -o $(NAME)
# all:	$(NAME)

# $(NAME) : $(OBJS)
# 	$(CPP) $(OBJS) -o $@

# %.o : %.cpp $(INCLUDES)
# 	$(CPP) -c $< -o $@

clean:
	$(RM) $(NAME)

# fclean:	clean
# 	$(RM) $(NAME)

# re: fclean all

.PHONY: all clean fclean re
