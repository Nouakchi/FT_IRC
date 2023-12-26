/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:04:10 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/26 01:00:55 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
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
            //   "Welcome to the Internet Relay Network
            //    <nick>!<user>@<host>"

            //   "Your host is <servername>, running version <ver>"
            //   "This server was created <date>"
enum Replies
{
	RPL_WELCOME  = 001, 
	RPL_YOURHOST = 002,
	RPL_CREATED  = 003,
	ERR_ERRONEUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,
 	ERR_NEEDMOREPARAMS = 461,
	ERR_ALREADYREGISTRED = 462,
	ERR_PASSWDMISMATCH = 464
};

void		splitString(const std::string& input, std::vector<std::string>& tokens);
std::string	skipSpaces(std::string input);

bool		valid_nickname(std::string nickname);
bool		nickInUse(std::string nickname);
std::string    displayTimestamp();

#endif