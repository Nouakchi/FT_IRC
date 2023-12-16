/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:14:18 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/16 12:06:30 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.h"



int main()
{
    int server_socket;
    struct  sockaddr_in sock_struct;
    

    //craeting the server socket using TCP/IP
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
        return (ft_error("Failed to open socket !!"));
    
    //initialize the socket struct
    sock_struct.sin_family = AF_INET;
    sock_struct.sin_addr.s_addr = INADDR_ANY;
    sock_struct.sin_port = htons( PORT );

    //binding the socket to an ip and port
    if (bind(server_socket, (struct sockaddr *) &sock_struct, sizeof(sock_struct)))
        return (ft_error("Failed to bind socket !!"));
        
    //listen for connection
    if (listen(server_socket, 10) == -1)
        return (ft_error("Failed to listen !!"));
        
    
    return   (0);
}

