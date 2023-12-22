/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:22:27 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/22 22:38:23 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	bzero(clients_fd,sizeof(clients_fd));
	bzero(&hints,sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	// hints.ai_flags = AI_PASSIVE;
	
}

Server::~Server()
{
	std::cout << "Server has turnedOFF" << std::endl;
}

void	Server::setUpsocket()
{
	int ad = getaddrinfo("0.0.0.0", "6667",&this->hints, &this->res);
	// if (ad)
	this->sfd =  socket(PF_INET, SOCK_STREAM, 0);

	int reuse = 1;
	setsockopt(this->sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	
	int b = bind(this->sfd, this->res->ai_addr, this->res->ai_addrlen);

	int l = listen(this->sfd,BACKLOG);
	fcntl(sfd, F_SETFL, O_NONBLOCK);
}

void Server::Authenticate_cnction(int fd, Client& clnt)
{
	if (clnt.AuthFlag)
		return; // already authentified
	char buff[512];
	recv(fd, buff,sizeof(buff), 0);
	std::string cmd(buff);
	size_t pos = cmd.find_first_not_of("PASS") + 1;
	size_t passwdlen = cmd.length() - pos;
	// pos = cmd.find_first_not_of(" ", pos);
	if (cmd.substr(pos, passwdlen) != this->passwd);
		
}

void	Server::setUpserver()
{
	this->kq = kqueue();
	EV_SET(&this->evSet, this->sfd, EVFILT_READ, EV_ADD, 0, 0, NULL);
	kevent(this->kq, &this->evSet, 1, NULL, 0, NULL);
}

int Server::addcnction(int fd)
{
	int i = -1;
	if (fd < 0)
		return -1;
	while (clients_fd[++i] != 0);
	if ((i + 1) == MAXFD)
		return -1;
	clients_fd[i] = fd;
	return 0;
}

int Server::delcnction(int fd)
{
	int i = -1;
	while (clients_fd[++i] != fd);
	clients_fd[i] = 0;
	close(fd);
	return 0;
}

void	Server::replay(int fd, std::string data)
{
	send(fd, data.c_str(), data.size(), 0);
}

void Server::recvFromClient(int fd)
{
	char buff[1024];
	bzero(buff, sizeof(buff));
	int recvdbytes;
	// if (clients)
	// recvdbytes = recv(fd,buff, sizeof(buff), 0);

	while (true)
	{
		recvdbytes = recv(fd,buff, sizeof(buff), 0);
		if (recvdbytes <= 0)
			break;
		clientInput.append(buff, recvdbytes);
	}
	std::cout << clientInput ;
	clientInput.clear();
}

void	Server::runServer()
{
	std::cout << "the Server is listening on 127.0.0.1:6667. Enjoy ;)\n";
	setUpsocket();
	setUpserver();
	while (1)
	{
		this->nbr_ofEvents = kevent(this->kq, NULL, 0, evList, MAXEVENTS, NULL);
		for (int i = 0; i < nbr_ofEvents; i++)
		{
			if (evList[i].ident == sfd) // new connection is availble
			{
				// int afd = accept(this->sfd, NULL, NULL);
				int afd = accept(this->sfd, res->ai_addr, &res->ai_addrlen);
				if (addcnction(afd) == 0)
				{
					EV_SET(&this->evSet,afd, EVFILT_READ, EV_ADD, 0, 0, NULL);
					kevent(this->kq, &this->evSet, 1, NULL, 0, NULL);
					replay(afd,"password: ");
					std::cout << "Client with fd:"<< afd<< " connected " << std::endl;
				}
				// while (true)
				// {
					// if (evList[i].filter & EVFILT_READ)
					// {
						// read from user 
					// }
					// if(Authentified)
						//break the loop and connect
				// }
			}
			else if (evList[i].flags & EV_EOF) // the client send EOF (disconnection) (so delete the cnction)
			{
				int dfd = evList[i].ident;
				EV_SET(&this->evSet, dfd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
				kevent(this->kq, &this->evSet, 1, NULL, 0, NULL);
				delcnction(dfd);
				std::cout << "A client with fd:" << dfd << " Disconnected" << std::endl;
			}
			else if (evList[i].flags & EVFILT_READ) // the client sent data and its ready to read
				recvFromClient(evList[i].ident);
		}
	}
}
