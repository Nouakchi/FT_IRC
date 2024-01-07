/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 09:47:19 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/07 17:12:56 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

int		ft_partChannel(t_server *server, Client *clt, std::string target, std::string quit_msg)
{
	std::map<std::string, Channel*>::iterator it = server->channels.find(target);
	if (it == server->channels.end())
		return (
			clt->reply(server->host_name, ERR_NOSUCHCHANNEL, target + " :No such channel"),
			EXIT_FAILURE
		);
	std::map<std::string, Client *>::iterator is_opt = it->second->users.find("@" + clt->getNickName());
	if (it->second->users.find(clt->getNickName()) == it->second->users.end() 
		&& is_opt == it->second->users.end())
		return (
			clt->reply(server->host_name, ERR_NOTONCHANNEL, target + " :You're not on that channel"),
			EXIT_FAILURE
		);
	// normal process for a user to part from a channel
	std::map<std::string, Client*>::iterator c_it = it->second->users.begin();
	while (c_it != it->second->users.end())
	{
		std::string msg = ":" + clt->getNickName() + "!" + clt->getLoginName() + "@" + server->host_name + " PART " + target + " " + quit_msg + " \r\n";
		std::cout << "-*- " << msg;
		send(c_it->second->getSocket(), msg.c_str(), msg.size(), 0);
		c_it++;
	}
	it->second->users.erase((is_opt == it->second->users.end()) ? clt->getNickName() : "@" + clt->getNickName());
	if (!it->second->users.size())
		server->channels.erase(it->first);
	return (EXIT_SUCCESS);
}

int		ft_partCmd(t_server *server, Client *clt, std::vector<std::string> &items)
{
	size_t size = items.size();
	std::string target;
	std::stringstream ss_targets(items[1]);
	std::string quit_msg = (size == 3) ? items[2] : "";

	if (size < 2 || size > 3)
		return (
			clt->reply(server->host_name, ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters"),
			EXIT_FAILURE
		);
	while (std::getline(ss_targets, target, ','))
	{
		std::cout << "[" << quit_msg << "]\n";
		ft_partChannel(server, clt, target, quit_msg);
		target.clear();
	}
	return (EXIT_SUCCESS);
}