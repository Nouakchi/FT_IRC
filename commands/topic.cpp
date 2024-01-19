/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:07:55 by heddahbi          #+#    #+#             */
/*   Updated: 2024/01/19 00:13:50 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"
#include "../models/Client.hpp"
#include "../models/Channel.hpp"

std::string _return_topic(std::vector<std::string> &items)
{
    // You need to implement this function to extract the topic
    // based on your specific logic. For now, let's assume it
    // concatenates all parameters starting from the third element.
    std::string topic;
    for (size_t i = 2; i < items.size(); ++i)
    {
        topic += items[i];
        if (i < items.size() - 1)
            topic += " ";
    }
    return topic;
}

int ft_topicCmd(t_server *server, Client *clt, std::vector<std::string> &items)
{
    size_t size = items.size();
    std::string ch;
    std::string topic;

    // if the size of the vector is less than 2, then we don't have enough parameters to execute the command
    if (size < 2)
        return clt->reply(server->host_name, ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters"), EXIT_FAILURE;

    std::stringstream ss(items[1]);
    ss >> ch; // Extract the channel name

    // if the size of the vector is greater than 2, then we have a topic for the channel because limechat considers the last parameter as a topic
    if (size > 2)
    {
        // Extracting the topic using the provided function
        topic = _return_topic(items);
    }

    // if the channel name is not valid, then we return an error
    if (!is_valid_channel_name(ch))
        return clt->reply(server->host_name, ERR_BADCHANMASK, ch + " :Bad Channel Mask"), EXIT_FAILURE;

    std::map<std::string, Channel *>::iterator it = server->channels.find(ch);

    // if the channel doesn't exist, then we return an error
    if (it == server->channels.end())
        return clt->reply(server->host_name, ERR_NOSUCHCHANNEL, ch + " :No such channel"), EXIT_FAILURE;

    // if the user is not in the channel or not an operator, then we return an error
    if (it->second->users.find(clt->getNickName()) == it->second->users.end() && it->second->users.find("@" + clt->getNickName()) == it->second->users.end())
        return clt->reply(server->host_name, ERR_NOTONCHANNEL, ch + " :You're not on that channel"), EXIT_FAILURE;
    if (size == 2)
    {
        if (it->second->topic.empty())
            return clt->reply(server->host_name, RPL_NOTOPIC, ch + " :No topic is set"), EXIT_SUCCESS;
        return clt->reply(server->host_name, RPL_TOPIC, ch + " :" + it->second->topic), EXIT_SUCCESS;
    }
    if (it->second->users.find("@" + clt->getNickName()) == it->second->users.end() && size > 2 && it->second->t == true)
        return clt->reply(server->host_name, ERR_CHANOPRIVSNEEDED, ch + " :You're not a channel operator"), EXIT_FAILURE;
    it->second->topic = topic;
    std::stringstream ss_topic;
    ss_topic << ":" << clt->getNickName() << "!" << clt->getLoginName() << "@" << server->host_name << " TOPIC " << ch << " :" << topic << "\r\n";

    std::map<std::string, Client *>::iterator u_it = it->second->users.begin();
    while (u_it != it->second->users.end())
    {
        send(u_it->second->getSocket(), ss_topic.str().c_str(), ss_topic.str().size(), 0);
        u_it++;
    }
    return EXIT_SUCCESS;
}

