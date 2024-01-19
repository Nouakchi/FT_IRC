/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:08:37 by heddahbi          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:56 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"
#include "../models/Client.hpp"
#include "../models/Channel.hpp"

// bad channel mask is an error that is returned when the channel name doesn't start with # or &
bool is_valid_channel_name(std::string name)
{
    if (name[0] != '#' && name[0] != '&')
        return false;
    return true;
}

// this function is used to return the reason of the kick bcs we split the message by spaces
std::string _return_reason(std::vector<std::string> &items)
{
    std::string reason;
    size_t size = items.size();
    if (size > 3)
    {
        for (size_t i = 3; i < size; ++i)
        {
            reason += items[i];
            if (i < size - 1)
                reason += " ";
        }
    }
    return reason;
}

int ft_kickCmd(t_server *server, Client *clt, std::vector<std::string> &items)
{
    size_t size = items.size();
    std::string ch;
    std::stringstream ss_targets(items[1]);
    std::stringstream ss_users(items[2]);
    std::string reason;

    // if the size of the vector is less than 3, then we don't have enough parameters to execute the command
    if (size < 3)
        return clt->reply(server->host_name, ERR_NEEDMOREPARAMS, "KICK :Not enough parameters"), EXIT_FAILURE;
    // if the size of the vector is greater than 3, then we have a reason for the kick because limechat considers the last parameter as a reason
    if (size > 3)
        reason = _return_reason(items);
    while (std::getline(ss_targets, ch, ','))
    {
        std::cout << "ch: " << ch << std::endl;
        // if the channel name is not valid, then we return an error
        if (!is_valid_channel_name(ch))
            return clt->reply(server->host_name, ERR_BADCHANMASK, ch + " :Bad Channel Mask"), EXIT_FAILURE;
        std::map<std::string, Channel *>::iterator it = server->channels.find(ch);
        // if the channel doesn't exist, then we return an error
        if (it == server->channels.end())
            return clt->reply(server->host_name, ERR_NOSUCHCHANNEL, ch + " :No such channel"), EXIT_FAILURE;
        std::map<std::string, Client *>::iterator is_opt = it->second->users.find("@" + clt->getNickName());
        if (it->second->users.find(clt->getNickName()) != it->second->users.end() && is_opt == it->second->users.end())
            return clt->reply(server->host_name, ERR_CHANOPRIVSNEEDED, clt->getNickName() + " " + ch + " :You are not a channel operator"), EXIT_FAILURE;
        else if (it->second->users.find(clt->getNickName()) == it->second->users.end() && is_opt == it->second->users.end())
            return clt->reply(server->host_name, ERR_NOTONCHANNEL, ch + " :You're not on that channel"), EXIT_FAILURE;
        std::stringstream ss_users_copy(items[2]);  // we need to copy the stringstream because it's already used in the while loop lfu9
        while (std::getline(ss_users_copy, ch, ','))
        {
            if (reason.empty())
                reason = "probably because you're a noob";
            // if the user is not in the channel, then we return an error
            if (it->second->users.find(ch) == it->second->users.end())
                return clt->reply(server->host_name, ERR_USERNOTINCHANNEL, ch + " " + it->second->name + " :They aren't on that channel"), EXIT_FAILURE;

            // Send KICK message to the user who is being kicked
            std::string kickMessage = ":" + clt->getNickName() + "!" + clt->getLoginName() + "@" + server->host_name + " KICK " + it->second->name + " " + ch + " :" + reason + "\r\n";
            send(it->second->users[ch]->getSocket(), kickMessage.c_str(), kickMessage.size(), 0);
            it->second->users.erase(ch);
        }
        // Check if the channel is empty and erase it from the map for optimization purposes
            std::string channelMessage = ":" + clt->getNickName() + "!" + clt->getLoginName() + "@" + server->host_name + " KICK " + it->second->name + " " + ch + " :" + reason + "\r\n";
            for (std::map<std::string, Client *>::iterator channelUser = it->second->users.begin(); channelUser != it->second->users.end(); ++channelUser)
            {
                if(channelUser->first != clt->getNickName())
                send(channelUser->second->getSocket(), channelMessage.c_str(), channelMessage.size(), 0);
            }
        if (it->second->users.size() == 0)
            server->channels.erase(it->second->name);
    }
    return EXIT_SUCCESS;
}

