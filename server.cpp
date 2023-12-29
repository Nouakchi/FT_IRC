/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:22:27 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/28 06:55:59 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
	: hostname(":")
{
	// bzero(clients_fd,sizeof(clients_fd));
	bzero(&hints,sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	// hints.ai_flags = AI_PASSIVE;

	this->creation_time = displayTimestamp();

	passwd = "123";
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

void	Server::setUpserver()
{
	this->kq = kqueue();
	EV_SET(&this->evSet, this->sfd, EVFILT_READ, EV_ADD, 0, 0, NULL);
	kevent(this->kq, &this->evSet, 1, NULL, 0, NULL);

	char hostnm[256];
	gethostname(hostnm, sizeof(hostnm));
	hostname.append(hostnm);
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
				int afd = accept(this->sfd, res->ai_addr, &res->ai_addrlen);
					EV_SET(&this->evSet,afd, EVFILT_READ, EV_ADD, 0, 0, NULL);
					kevent(this->kq, &this->evSet, 1, NULL, 0, NULL);
					
					std::cout << "Client with fd:"<< afd << " connected " << std::endl;
			}
			else if (evList[i].flags & EV_EOF) // the client send EOF (disconnection) (so delete the cnction)
			{
				int dfd = evList[i].ident;
				EV_SET(&this->evSet, dfd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
				kevent(this->kq, &this->evSet, 1, NULL, 0, NULL);
				std::cout << "A client with fd:" << dfd << " Disconnected" << std::endl;
			}
			else if (evList[i].flags & EVFILT_READ) // the client sent data and its ready to read
				recvFromClient(evList[i].ident);
			// else if (evList[i].flags & EVFILT_WRITE) // the client is ready to write
			// 	std::cout << "Client with fd:" << evList[i].ident << " is ready to write" << std::endl;
		}
	}
}



void Server::Authenticate_cnction(Client& clnt, std::vector<std::string> cmd)
{
	if ((cmd[0] == "PASS")&& (clnt.AuthFlag == 1 || clnt.AuthFlag == 0))
		processPass(clnt, cmd);
	else if (cmd[0] == "NICK" && clnt.AuthFlag > 0)
		processNick(clnt, cmd);
	else if (cmd[0] == "USER" && clnt.AuthFlag > 0)
		processUser(clnt, cmd);
	else // not registred Yet
		error_replay(ERR_NOTREGISTERED, clnt, ":Unauthorized command (already registered)\r\n");

	std::cout << "Auth flag : " << clnt.AuthFlag << std::endl;

	if (clnt.AuthFlag == 3
		&& !clnt.nickName.empty()
		&& !clnt.userName.empty())
	{
		checkAuth(clnt);
		if (clnt.AuthFlag == 3)
			wlcmMsg(clnt);
	}
}

void Server::recvFromClient(int fd)
{
	std::string Input;
	std::string tosend;
	int recvdbytes;

	clnt.sfd = fd;

	while (true)
	{
		char buff[512];
		recvdbytes = recv(fd,buff, sizeof(buff), 0);
		if (recvdbytes< 0)
			break;

		Input.append(buff, recvdbytes);

		if (Input.find("\n")!= std::string::npos)
		{	
			Input.pop_back();
			if (Input.find("\r")!= std::string::npos)
			{
				Input.pop_back();
				break;
			}
			break;
		}
	}
	std::cout << Input << std::endl<< std::endl;
	

	if (clnt.AuthFlag == 3)
	{
		//already AUthentified //execute any cmd except PASSS/USER(ERR_AlreadyRegistred) ;
		std::cout << Input << std::endl;
		Input.clear();
		return;
	}

	// Authentification
	std::vector<std::string> cmd;
	splitString(Input, cmd);
	Input.clear();

	Authenticate_cnction(clnt, cmd);
}