/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 00:45:36 by onouakch          #+#    #+#             */
/*   Updated: 2023/12/15 17:40:06 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>


// int check_digit(int port)
// {
  
// }
void   ft_error(std::string str)
{
    std::cerr << str << std::endl;
    exit(1);
}
void check_port(int port)
{
    if(port <= 1023 || port > 65535)
        ft_error("Please enter A valid Port");
}
int main(int ac , char **av)
{
    int port;
    // int pwd;
    if(ac != 3)
        ft_error("Usage: ./ircserv <port> <password>");
    else
    {
       if (av[1] && av[2])
       {
            port = atoi(av[1]);
            check_port(port);
            
       }
       else
            ft_error("please Provide Host and Port ");
    }
    //AF_INET = IPv4 for TCP/IP
    //SOCK_STREAM = TCP
    //0 = IP
    int dd = socket(AF_INET, SOCK_STREAM, 0);
    if (dd == -1)
    {
        ft_error("Socket Failed");
        return (1);
    }
  
    std::cout << "hello" << std::endl;
    return (0);
}