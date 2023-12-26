/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:14:18 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/26 07:03:47 by onouakch         ###   ########.fr       */
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
    if (buff.length() == 0)
        return (clt->reply(":localhost", ERR_NEEDMOREPARAMS, "PASS :Not enough parameters"), EXIT_FAILURE);
    if (clt->getNickName() == "*")
    {
        if (buff == pass)
            clt->setPassChecked(true);
        else
            clt->setPassChecked(false);
    }
    else
        clt->reply(":localhost", ERR_ALREADYREGISTRED, ":You may not reregister");
    return (EXIT_SUCCESS);
}

int     ft_checkNick( t_server *server, Client *clt, std::string buff )
{
    (void) server;
    if (buff.length() == 0)
        return (clt->reply(":localhost", ERR_NONICKNAMEGIVEN, ":No nickname given"), EXIT_FAILURE);
        
    if (buff.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-{}[]\\`^") != std::string::npos)
        return (clt->reply(":localhost", ERR_ERRONEUSNICKNAME, buff + " :Erroneus nickname"), EXIT_FAILURE);
        
    clt->setNickName(buff);
    return (EXIT_SUCCESS);
}

int     ft_checkUser( Client *clt, std::string buff )
{
    if (clt->getNickName() != "*")
    {
        int nbr_args = 0;
        std::stringstream ss(buff);
        std::string arg;
        while (ss >> arg)
        {
            nbr_args++;
            if (nbr_args == 1)
                clt->setLoginName(arg);
            else if (nbr_args == 4)
            {
                if (arg[0] == ':' && arg.length() > 1)
                {
                    clt->setRealName(arg.substr(1, arg.length()));
                    break;
                }
                else
                    clt->setRealName(arg);
            }
            else if (nbr_args > 4)
                break;
        }
        if (nbr_args > 4)
            return (
                        clt->reply(":localhost", ERR_NEEDMOREPARAMS, "USER :Not enough parameters"),
                        EXIT_FAILURE
                    );
    }
    return (EXIT_FAILURE);
}

int    ft_authProcess( t_server *server, Client *clt, std::string buff)
{
    int status;

    buff.pop_back();
    if (buff.find("\r") != std::string::npos)
        buff.pop_back();
    // get data from the new client to authenticate
    if (buff.length() < 5)
        return (clt->reply(":localhost", ERR_NOTREGISTERED, ":You have not registered"), EXIT_SUCCESS);
    std::string tmp = buff.substr(0,5);
    if (tmp == "PASS ")
        status = ft_checkPass(clt, buff.substr(5, buff.length()), server->serv_pass);
    else if (tmp == "NICK ")
        status = ft_checkNick(server, clt, buff.substr(5, buff.length()));
    else if (tmp == "USER ")
        status = ft_checkUser(clt, buff.substr(5, buff.length()));
    else
        status = clt->reply(":localhost", ERR_NOTREGISTERED, ":You have not registered");
        
    if (status == EXIT_FAILURE)
        return (EXIT_SUCCESS);

    // check if the client's data is ready to be authenticated
    status = clt->check_authentification( );
    if (status > 0)
        return (EXIT_FAILURE);
    else if (!status)
    {
        std::vector<std::string>::iterator it = std::find(server->nicknames.begin(), server->nicknames.end(), clt->getNickName());
        if (it != server->nicknames.end())
            return (
                        clt->setNickName("*"),
                        clt->reply(":localhost", ERR_NICKNAMEINUSE, clt->getNickName() + " :Nickname is already in use"),
                        EXIT_SUCCESS
                    );
        server->nicknames.push_back(clt->getNickName());
        // sending mssg to the client to be informed 
        // that the connection has been accepted
        if (clt->reply(":localhost", RPL_WELCOME, ":Welcome to the IRC server!"))
            return (EXIT_FAILURE);
        if (clt->reply(":localhost", RPL_YOURHOST, ":Your host is " + server->server_name + ", running version 1.0"))
            return (EXIT_FAILURE);
        std::string datetime(server->server_date);
        if (clt->reply(":localhost", RPL_CREATED, ":This server was created " + datetime))
            return (EXIT_FAILURE);  
    }
    return (EXIT_SUCCESS);
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
        {
            ft_parseCommand(buff);
        }
        else
        {
            if (ft_authProcess(server, it->second, std::string(buff)))
            {
                EV_SET(&server->delete_event, event_fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
                kevent(server->kq, &server->delete_event, 1, NULL, 0, NULL);
                server->clients.erase(event_fd);
                close(event_fd);
                std::cout << "client disconnected !!" << std::endl;
            }
        }
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



