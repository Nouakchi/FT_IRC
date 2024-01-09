/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:07:55 by heddahbi          #+#    #+#             */
/*   Updated: 2024/01/09 17:46:33 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"
#include "../models/Client.hpp"
#include "../models/Channel.hpp"



int ft_topicCmd(t_server *server, Client *clt, std::vector<std::string> &items)
{
  size_t size = items.size();

  if(size < 2)
    return clt->reply(server->host_name, ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters"), EXIT_FAILURE; // not enough parameters
    if(size > 2)
    
    if (server->channels.find(items[1]) == server->channels.end())
        return clt->reply(server->host_name, ERR_NOSUCHCHANNEL, items[1] + " :No such channel"), EXIT_FAILURE; // no such channel
    if (server->channels[items[1]]->users.find("@" + clt->getNickName()) == server->channels[items[1]]->users.end() && server->channels[items[1]]->users.find(clt->getNickName()) == server->channels[items[1]]->users.end())
        return clt->reply(server->host_name, ERR_NOTONCHANNEL, items[1] + " :You're not on that channel"), EXIT_FAILURE; // you're not on that channel
    if (size == 2)
    {
        std::string msg = ":" + clt->getNickName() + "!" + clt->getLoginName() + "@" + server->host_name + " TOPIC " + items[1] + " :" + server->channels[items[1]]->topic + " \r\n";
        send(clt->getSocket(), msg.c_str(), msg.size(), 0);
    }
    else
    {
        if (server->channels[items[1]]->users.find("@" + clt->getNickName()) == server->channels[items[1]]->users.end())
            return clt->reply(server->host_name, ERR_CHANOPRIVSNEEDED, items[1] + " :You're not channel operator"), EXIT_FAILURE; // you're not channel operator
        server->channels[items[1]]->topic = items[2];
        std::map<std::string, Client *>::iterator u_it = server->channels[items[1]]->users.begin();
        while (u_it != server->channels[items[1]]->users.end())
        {
            std::string msg = ":" + clt->getNickName() + "!" + clt->getLoginName() + "@" + server->host_name + " TOPIC " + items[1] + " :" + server->channels[items[1]]->topic + " \r\n";
            std::cout << "-*- " << msg;
            send(u_it->second->getSocket(), msg.c_str(), msg.size(), 0);
            u_it++;
        }
    }
    return (EXIT_SUCCESS);
}