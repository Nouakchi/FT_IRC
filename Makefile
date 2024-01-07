# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 00:53:25 by onouakch          #+#    #+#              #
#    Updated: 2024/01/06 12:50:10 by heddahbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME	=	ircserv
CPP		=	c++
RM		=	rm -rf
FLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address

INCLUDES	=	includes/irc.h		\
				models/Client.hpp	\
				models/Channel.hpp	\

SRCS	=	main.cpp \
			$(wildcard models/*.cpp) \
			$(wildcard utils/*.cpp) \
			$(wildcard commands/*.cpp) \
			$(wildcard server/*.cpp) \
			

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
