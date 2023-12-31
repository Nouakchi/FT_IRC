/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:00:24 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/30 16:00:40 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

void    ft_parseCommand( t_server *server, Client *clt, std::string buff )
{
    std::string                 token;
    std::vector<std::string>    items;
    std::stringstream           ss(buff);
    buff.pop_back();
    if (buff.find("\r") != std::string::npos)
        buff.pop_back();
    
    std::cout << "	::::	" << buff << "	:::::\n";
    while (ss >> token)
        items.push_back(token);
    ft_joinCmd(server, clt, items);
}