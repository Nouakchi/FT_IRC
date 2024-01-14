/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:31:38 by heddahbi          #+#    #+#             */
/*   Updated: 2024/01/14 12:16:54 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"
#include "../models/Client.hpp"
#include "../models/Channel.hpp"
#define ERR_NEEDMOREPARAMS 461
#define ERR_NOSUCHCHANNEL 403
#define ERR_NOTONCHANNEL 442
#define ERR_USERNOTINCHANNEL 441
#define ERR_CHANOPRIVSNEEDED 482
#define ERR_NOSUCHNICK 401
#define ERR_USERONCHANNEL 443
#define RPL_INVITING   341

int get_client_by_fd(t_server *server,std::string nickname)
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
    std::map<std::string, Channel*>::iterator it_channel = server->channels.find(target);
    if (it_channel == server->channels.end())
    {
        clt->reply(server->host_name, ERR_NOSUCHCHANNEL, user + " :No such channel");
        return EXIT_FAILURE;
    }
    std::map<int, Client*>::iterator it = server->clients.find(get_client_by_fd(server, user));
    if(it == server->clients.end())
    {
        clt->reply(server->host_name, ERR_NOSUCHNICK, user + " :No such nick/channel");
        return EXIT_FAILURE;
    }
    else if(it_channel->second->users.find(clt->getNickName()) == it_channel->second->users.end())
    {
        clt->reply(server->host_name, ERR_NOTONCHANNEL, target + " :You're not on that channel");
        return EXIT_FAILURE;
    }
    else if(it_channel->second->users.find(user) != it_channel->second->users.end())
    {
        clt->reply(server->host_name, ERR_USERONCHANNEL, user + " " + target + " :is already on channel");
        return EXIT_FAILURE;
    }
    else if(it_channel->second->users.find(user) == it_channel->second->users.end())
    {
        std::map<std::string, Client*>::iterator c_it = it_channel->second->users.begin();
            while (c_it != it_channel->second->users.end())
            {
                std::string msg = target + " " + user;
                if (c_it->second->getNickName() != user)
                    c_it->second->reply("",RPL_INVITING,msg);
                c_it++;
            }

        std::map<std::string , Client*>::iterator op_it = it_channel->second->users.find("@" + clt->getNickName());
        if (op_it == it_channel->second->users.end() && it_channel->second->o == true )
        {
            clt->reply(server->host_name, ERR_CHANOPRIVSNEEDED, clt->getNickName() + " " + target + " :You are not a channel operator");
            return EXIT_FAILURE;
        }
    
        std::string mess = "You have been invited to channel " + target + " by " + clt->getNickName().append("\r\n");
        it_channel->second->users.insert(std::pair<std::string, Client*>(user, it->second));
        send(it->second->getSocket(), mess.c_str(), mess.length(), 0);
    }
    return EXIT_SUCCESS;
}
