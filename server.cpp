/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 10:22:27 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/24 09:08:52 by aaoutem-         ###   ########.fr       */
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
		// if (buff.find_last_of("\r\n") == std::string::npos);
		// break;
		if (recvdbytes <= 0)
			break;
		clientInput.append(buff, recvdbytes);
	}
	std::cout << clientInput ;
	clientInput.clear();
}

void Server::Authenticate_cnction(int fd, Client& clnt)
{
	return ;
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

					replay(afd, hostname + " Welcome to the Internet Relay Network ");
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

bool valid_nickname(std::string nickname)
{
	std::string special_set = "-|[]|\\`^{}";

	if (nickname.empty() || isdigit(nickname[0]))
		return false;
	for (int i = 0; i < nickname.length(); i++)
		if (!isalnum(nickname[i]) && (special_set.find(nickname[i]) == std::string::npos))
			return false;
	return true;
}

void splitcmd(std::string &cmd, std::vector<std::string>& vct)
{
	std::istringstream iss(cmd);
	std::string			param;

	while (std::getline(iss, param, ' '))
	{
		if (param[0] == ':')
		{
			std::string realnm;
			std::getline(iss, realnm, '\n');
			vct.push_back(param.substr(1) + " " + realnm);
		}
		else
			vct.push_back(param);
	}
}
void user_cmd(std::string Input, Client clnt)
{
	std::vector<std::string> params;
	splitcmd(Input, params);
	if (params.size() != 5)
		return ; // error 
	clnt.userName = params[1];
	clnt.realName = params[4];
}

void Server::Authenticate_cnction(int fd, Client& clnt)
{
	// if (clnt.AuthFlag == 2)
	// 	return; // already authentified
	char buff[512];
	std::string Input;
	std::string tosend;
	int recvdbytes;
	
	while (true)
	{
		recvdbytes = recv(fd,buff, sizeof(buff), 0);
		if (recvdbytes <= 0)
			break;
		Input.append(buff, recvdbytes);
	}
	// std::cout << Input ;
	// Input.clear();
	if ((Input.substr(0, 4) == "PASS")
		 && (clnt.AuthFlag == 1 || clnt.AuthFlag == 0)){
		size_t pos = Input.find_first_not_of(" ", 4);
		if (pos == std::string::npos)
			return ; // this is an Error of Empty Param(only Spaces)
		std::string key = Input.substr(pos, Input.length() - pos);
		if (key == passwd)
			clnt.AuthFlag = 1;
		else
		{
			tosend = "incorrect password !!";
			send(clnt.sfd, tosend.c_str(), tosend.size(), 0);
		}
	}
	switch (clnt.AuthFlag)
	{
		case 1:
		{
			//NICK
			if (Input.substr(0, 4) == "NICK"){
				size_t pos = Input.find_first_not_of(" ", 4);
				if (pos == std::string::npos)
					return ; // this is an Error Empty Param(only Spaces)
				std::string nickname = Input.substr(pos, Input.length() - pos);
				if (valid_nickname(nickname)){
					clnt.nick = nickname;
					clnt.AuthFlag = 2;
				}
				else{
					tosend = "enter A valid NICKname"; 
					send(clnt.sfd, tosend.c_str(), tosend.size(), 0);
				}
			}
			else{
				tosend = "to Authenticate you should enter a valid nickname";
				send(clnt.sfd, tosend.c_str(), tosend.size(), 0);
			}
			break;
		}
		case 2:
		{
			//USER
			user_cmd(Input);
			clnt.AuthFlag = 3;
			break;
		}
		case 3:
		{
			// After Authentication, its time to execute some COMMANDS
			std::cout << Input << std::endl;
		}
		default:
		{
			// nothig to do before Authentication 
			break;
		}
	}
	
}