/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:02:26 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/28 00:49:19 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/irc.h"

int main()
{
    int             i , num_events;
    t_server        server;
    struct  kevent  new_event[512];
    time_t          tt;
    struct tm       *ti;

    time(&tt);
    ti = localtime(&tt);
    
    server.server_name = "1337_server";
    server.serv_pass = "pass_test";
    server.host_name = 
    server.server_date = asctime(ti);
    
    if (EXIT_FAILURE == ft_create_socket(&server))
        return (EXIT_FAILURE);

    if (EXIT_FAILURE == ft_bind_to_listen(&server))
        return (EXIT_FAILURE);
        
    if (EXIT_FAILURE == ft_setup_kernel_queue(&server))
        return (EXIT_FAILURE);
        
    // // Get the local address and port the socket is bound to
    // struct sockaddr_in local_addr;
    // socklen_t addr_len = sizeof(local_addr);

    // if (getsockname(server.socket, (struct sockaddr *)&local_addr, &addr_len) == -1) {
    //     perror("getsockname failed");
    //     close(server.socket);
    //     return 1;
    // }

    // // Convert the IP address to a string and print it along with the port
    // char ipstr[INET_ADDRSTRLEN];
    // inet_ntop(AF_INET, &(local_addr.sin_addr), ipstr, INET_ADDRSTRLEN);
    // printf("Local address: %s\n", ipstr);
    // printf("Local port: %d\n", ntohs(local_addr.sin_port));
    
    // getchar();
    
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
                std::map<int, Client*>::iterator it = server.clients.find(event_fd);
                std::vector<std::string>::const_iterator s_it = std::find(server.nicknames.begin(), server.nicknames.end(), it->second->getNickName());
                if (s_it != server.nicknames.end())
                    server.nicknames.erase(s_it);
                ft_disconnect( &server, event_fd );
                // server.clients.erase(event_fd);
                // EV_SET(&server.delete_event, event_fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
                // kevent(server.kq, &server.delete_event, 1, NULL, 0, NULL);
                // close(event_fd);
                // std::cout << "client disconnected !!" << std::endl;
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