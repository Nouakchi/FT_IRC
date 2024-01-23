/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_authInfo.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 03:51:58 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/23 08:44:22 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

int     ft_checkPass( Client *clt, std::string buff, std::string pass )
{
    if (buff.length() == 0)
        return (clt->reply(":localhost", ERR_NEEDMOREPARAMS, "PASS :Not enough parameters"), EXIT_FAILURE);
    
    // if the nickname is not given, so the user still in the PASS step,
    // otherwise the pass is ignored and an ERR_MSG is sent to the client
    if (clt->getNickName() == "*")
    {
        if (buff == pass)
            clt->setPassChecked(true);
        else
            clt->setPassChecked(false);
    }
    else
        clt->reply(":localhost", ERR_ALREADYREGISTRED, ":You may not reregister");
    return (EXIT_SUCCESS);
}

int     ft_checkNick( t_server *server, Client *clt, std::string buff )
{
    (void) server;
    if (buff.length() == 0)
        return (clt->reply(server->host_name, ERR_NONICKNAMEGIVEN, ":No nickname given"), EXIT_FAILURE);
        
    std::string allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-{}[]\\`^";
    if (buff.find_first_not_of(allowed_chars) != std::string::npos)
        return (clt->reply(server->host_name, ERR_ERRONEUSNICKNAME, buff + " :Erroneus nickname"), EXIT_FAILURE);
        
    clt->setNickName(buff);
    return (EXIT_SUCCESS);
}

int     ft_checkUser( t_server *server, Client *clt, std::string buff )
{
    int nbr_args = 0;
    
    if (clt->getNickName() != "*")
    {
        std::stringstream ss(buff);
        std::string arg;
        while (ss >> arg)
        {
            nbr_args++;
            if (nbr_args == 1)
                clt->setLoginName(arg);
            else if (nbr_args == 4)
            {
                if (arg.length() >= 1)
                {
                    if (arg[0] == ':')
                    {
                        size_t pos = buff.find(":");
                        clt->setRealName(buff.substr(pos + 1, buff.length()));
                        break;
                    }
                    else
                        clt->setRealName(arg);
                }
                else
                {
                    nbr_args--;
                    break;
                }
            }
        }
        if (nbr_args != 4)
            return (
                        clt->reply(server->host_name, ERR_NEEDMOREPARAMS, "USER :Not enough parameters"),
                        EXIT_FAILURE
                    );
    }
    return (EXIT_SUCCESS);
}

int     ft_checkCmd( Client *clt, t_server *server, std::string buff)
{
    std::string tmp = buff.substr(0,5);
    if (tmp == "PASS ")
        return (ft_checkPass(clt, buff.substr(5, buff.length()), server->serv_pass));
    else if (tmp == "NICK ")
        return (ft_checkNick(server, clt, buff.substr(5, buff.length())));
    else if (tmp == "USER ")
        return (ft_checkUser(server, clt, buff.substr(5, buff.length())));
    else
        return (clt->reply(server->host_name, ERR_NOTREGISTERED, ":You have not registered"));
}