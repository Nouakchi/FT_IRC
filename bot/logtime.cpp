/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logtime.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:37:07 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/23 13:52:15 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"
#include <sys/types.h>
#include <sys/socket.h>

int ft_parse_port( char *port )
{
    int i = -1;
    while (port[++i])
        if (!isdigit(port[i]))
        {
	        std::cout << "Port must be between 0 and 65535 !!\n";
	    	return (EXIT_SUCCESS);
		}
    if(atoi(port) < 1024 || atoi(port) > 65535)
	{
        std::cout << "Port must be between 0 and 65535 !!\n";
	    return (EXIT_SUCCESS);
	}

    return (EXIT_SUCCESS);
}

void splitString(const std::string& cmd, std::vector<std::string>& substrs, char delim)
{
	std::istringstream iss(cmd);
	std::string token;
	std::string realname;

	while (std::getline(iss, token, delim)) {
		if (!token.empty())
			substrs.push_back(token);
	}

	return ;
}

std::string	loggedTime(std::string joinTimeStr)
{
	std::time_t currenttime = std::time(NULL);
	std::time_t jointime  = atol(joinTimeStr.c_str());
	std::time_t difftime =  currenttime - jointime;

	int days = difftime / 86400;
	int restSeconds = difftime % 86400; 
	int hours = restSeconds / 3600;
	int minutes = (restSeconds % 3600) / 60;
	int seconds = restSeconds % 60;
	
	std::string logtime = std::to_string(days) + " day "
		+ std::to_string(hours) +":"+ std::to_string(minutes) +":"+ std::to_string(seconds);

	return (logtime);
}

int main(int ac, char *av[])
{
	int botsock;
	struct  sockaddr_in serv_addr;

	char buff[512];
	std::string cmd;

	if(ac != 3)
		std::cout << "./ircbot <port> <password>\n";

	if (EXIT_FAILURE == ft_parse_port(av[1]))
        return (EXIT_FAILURE);

	int port = atoi(av[1]);

	bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( port );

	botsock = socket(AF_INET, SOCK_STREAM, 0);
	if (botsock == -1)
	{
		std::cout << "Error creating socket\n";
		return (0);
	}
	int n = connect(botsock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (n < -1)
		return (std::cout << "Error connecting\n", 0);

	cmd = "PASS " +std::string(av[2]) + "\r\n";
	send(botsock, cmd.c_str(), cmd.size(), 0);
	cmd = "NICK BOT\r\n";
	send(botsock, cmd.c_str(), cmd.size(), 0);
	cmd = "USER as as as as\r\n";
	send(botsock, cmd.c_str(), cmd.size(), 0);	
	
	ssize_t bytes  = recv(botsock, (void *)buff, sizeof(buff), 0);
	fcntl(botsock, F_SETFL, O_NONBLOCK);
	while (bytes > 0)
	{
		// std::cout << buff ;
		bzero(buff, sizeof(buff));
		bytes = recv(botsock, (void *)buff, sizeof(buff), 0);
	}

	bzero(buff, sizeof(buff));

	std::string logtime;
	std::string replay;
	std::vector<std::string> items;
	while (recv(botsock, (void *)buff, sizeof(buff), 0))
	{
		if (strlen(buff) == 0)
			continue ;
		splitString(buff, items, ' ');
		if (items[0] != "LOGTIME")
		{
			items.clear();
			continue;
		}
		bzero(buff, sizeof(buff));
		logtime = loggedTime (items[2]);
		replay = "PRIVMSG " + items[1] + " :You Logged for " + logtime + "\r\n";
		send(botsock, replay.c_str(), replay.size(), 0);
		items.clear();
	}
	return (0);
}
