/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:14:18 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/17 11:03:13 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"



int main()
{
    struct  sockaddr_in sock_struct, nuser_sock_struct;
    // bzero(&sock_struct, sizeof(sock_struct));
    // bzero(&nuser_sock_struct, sizeof(nuser_sock_struct));
    int server_socket, nuser_socket, opt_val = 1, nuser_sock_struct_length = sizeof(nuser_sock_struct);
    

    //craeting the server socket using TCP/IP
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
        return (ft_error("Failed to open socket !!"));
    //seting the port ot be reused by the kernel
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT, &opt_val, sizeof(opt_val)))
        return (ft_error("Failed to setup socket options !!"));
    
    //initialize the socket struct
    sock_struct.sin_family = AF_INET;
    sock_struct.sin_addr.s_addr = INADDR_ANY;
    sock_struct.sin_port = htons( PORT );

    //binding the socket to an ip and port
    if (bind(server_socket, (struct sockaddr *) &sock_struct, sizeof(sock_struct)))
        return (ft_error("Failed to bind socket !!"));
        
    //listen for connection
    if (listen(server_socket, 4))
        return (ft_error("Failed to listen !!"));
        
    //check for new events
    
    struct kevent event[5], new_event[5];
        // init event before using it in kqueue
    EV_SET(event, server_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
        //creating a kqueue
    int i, kq = kqueue();
        // register event to be monitored (read)
    if (kevent(kq, event, 1, 0, 0, 0))
        return (ft_error("Failed to change event !!"));

    while (true)
    {
        int num_events = kevent(kq, 0, 0, new_event, 1, 0);
        std::cout << num_events << std::endl;
        if (num_events == -1)
            return (ft_error("Faile to check on events !!"));
        if (num_events > 0)
        {
            i = -1;
            while (++i < num_events)
            {
                int event_fd = event[i].ident;
                std::cout << event[i].flags <<  " , " << EV_EOF << " :: " << (event[i].flags & EV_EOF) << std::endl;
                // getchar();
                if (event[i].flags & EV_EOF)
                {
                    std::cout << "client disconnected !!" << std::endl;
                    close(event_fd);
                }
                else if (event_fd == server_socket)
                {
                    std::cout << "client connected !!" << std::endl;
                    nuser_socket = accept(event_fd, (struct sockaddr *)&nuser_sock_struct , (socklen_t *)&nuser_sock_struct_length);
                    if (nuser_socket == -1)
                        std::cerr << "Failed to accept socket" << std::endl;
                    else
                    {
                        EV_SET(event, nuser_socket, EVFILT_READ, EV_ADD, 0, 0, 0);
                        if (kevent(kq, event, 1, 0, 0, 0))
                            std::cerr << "Kevent falied !!"<< std::endl;
                    }
                }
                else if (event[i].filter & EVFILT_READ)
                {
                    char buff[1024] = {0};
                    size_t bytes_read = recv(event_fd, &buff, sizeof(buff), 0);
                    if (bytes_read)
                        std::cout << bytes_read << " : " << buff << std::endl;
                }
            }
        }
    }
        
    
    return   (0);
}

