/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:27:08 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/19 13:37:37 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int addCnction(int (*clients_fd)[MAXFD], int accepted_fd)
{
	int i = -1;

	if (accepted_fd < 0)
		return -1;
	while ((*clients_fd)[++i] != 0)
		;
	if ((i + 1) == MAXFD)
		return -1;
	(*clients_fd)[i] = accepted_fd;
	return 0;
}

int delCnction(int (*clients_fd)[MAXFD], int accepted_fd)
{
	int i = -1;
	
	while ((*clients_fd)[++i] != accepted_fd)
		;
	(*clients_fd)[i] = 0;
	return 0;
}

void sendToClient(int accepted_fd)
{
	std::string	buff = "U welcome asat\nTaaaalk to mee\n";
	send(accepted_fd, buff.c_str(), buff.size(), 0);
}

void recvMsgFromClient(int fd)
{
	char buf[1024];
	int read = recv(fd, buf, sizeof(buf) - 1, 0);
	buf[read] = '\0';
	std::cout << buf;
}

void connect_Socket(int sfd, int kq, struct addrinfo** res_)
{
	struct addrinfo* res = *res_;
	struct kevent	evSet;
	struct kevent	evList[MAXEVENTS];
	int 			clients_fd[MAXFD];
	int 			nbr_events;

	bzero(clients_fd, sizeof(clients_fd));
	while (1) {
		nbr_events = kevent(kq, NULL, 0, evList, MAXEVENTS, NULL);
		for (int i = 0; i < nbr_events; i++)
		{
			if (evList[i].ident == sfd)
			{
				int accepted_fd = accept(sfd,res->ai_addr,&res->ai_addrlen);
				if (addCnction(&clients_fd, accepted_fd) == 0)
				{
					EV_SET(&evSet, accepted_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
					kevent(kq, &evSet, 1, NULL, 0, NULL);
					std::cout << "A client with fd:" << accepted_fd << " Connected" << std::endl;
					sendToClient(accepted_fd);
				}
				else
				{
					std::cout << "Connection refused" << std::endl; 
					close(accepted_fd);
				}
			}
			else if (evList[i].flags & EV_EOF)
			{
				int discnct_fd = evList[i].ident;
				EV_SET(&evSet, discnct_fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
				kevent(kq, &evSet, 1, NULL, 0, NULL);
				delCnction(&clients_fd, discnct_fd);
				close(evList[i].ident);
				std::cout << "A client with fd:" << discnct_fd << " Disconnected" << std::endl;
			}
			else if (evList[i].flags & EVFILT_READ )
				recvMsgFromClient(evList[i].ident);
		}
	}
}

int setUpSocket(struct addrinfo **res)
{
	struct addrinfo hints;
	int l;

	bzero(&hints,sizeof(hints));
	hints.ai_family = PF_UNSPEC; // ipv4 or ipv6 
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //

	int status = getaddrinfo("127.0.0.1", "6667", &hints, res);

	int sfd = socket(PF_INET, SOCK_STREAM, 0);

	int b = bind(sfd, (*res)->ai_addr, (*res)->ai_addrlen);

	l = listen(sfd, BACKLOG);

	return (sfd);
}

void	setupServer()
{
	int sfd;
	struct addrinfo *res;
	struct kevent	evSet;

	sfd = setUpSocket(&res);
	int kq = kqueue();
	EV_SET(&evSet, sfd, EVFILT_READ, EV_ADD, 0, 0, NULL);
	kevent(kq, &evSet, 1, NULL, 0, NULL);
	connect_Socket(sfd, kq, &res);
}

int main()
{
	setupServer();
}

