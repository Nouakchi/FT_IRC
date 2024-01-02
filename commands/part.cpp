/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 09:47:19 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/02 10:38:04 by onouakch         ###   ########.fr       */
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
	if (it->second->u_names.find(clt->getNickName()) == std::string::npos)
		return (
			clt->reply(server->host_name, ERR_NOTONCHANNEL, target + " :You're not on that channel"),
			EXIT_FAILURE
		);
	if (it->second->opt->getNickName() == clt->getNickName())
	{
		// if this client is the last one delete channel else try to give opt to another one
	}
	else
	{
		// normal process fro a user to part from a channel
	}
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
		ft_partChannel(server, clt, target, quit_msg);
		target.clear();
	}
	return (EXIT_SUCCESS);
}