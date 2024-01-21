/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 03:47:54 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/21 14:24:45 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"
#include <sstream>

void  ft_disconnect( t_server *server, int event_fd )
{
    // remove the socket from the EVLIST
    EV_SET(&server->delete_event, event_fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
    kevent(server->kq, &server->delete_event, 1, NULL, 0, NULL);
    // remove the user from the SET && close it's FD
    Client *clt = server->clients.find(event_fd)->second;
    clt->clearHistory();
    server->nicknames.erase(clt->getNickName());
    server->clients.erase(event_fd);
    close(event_fd);
    delete clt;
    std::cout << "client disconnected !!" << std::endl;
}

#include <iostream>
#include <string>


void  ft_check_event( t_server *server, int event_fd )
{
    char buff[1024] = {0};
    ssize_t bytes_read = recv(event_fd, &buff, sizeof(buff), 0);
    if (bytes_read <= 0)
        return ;

    // std::string test = "PASS pass_test\nNICK mok\nUSER a b c d\n";
    
    
    std::map<int, Client*>::iterator it = server->clients.find(event_fd);
    if (it != server->clients.end())
    {
        it->second->setCmd(it->second->getCmd() + buff);
        std::string cmd = it->second->getCmd();
        if (cmd.find("\n") != std::string::npos)
        {
            // if the user is registered otherwise it will proced the auth process
            size_t pos = cmd.find("\n");
            while (pos != std::string::npos)
            {
                std::string ex_cmd = cmd.substr(0, pos + 1);
                // std::cout << "*** " << ex_cmd.length() << "[" << ex_cmd.substr(0,ex_cmd.length() - 2) << "]" << std::endl;
                if (it->second->getAuthFlag())
                    ft_parseCommand(server, it->second, ex_cmd);
                else if (ft_authProcess(server, it->second, ex_cmd))
                {
                    ft_disconnect(server, event_fd);
                    return ;
                }
                cmd = cmd.substr(pos + 1, cmd.length());
                pos = cmd.find("\n");
            }
            it->second->setCmd("");
        }
        else
            std::cout << it->second->getCmd() << std::endl;
    }
}

