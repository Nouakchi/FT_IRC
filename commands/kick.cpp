/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:08:37 by heddahbi          #+#    #+#             */
/*   Updated: 2024/01/07 17:08:38 by heddahbi         ###   ########.fr       */
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
    // if the size of the vector is greater than 3, then we have a reason for the kick bcs limechat consider the last parameter as a reason
    if (size > 3)
        reason = _return_reason(items);
    // if the channel name is not valid, then we return an error
    if (!is_valid_channel_name(items[1]))
        return clt->reply(server->host_name, ERR_BADCHANMASK, items[1] + " :Bad Channel Mask"), EXIT_FAILURE;
    while (std::getline(ss_targets, ch, ','))
    {

        std::map<std::string, Channel *>::iterator it = server->channels.find(ch);
        // if the channel doesn't exist, then we return an error
        if (it == server->channels.end())
            return clt->reply(server->host_name, ERR_NOSUCHCHANNEL, ch + " :No such channel"), EXIT_FAILURE;
        std::map<std::string, Client *>::iterator is_opt = it->second->users.find("@" + clt->getNickName());
        if (it->second->users.find(clt->getNickName()) != it->second->users.end() && is_opt == it->second->users.end())
            return clt->reply(server->host_name, ERR_CHANOPRIVSNEEDED, clt->getNickName() + " " + ch + " :You are not a channel operator"), EXIT_FAILURE;
        
        else if (it->second->users.find(clt->getNickName()) == it->second->users.end() && is_opt == it->second->users.end())
            return clt->reply(server->host_name, ERR_NOTONCHANNEL, ch + " :You're not on that channel"), EXIT_FAILURE;
        while (std::getline(ss_users, ch, ','))
        {
            std::map<std::string, Client *>::iterator it_user = it->second->users.find(ch);
            if (it_user == it->second->users.end() && is_opt != it->second->users.end())
                return clt->reply(server->host_name, ERR_USERNOTINCHANNEL, ch + " " + it->first + " :They aren't on that channel"), EXIT_FAILURE;
            std::map<std::string, Client *>::iterator c_it = it->second->users.begin();
            while (c_it != it->second->users.end())
            {
                if (reason.empty())
                    reason = "Probably because you're a noob";
                std::string message;
                message = ":KICK " + ch + " " + it_user->first + " " + ": " + clt->getNickName() + " " + reason + "\r\n";
                if (c_it->second->getNickName() != clt->getNickName())
                    c_it->second->reply(server->host_name, 00, message);
                c_it++;
            }
            // we erase the user from the channel if he's kicked
            it->second->users.erase(ch);
            // if the channel is empty, then we erase it from the map optimisation purposes
            if (!it->second->users.size())
                server->channels.erase(it->first);
        }
    }

    return EXIT_SUCCESS;
}

