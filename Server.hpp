/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:05:37 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/20 14:26:11 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"

class Server
{
private :
	int sfd;

	int kq;
	int nbr_ofEvents;

	int	clients_fd[MAXFD];
	struct addrinfo hints, *res;
	struct kevent	evSet;
	struct kevent	evList[MAXEVENTS];

	// std::istream ifs;
	
	void	setUpsocket();
	void	setUpserver();

	int addcnction(int fd);
	int delcnction(int fd);

	void sendToClient(int fd, std::string data);
	void recvFromClient(int fd);

	int	errflag;

public :
	Server();

	void	runServer();

	~Server();
};

#endif