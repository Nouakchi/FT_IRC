/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:14:18 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/23 04:37:55 by onouakch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

void    ft_parseCommand( char *buff )
{
    // here where we will be parsing commands
    std::cout << " :: " << buff;
}

int     ft_checkPass( Client *clt, std::string buff, std::string pass )
{
    if (buff.substr(5, buff.length()) == pass)
        return (clt->setPassChecked(true), 1);
    else
        return (clt->setPassChecked(false), 1);
    return (1);
}

int     ft_checkNick( Client *clt, std::string buff )
{
    clt->setNickName(buff.substr(5, buff.length()));
    return (1);
}

int     ft_checkUser( Client *clt, std::string buff )
{
    if (clt->getNickName() != "*")
        return (clt->setLoginName(buff.substr(5, buff.length())), 0);
    return (1);
}

void    ft_authProcess( Client *clt, std::string buff, std::string pass)
{
    buff.pop_back();
    // get data from the new client to authenticate
    if (buff.length() <= 5)
        return ;
    std::string tmp = buff.substr(0,5);
    if (tmp == "PASS ")
        ft_checkPass(clt, buff, pass);
    else if (tmp == "NICK ")
        ft_checkNick(clt, buff);
    else if (tmp == "USER ")
        ft_checkUser(clt, buff);
        
    // check if the client's data is ready to be authenticated
    clt->check_authentification();
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
            ft_authProcess(it->second, std::string(buff), server->serv_pass);
    }
}

void ft_setup_new_connection( t_server *server , int event_fd )
{
    
    std::cout << "client connected !!" << std::endl;
    server->new_sock_struct_len = sizeof(server->new_sock_struct);
    server->new_client = accept(event_fd, (struct sockaddr *)&server->new_sock_struct , (socklen_t *)&server->new_sock_struct_len);
    
    //addin the new event to the kqueue evList
    if (server->new_client == -1)
        std::cerr << "Failed to accept socket" << std::endl;
    else
    {
        EV_SET(server->event, server->new_client, EVFILT_READ, EV_ADD, 0, 0, 0);
        if (kevent(server->kq, server->event, 1, NULL, 0, NULL))
            std::cerr << "Kevent falied !!"<< std::endl;
        server->clients.insert(std::pair<int, Client*>(server->new_client, new Client(server->new_client)));
    }
}

int ft_setup_kernel_queue( t_server *server)
{
    //creating a kqueue
    server->kq = kqueue();
        
    // init event before using it in kqueue
    EV_SET(server->event, server->socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, 0);
    
    // register event to be monitored (read)
    if (kevent(server->kq, server->event, 1, NULL, 0, NULL))
        return (ft_error("Failed to change event !!"));

    return (EXIT_SUCCESS);
}

int ft_bind_to_listen( t_server *server )
{
    //initialize the socket struct
    bzero((char *)&server->sock_struct, sizeof(server->sock_struct));
    server->sock_struct.sin_family = AF_INET;
    server->sock_struct.sin_addr.s_addr = INADDR_ANY;
    server->sock_struct.sin_port = htons( PORT );
    
    //binding the socket to an ip and port
    if (bind(server->socket, (struct sockaddr *) &server->sock_struct, sizeof(server->sock_struct)))
        return (ft_error("Failed to bind socket !!"));
        
    //listen for connection
    if (listen(server->socket, 4))
        return (ft_error("Failed to listen !!"));
    std::cout << "server is listening on port " << PORT << std::endl;
    return (EXIT_SUCCESS);
}

int	ft_create_socket( s_server *server )
{
	server->opt_val = 1;
	//craeting the server socket using TCP/IP
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1)
        return (ft_error("Failed to open socket !!"));
    if (fcntl(server->socket, F_SETFL, O_NONBLOCK) == -1)
        return (ft_error("Failed"));
    //seting the port to be reused by the kernel
    if (setsockopt(server->socket, SOL_SOCKET, SO_REUSEPORT,&server->opt_val, sizeof(server->opt_val)))
        return (ft_error("Failed to setup socket options !!"));

    return (EXIT_SUCCESS);
}



