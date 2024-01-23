/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:02:26 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/23 11:27:45 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/irc.h"
#include <sstream>
#include <vector>
int ft_parse_port( char *port )
{
    int i = -1;
    while (port[++i])
        if (!isdigit(port[i]))
            return (ft_error("Port must be a number !!"));
    if(atoi(port) < 1024 || atoi(port) > 65535)
        return (ft_error("Port must be between 0 and 65535 !!" ));

    return (EXIT_SUCCESS);
}
int parse_pwd( char *pwd )
{
    int i = -1;
    if(strlen(pwd) < 1)
        return (ft_error("Password must be at least 1 char long !!"));
    while (pwd[++i])
        if (isspace(pwd[i]))
            return (ft_error("Password must not contain spaces !!"));
    return (EXIT_SUCCESS);
}

void clear_events(struct kevent *new_event, int num_events)
{
    int i = -1;
    while (++i < num_events)
    {
        new_event[i].ident = 0;
        new_event[i].filter = 0;
        new_event[i].flags = 0;
        new_event[i].fflags = 0;
        new_event[i].data = 0;
        new_event[i].udata = NULL;
    }
}
int main(int ac , char **av)
{
    int             i , num_events;
    char            tmp_host[32];
    t_server        server;
    struct  kevent  new_event[512];
    time_t          tt;
    struct tm       *ti;

    time(&tt);
    ti = localtime(&tt);
    
    if (ac != 3)
        return (ft_error("Usage: ./ircserv <port> <password>"));
    if (EXIT_FAILURE == parse_pwd(av[2]))
        return (EXIT_FAILURE);
    if (EXIT_FAILURE == ft_parse_port(av[1]))
        return (EXIT_FAILURE);
    server.serv_pass = av[2];
    server.port = atoi(av[1]);
    server.server_date = asctime(ti);

    gethostname(tmp_host, sizeof(tmp_host));
    server.server_name = std::string(tmp_host);
    server.host_name = ":" + server.server_name;

    if (EXIT_FAILURE == ft_create_socket(&server))
        return (EXIT_FAILURE);

    if (EXIT_FAILURE == ft_bind_to_listen(&server))
        return (EXIT_FAILURE);

    if (EXIT_FAILURE == ft_setup_kernel_queue(&server))
        return (EXIT_FAILURE);
    try
    {
        while (true)
        {
            //check for a new connection or a received message
            num_events = kevent(server.kq, NULL, 0, new_event, 1, NULL);
            if (num_events == -1)
                return (ft_error("Faile to check on events !!"));
                
            i = -1;
            while (++i < num_events)
            {
                int event_fd = new_event[i].ident;

                //check for new client
                if (new_event[i].flags & EV_EOF )
                {
                    std::map<int, Client*>::iterator it = server.clients.find(event_fd);
                    std::set<std::string>::iterator s_it = std::find(server.nicknames.begin(), server.nicknames.end(), it->second->getNickName());
                    if (s_it != server.nicknames.end())
                        server.nicknames.erase(s_it);
                    ft_disconnect( &server, event_fd );
                }
                else if (event_fd == server.socket)
                    ft_setup_new_connection( &server, event_fd );
                //check for an event from an existant client
                else if (new_event[i].filter & EVFILT_READ)
                    ft_check_event(&server, event_fd);
            }
            clear_events(new_event, num_events);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    
    
    return   (0);
}