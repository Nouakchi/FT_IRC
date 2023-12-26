/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:22:27 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/26 03:08:43 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
	: hostname(":")
{
	bzero(clients_fd,sizeof(clients_fd));
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
					
					std::cout << "Client with fd:"<< afd << " connected " << std::endl;

					// replay(afd, hostname + " Welcome to the Internet Relay Network ");
				}
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

int main()
{
	Server srvr;
	srvr.runServer();
	return (0);
}

void Server::Authenticate_cnction(Client& clnt, std::vector<std::string> cmd)
{
	if ((cmd[0] == "PASS")
		 && (clnt.AuthFlag == 1 || clnt.AuthFlag == 0)){
		if (cmd.size() != 2)
		{
			error_replay(ERR_NEEDMOREPARAMS, clnt, " PASS :Not enough parametres\r\n");
			return ;
		}
		std::cout  << "lok am here " << std::endl;
		clnt.AuthFlag = 1;
		clnt.clnt_entred_passwd = cmd[1];
	}
	else if (cmd[0] == "NICK"
			 && clnt.AuthFlag > 0){
		if (cmd.size() != 2){
			error_replay(ERR_NEEDMOREPARAMS, clnt, " NICK :Not enough parametres\r\n");
			return ;
		}
		else {
			clnt.nickName = cmd[1];
			if (clnt.AuthFlag < 2)
				clnt.AuthFlag++ ;
		}
	}
	else if (cmd[0] == "USER"
			 && clnt.AuthFlag > 0){
		//USER
		if (cmd.size() != 5){
			error_replay(ERR_NEEDMOREPARAMS, clnt, " USER :Not enough parametres\r\n");
			return ;
		}
		// user_cmd(cmd);
		if (clnt.AuthFlag < 3)
		{
			clnt.AuthFlag++ ;
			std::cout  << "lok am here " << std::endl;
		}
	}

	if (clnt.AuthFlag == 3
		&& !clnt.nickName.empty()
		&& !clnt.userName.empty())
	{
			std::cout << "AUTHENT" << std::endl;
		// checkAuth(clnt);
		// if (clnt.AuthFlag == 3)
		// wlcmMsg(clnt);
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
		// if (buff.find_last_of("\r\n") != std::string::npos);
		// break;
		if (recvdbytes <= 0)
			break;
		Input.append(buff, recvdbytes);
	}
	

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