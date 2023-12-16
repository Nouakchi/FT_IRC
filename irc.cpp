// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   irc.cpp                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: onouakch <onouakch@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/12/11 00:45:36 by onouakch          #+#    #+#             */
// /*   Updated: 2023/12/16 09:55:27 by onouakch         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


// #include <iostream>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <fcntl.h>


// // int check_digit(int port)
// // {
  
// // }
// void   ft_error(std::string str)
// {
//     std::cerr << str << std::endl;
//     exit(1);
// }
// void check_port(int port)
// {
//     if(port <= 1023 || port > 65535)
//         ft_error("Please enter A valid Port");
// }
// int main(int ac , char **av)
// {

//     int port;
//     if(ac != 3)
//         ft_error("Usage: ./ircserv <port> <password>");
//     else
//     {
//        if (av[1] && av[2])
//        {
//             port = atoi(av[1]);
//             check_port(port);
//        }
//        else
//             ft_error("please Provide Host and Port ");
//     }
  
//     std::cout << "hello" << std::endl;
//     return (0);
// }