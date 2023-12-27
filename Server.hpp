/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:05:37 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/27 02:52:41 by aaoutem-         ###   ########.fr       */
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
	std::string creation_time;

	std::vector<Client> clnts;
	Client clnt;

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

	void Authenticate_cnction(Client& clnt, std::vector<std::string> cmd);
	int processPass(Client& clnt, std::vector<std::string>& cmd);
	int processNick(Client& clnt, std::vector<std::string>& cmd);
	int processUser(Client& clnt, std::vector<std::string>& cmd);
	void checkAuth(Client& clnt);
	void wlcmMsg(Client clnt);

	int  errflag;
	void error_replay(int errNbr, Client& clnt, std::string err);

public :
	Server();
	void	runServer();
	~Server();
};

#endif