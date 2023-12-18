/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:04:10 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/18 14:38:34 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <sys/socket.h>
#include <sys/event.h>
#include <netdb.h>
#include <unistd.h>

#define BACKLOG 10
#define IRCPORT  6667
#define MAXEVENTS 64
#define MAXFD 256


#endif