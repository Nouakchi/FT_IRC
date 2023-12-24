/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:05:37 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/23 22:51:48 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"
#include "IRCEntities/client.hpp"

class Server
{
private :
	std::string passwd;
	std::string hostname;
	std::string clientInput;

	int sfd;

	int kq;
	int nbr_ofEvents;

	int	clients_fd[MAXFD];
	struct addrinfo hints, *res;
	struct kevent	evSet;
	struct kevent	evList[MAXEVENTS];

	// std::map<int, Client> clients;

	void	setUpsocket();
	void	setUpserver();

	int addcnction(int fd);
	int delcnction(int fd);

	void replay(int fd, std::string data);
	void recvFromClient(int fd);
	void Authenticate_cnction(int fd, Client& clnt);

	int	errflag;

public :
	Server();
	void	runServer();
	~Server();
};

#endif