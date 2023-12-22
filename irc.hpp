/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:04:10 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/22 00:50:01 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <fstream>
#include <ios>
#include <sys/socket.h>
#include <sys/event.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#define BACKLOG 10
#define MAXEVENTS 64
#define MAXFD 256
enum role
{
    OPERATOR,
    
};

#endif