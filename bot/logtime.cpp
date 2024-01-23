/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logtime.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:37:07 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/23 12:30:56 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"
#include <sys/types.h>
#include <sys/socket.h>


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

int ft_error(std::string msg)
{
	std::cout << msg << std::endl;
	return (EXIT_FAILURE);
}
int parse_pwd( char *pwd )
{
    int i = -1;
    if(strlen(pwd) < 1)
        return (ft_error("Password must be at least 1 char long !!"));
    while (pwd[++i])
        if (isspace(pwd[i]))
            return (ft_error("Password must not contain spaces !!"));
    return (EXIT_SUCCESS);
}

std::string	loggedTime(std::string joinTimeStr)
{
	std::time_t jointime  = atol(joinTimeStr.c_str());
	std::time_t currenttime = std::time(NULL);
	std::time_t difftime =  currenttime - jointime;
	std::cout << "currenttime: " << currenttime << std::endl;
	std::cout << "jointime: " << jointime << std::endl;

	int days = difftime / 86400;
	int restSeconds = difftime % 86400; 
	int hours = restSeconds / 3600;
	int minutes = (restSeconds % 3600) / 60;
	int seconds = restSeconds % 60;
	
	std::string logtime = std::to_string(days) + " day "
		+ std::to_string(hours) +":"+ std::to_string(minutes) +":"+ std::to_string(seconds);

	return (logtime);
}

// int main(int ac, char **av)
int main(int ac, char **av)
{
	std::cout << "logtime" << std::endl;
	int botsock;
	struct  sockaddr_in serv_addr;
	
	char buff[512];
	std::string cmd;

	if(ac != 2)
		return (std::cout << "Usage: ./logtime <password>\n", 0);
	bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons( 6667 );

	botsock = socket(AF_INET, SOCK_STREAM, 0);
	if (botsock == -1)
	{
		std::cout << "Error creating socket\n";
		return (0);
	}
	int n = connect(botsock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (n < -1)
		return (std::cout << "Error connecting\n", 0);
	
	cmd = "PASS " + std::string(av[1]) + "\r\n";
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
	// std::cout << buff << std::endl;

	bzero(buff, sizeof(buff));

	std::string logtime;
	std::string replay;
	
	std::vector<std::string> items;
	while (true)
	{
		/*
			the probleme here is that the BOT is a clieent so it could recieve private msgs and kayferbal
			if soo we should make somthg for it soit 
			we should ignore the (PRIVMSG BOT :msg) 
			so to avoid another user register with a BOT nickname we should make BOT NickName reserved and the BOT couldnt 
		*/
		recv(botsock, (void *)buff, sizeof(buff), 0); // ignore the Private msgs to the BOT or 
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
		// std::cout <<"[" + items[0]+ " | "+ logtime +"]" << std::endl;
		replay = "PRIVMSG " + items[1] + " :You Logged for " + logtime + "\r\n";
		send(botsock, replay.c_str(), replay.size(), 0);
		items.clear();
	}
	return (0);
}
