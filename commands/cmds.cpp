/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:00:24 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/23 11:33:10 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

void LogtimeBot(t_server *server, Client *clt)
{
	std::string CltJointime = std::to_string(clt->getcltsrvrJointime());

	std::map<int , Client*>::iterator it = server->clients.begin();
	while (it != server->clients.end())
	{
		if (it->second->getNickName() == "BOT")
		{
			std::cout << ">> " + clt->getNickName() + " | ";
			std::string arg = "LOGTIME " + clt->getNickName()+ " " + CltJointime.c_str();
			send(it->second->getSocket(), arg.c_str(), arg.size(), 0);
			break;
		}
		it++;
	}

	if (it == server->clients.end())
	{
		std::cout << "Bot not Connected\n";
		return ;
	}
	return ;
}

void    ft_parseCommand( t_server *server, Client *clt, std::string buff )
{
    std::string                 token;
    std::vector<std::string>    items;
    std::stringstream           ss(buff);
    buff.pop_back();
    if (buff.find("\r") != std::string::npos)
        buff.pop_back();
    
    std::cout << "\n	::::	" << buff << "	:::::\n";
    while (ss >> token)
    {
        if (token[0] == ':' && token.length() > 1)
        {
            items.push_back(buff.substr(buff.find(":"), buff.length()));
            break;
        }
        items.push_back(token);
    }

    if (items.size() >= 1)
    {
        if (items[0] == "JOIN")
            ft_joinCmd(server, clt, items);
        else if (items[0] == "PART")
            ft_partCmd(server, clt, items);
        else if (items[0] == "KICK")
            ft_kickCmd(server, clt, items);
        else if (items[0] == "INVITE")
            ft_inviteCmd(server, clt, items);
        else if (items[0] == "TOPIC")
            ft_topicCmd(server, clt, items);
        else if (items[0] == "PRIVMSG" || items[0] == "NOTICE")
            ft_privmsg(server, clt, items);
        else if (items[0] == "MODE")
            ft_modeCmd(server, clt, buff);
        else if (items[0] == "LOGTIME")
            LogtimeBot( server, clt );
    }
}
