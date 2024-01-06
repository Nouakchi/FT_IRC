/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 11:14:29 by onouakch          #+#    #+#             */
/*   Updated: 2024/01/06 11:58:18 by aaoutem-         ###   ########.fr       */
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
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <map>
#include "../models/Client.hpp"
#include "../models/Channel.hpp"
#include <iterator>
#include <vector>
#include <sstream>

#define PORT 6667

enum err_rpl
{
    RPL_WELCOME = 001,
    RPL_YOURHOST = 002,
    RPL_CREATED = 003,
    
    RPL_NOTOPIC = 313,
    RPL_CHANNELMODEIS = 324,
    RPL_TOPIC = 332,
    RPL_NAMREPLY = 353,
    RPL_ENDOFNAMES = 366,
    
    ERR_NOSUCHCHANNEL = 403,
    ERR_UNKNOWNMODE = 472,
    ERR_CHANOPRIVSNEEDED = 482,

    ERR_NONICKNAMEGIVEN = 431,
    ERR_ERRONEUSNICKNAME = 432,
    ERR_NICKNAMEINUSE = 433,
    
    ERR_NOTONCHANNEL = 442,
    ERR_USERNOTINCHANNEL = 441,
    ERR_NOTREGISTERED = 451,
    ERR_NEEDMOREPARAMS = 461,
    ERR_ALREADYREGISTRED = 462,
    ERR_PASSWDMISMATCH = 464,
};

typedef struct s_server
{
    int					            socket;
    int                             new_client;
    int                             kq;
	int					            opt_val;
    int                             new_sock_struct_len;
    char                            *server_date;
    std::string                     host_name;
    std::string                     server_name;
    std::string                     serv_pass;
    struct	kevent		            event[512];
    struct  kevent                  delete_event;
    struct	sockaddr_in	            sock_struct;
    struct	sockaddr_in	            new_sock_struct;
    std::map<int, Client*>          clients;
    std::map<std::string, Channel*> channels;
    std::vector<std::string>        nicknames;

	
}   t_server;

int     ft_error( std::string err_msg );
int     ft_create_socket( t_server *server );
int     ft_bind_to_listen( t_server *server );
int     ft_setup_kernel_queue( t_server *server);
void    ft_disconnect( t_server *server, int event_fd );
void    ft_check_event( t_server *server, int event_fd );
void    ft_setup_new_connection( t_server *server , int event_fd );
int     ft_checkCmd( Client *clt, t_server *server, std::string buff);
int     ft_authProcess( t_server *server, Client *clt, std::string buff);
int     ft_send(int socket, std::string serv_name, std::string code, std::string nickname, std::string message);

/*####################*/

void    ft_parseCommand( t_server *server, Client *clt, std::string buff );
int     ft_joinCmd( t_server *server, Client *clt, std::vector<std::string> &items );
int		ft_partCmd(t_server *server, Client *clt, std::vector<std::string> &items);

/*_________ kaigh_________________*/

int     ft_modeCmd( t_server *server, Client *clnt, std::string buff);
void    splitString(const std::string& cmd, std::vector<std::string>& substrs);

void	SetMode( t_server *server, Client *clnt, std::vector<std::string>& cmd );
void	RmMode( t_server *server, Client *clnt, std::vector<std::string>& cmd );


void	error_replay( t_server* server ,int errNbr, Client clnt, std::string err);

/*____________________________________*/
# endif