/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:31:38 by heddahbi          #+#    #+#             */
/*   Updated: 2024/01/24 15:51:28 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

int get_client_by_fd(t_server *server, std::string nickname)
{
    std::map<int, Client*>::iterator it = server->clients.begin();
    while (it != server->clients.end())
    {
        if (it->second->getNickName() == nickname)
            return it->second->getSocket();
        it++;
    }
    return -1;
}

int ft_inviteCmd(t_server *server, Client *clt, std::vector<std::string> &items)
{
    size_t size = items.size();
    if (size < 3)
    {
        clt->reply(server->host_name, ERR_NEEDMOREPARAMS, "INVITE :Not enough parameters");
        return EXIT_FAILURE;
    }

    std::string target = items[2];
    std::string user = items[1];

    // Check if the target channel exists
    std::map<std::string, Channel*>::iterator it_channel = server->channels.find(target);
    if (it_channel == server->channels.end())
    {
        clt->reply(server->host_name, ERR_NOSUCHCHANNEL, target + " :No such channel");
        return EXIT_FAILURE;
    }

    // Check if the user being invited exists
    std::map<int, Client*>::iterator it_user = server->clients.find(get_client_by_fd(server, user));
    if (it_user == server->clients.end())
    {
        clt->reply(server->host_name, ERR_NOSUCHNICK, user + " :No such nick/channel");
        return EXIT_FAILURE;
    }

    // Check if the invoker is on the channel and has sufficient privileges
    if (it_channel->second->users.find(clt->getNickName()) == it_channel->second->users.end() &&
        it_channel->second->users.find("@" + clt->getNickName()) == it_channel->second->users.end())
    {
        clt->reply(server->host_name, ERR_NOTONCHANNEL, target + " :You're not on that channel");
        return EXIT_FAILURE;
    }
    else if (it_channel->second->users.find("@" + clt->getNickName()) == it_channel->second->users.end() &&
             it_channel->second->o == false)
    {
        clt->reply(server->host_name, ERR_CHANOPRIVSNEEDED, clt->getNickName() + " " + target + " :You are not a channel operator");
        return EXIT_FAILURE;
    }

    // Check if the user is already on the channel
    if (it_channel->second->users.find(user) != it_channel->second->users.end())
    {
        clt->reply(server->host_name, ERR_USERONCHANNEL, user + " " + target + " :is already on channel");
        return EXIT_FAILURE;
    }

    // Send INVITE message to the user
    std::string inviteMessage = ":" + clt->getNickName() + " INVITE " + user + " " + target + "\r\n";
    send(it_user->second->getSocket(), inviteMessage.c_str(), inviteMessage.length(), 0);

    //insert the user in the invited_users list
    it_channel->second->invited_users.insert(user);
    it_channel->second->users.insert(std::pair<std::string, Client*>(user, it_user->second));
    
    // Send RPL_INVITING to the invoker
    std::string rplMessage = ":" + server->host_name + " 341 " + clt->getNickName() + " " + user + "\r\n";
    send(clt->getSocket(), rplMessage.c_str(), rplMessage.length(), 0);

    return EXIT_SUCCESS;
}







