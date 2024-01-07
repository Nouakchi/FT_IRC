/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:02:26 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/05 15:15:17 by onouakch         ###   ########.fr       */
=======
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:02:26 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/03 20:19:39 by heddahbi         ###   ########.fr       */
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)
/*                                                                            */
/* ************************************************************************** */

#include "includes/irc.h"

int main()
{
    int             i , num_events;
    char            tmp_host[32];
    t_server        server;
    struct  kevent  new_event[512];
    time_t          tt;
    struct tm       *ti;

    time(&tt);
    ti = localtime(&tt);
    
    server.serv_pass = "pass_test";
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
    
    while (true)
    {
        //check for a new connection or a received message
        num_events = kevent(server.kq, NULL, 0, new_event, 1, NULL);
        if (num_events == -1)
<<<<<<< HEAD
            return (ft_error("Faile to check on events !!"));
=======
            return (ft_error("Failed to check on events !!"));
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)

        i = -1;
        while (++i < num_events)
        {
            int event_fd = new_event[i].ident;
            //check for disconnected client
            if (new_event[i].flags & EV_EOF)
            {
                std::map<int, Client*>::iterator it = server.clients.find(event_fd);
<<<<<<< HEAD
                std::set<std::string>::iterator s_it = std::find(server.nicknames.begin(), server.nicknames.end(), it->second->getNickName());
=======
                std::vector<std::string>::const_iterator s_it = std::find(server.nicknames.begin(), server.nicknames.end(), it->second->getNickName());
>>>>>>> 20a4cf9 (finish all cmds based on the first version of <join>)
                if (s_it != server.nicknames.end())
                    server.nicknames.erase(s_it);
                ft_disconnect( &server, event_fd );
            }
            //check for new client
            else if (event_fd == server.socket)
                ft_setup_new_connection( &server, event_fd );
            //check for an event from an existant client
            else if (new_event[i].filter & EVFILT_READ)
                ft_check_event(&server, event_fd);
        }
    }
    return   (0);
}