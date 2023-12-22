/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:04:10 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/22 22:01:53 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <map>
#include <sys/socket.h>
#include <sys/event.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#define BACKLOG 10
#define MAXEVENTS 64
#define MAXFD 256

// create a paire of a <socketFD, clientClass>: using MAP container ofc 

enum role
{
    OPERATOR,
    
};

#endif