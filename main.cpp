/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:02:26 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/22 03:51:38 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/irc.h"

int main()
{
    int             i , num_events;
    t_server        server;
    struct  kevent  new_event[512];
    
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
            return (ft_error("Faile to check on events !!"));

        i = -1;
        while (++i < num_events)
        {
            int event_fd = new_event[i].ident;
            //check for disconnected client
            if (new_event[i].flags & EV_EOF)
            {
                std::cout << "client disconnected !!" << std::endl;
                close(event_fd);
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