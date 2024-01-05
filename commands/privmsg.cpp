/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:17:10 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/05 16:01:45 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

int     toChannel(t_server *server, Client *clt, std::string target, std::string msg_toSend)
{
    std::map<std::string, Channel*>::iterator it = server->channels.find(target);
    if (it == server->channels.end() || (it->second->users.find(clt->getNickName()) == it->second->users.end()
        &&  it->second->users.find("@" + clt->getNickName()) == it->second->users.end()))
		return (
			clt->reply(server->host_name, ERR_CANNOTSENDTOCHAN, target + " :Cannot send to channel"),
			EXIT_FAILURE
		);
    std::map<std::string, Client *>::iterator u_it = it->second->users.begin();
    while (u_it != it->second->users.end())
    {
        if (u_it->first.find(clt->getNickName()) == std::string::npos)
        {
            std::string msg = ":" + clt->getNickName() + "!" + clt->getLoginName() + "@" + server->host_name + " PRIVMSG " + target + " " + msg_toSend + " \r\n";
		    std::cout << "-*- " << msg;
		    send(u_it->second->getSocket(), msg.c_str(), msg.size(), 0);
        }
        u_it++;
    }
    return (EXIT_SUCCESS);
}

int     toUser(t_server *server, Client *clt, std::string target, std::string msg_toSend)
{
    if (server->nicknames.find(target) == server->nicknames.end())
        return (
			clt->reply(server->host_name, ERR_NOSUCHNICK, target + " :No such nick"),
			EXIT_FAILURE
		);
    std::map<int, Client*>::iterator u_it = server->clients.begin();
    std::cout << "[" << target << "]\n";
    while (u_it != server->clients.end())
    {
        if (u_it->second->getNickName() == target)
        {
            std::string msg = ":" + clt->getNickName() + "!" + clt->getLoginName() + "@" + server->host_name + " PRIVMSG " + target + " " + msg_toSend + " \r\n";
	        std::cout << "-*- " << msg;
	        send(u_it->second->getSocket(), msg.c_str(), msg.size(), 0);
            break;
        }
        u_it++;
    }
    return (EXIT_SUCCESS);
}

int     ft_privmsg( t_server *server, Client *clt, std::vector<std::string> &items )
{
    size_t size = items.size();
    if (size < 2)
        return (
			clt->reply(server->host_name, ERR_NORECIPIENT, ":No recipient given (PRIVMSG)"),
			EXIT_FAILURE
		);
    else if (size < 3)
        return (
			clt->reply(server->host_name, ERR_NOTEXTTOSEND, ":No text to send"),
			EXIT_FAILURE
		);
	std::string target;
	std::stringstream ss_targets(items[1]);
    std::string msg = (size == 3) ? items[2] : "";
    

    while (std::getline(ss_targets, target, ','))
	{
        if (target[0] == '#')
            toChannel(server, clt, target, msg);
        else
            toUser(server, clt, target, msg);
		target.clear();
	}
    return (EXIT_SUCCESS);
}