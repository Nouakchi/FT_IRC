/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:14:29 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/26 00:05:06 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __IRC_HPP__
# define __IRC_HPP__

#include <iostream>
#include <ctime>
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
#include <vector>

#define PORT 6667

enum err_rpl
{
    RPL_WELCOME = 001,
    RPL_YOURHOST = 002,
    RPL_CREATED = 003,
    ERR_NONICKNAMEGIVEN = 431,
    ERR_ERRONEUSNICKNAME = 432,
    ERR_NICKNAMEINUSE = 433,
    ERR_NOTREGISTERED = 451,
    ERR_NEEDMOREPARAMS = 461,
    ERR_ALREADYREGISTRED = 462,
    ERR_PASSWDMISMATCH = 464,
};

typedef struct s_server
{
    int					socket;
    std::string         server_name;
    char                *server_date;
    std::string         serv_pass;
    int                 new_client;
    int                 kq;
	int					opt_val;
    int                 new_sock_struct_len;
    struct	kevent		event[512];
    struct  kevent      delete_event;
    struct	sockaddr_in	sock_struct;
    struct	sockaddr_in	new_sock_struct;
    std::vector<std::string> nicknames;
    std::map<int, Client*> clients;
    
	
}   t_server;

void    ft_check_event( t_server *server, int event_fd );
int     ft_error( std::string err_msg );
int     ft_create_socket( t_server *server );
int     ft_bind_to_listen( t_server *server );
int     ft_setup_kernel_queue( t_server *server);
void    ft_setup_new_connection( t_server *server , int event_fd );
int     ft_send(int socket, std::string serv_name, std::string code, std::string nickname, std::string message);

# endif