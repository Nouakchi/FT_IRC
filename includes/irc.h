/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:14:29 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/22 03:55:42 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __IRC_HPP__
# define __IRC_HPP__

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <map>
#include "../models/Client.hpp"
#include <iterator>

#define PORT 6667

typedef struct s_server
{
    int					socket;
    int                 new_client;
    int                 kq;
	int					opt_val;
    int                 new_sock_struct_len;
	char				buff[1024];
	size_t				bytes_read;
    struct	kevent		event[5];
    struct	sockaddr_in	sock_struct;
    struct	sockaddr_in	new_sock_struct;
    std::map<int, Client*> clients;
	
}   t_server;

void    ft_check_event( t_server *server, int event_fd );
int     ft_error( std::string err_msg );
int     ft_create_socket( t_server *server );
int     ft_bind_to_listen( t_server *server );
int     ft_setup_kernel_queue( t_server *server);
void    ft_setup_new_connection( t_server *server , int event_fd );


# endif