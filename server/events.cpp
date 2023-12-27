/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 03:47:54 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/27 03:48:56 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

void    ft_parseCommand( char *buff )
{
    // here where we will be parsing commands
    std::cout << " :: " << buff;
}

void  ft_disconnect( t_server *server, int event_fd )
{
    EV_SET(&server->delete_event, event_fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
    kevent(server->kq, &server->delete_event, 1, NULL, 0, NULL);
    server->clients.erase(event_fd);
    close(event_fd);
    std::cout << "client disconnected !!" << std::endl;
}

void  ft_check_event( t_server *server, int event_fd )
{
    char buff[1024] = {0};
    ssize_t bytes_read = recv(event_fd, &buff, sizeof(buff), 0);
    if (bytes_read <= 0)
        return ;
    std::map<int, Client*>::iterator it = server->clients.find(event_fd);
    if (it != server->clients.end())
    {
        if (it->second->getAuthFlag())
            ft_parseCommand(buff);
        else
            if (ft_authProcess(server, it->second, std::string(buff)))
                ft_disconnect(server, event_fd);
    }
}