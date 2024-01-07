# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 00:53:25 by onouakch          #+#    #+#              #
#    Updated: 2024/01/05 14:38:50 by onouakch         ###   ########.fr        #
=======
#    By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 00:53:25 by onouakch          #+#    #+#              #
#    Updated: 2024/01/06 12:50:10 by heddahbi         ###   ########.fr        #
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME	=	ircserv
CPP		=	c++
RM		=	rm -rf
<<<<<<< HEAD
FLAGS	=	-Wall -Wextra -Werror -std=c++98
=======
FLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)

INCLUDES	=	includes/irc.h		\
				models/Client.hpp	\
				models/Channel.hpp	\

<<<<<<< HEAD
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
			commands/part.cpp			\
			commands/privmsg.cpp		\
=======
SRCS	=	main.cpp \
			$(wildcard models/*.cpp) \
			$(wildcard utils/*.cpp) \
			$(wildcard commands/*.cpp) \
			$(wildcard server/*.cpp) \
			
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)

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
