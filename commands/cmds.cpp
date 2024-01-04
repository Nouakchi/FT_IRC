/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:00:24 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/04 10:24:32 by aaoutem-         ###   ########.fr       */
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
    {
        if (token[0] == ':' && token.length() > 1)
        {
            items.push_back(buff.substr(1, buff.length()));
            break;
        }
        items.push_back(token);
    }
    if (items.size())
    {
        if (items[0] == "JOIN")
            ft_joinCmd(server, clt, items);
        else if (items[0] == "PART")
            ft_partCmd(server, clt, items);
        else if(items[0] == "MODE")
            ft_modeCmd(server, clt, buff);
    }
}
