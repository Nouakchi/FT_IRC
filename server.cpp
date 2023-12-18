/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:27:08 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/18 17:12:06 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int addCnction(int (*clients_fd)[MAXFD], int accepted_fd)
{
	int i = -1;

	if (accepted_fd < 0)
		return -1;
	while ((*clients_fd)[++i] != 0)
		break;
	if ((i + 1) == MAXFD)
		return -1;
	(*clients_fd)[i] = accepted_fd;
	return 0;
}

int delCnction(int (*clients_fd)[MAXFD], int accepted_fd)
{
	int i = -1;

	while ((*clients_fd)[++i] != 0)
}
void connect_Socket(int sfd, int kq, struct addrinfo** res_)
{
	struct addrinfo* res = *res_;
	struct kevent	evSet;
	struct kevent	evList[MAXEVENTS];
	int 			clients_fd[MAXFD];	
	int 			nbr_events;

	bzero(clients_fd, sizeof(clients_fd));
	while (1)
	{
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
				EV_SET(&evSet, discnct_fd, EVFILT_READ, EV_DELETE,0,0,NULL);
				kevent(kq, &evSet, 1, NULL, 0, NULL);
				// deleteCnction(fd);
				std::cout << "A client with fd:" << discnct_fd << " Disconnected";
			}
		}
	}
}

int setUpSocket(struct addrinfo **res)
{
	struct addrinfo hints;
	int l;

	memset(&hints,0,sizeof(hints));
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

	// kevent kv; 
	

	// while(true)
	// {
	// 	int accepted_fd = accept(sfd,res->ai_addr,&res->ai_addrlen);
	// 	if (accepted_fd != -1)
	// 	{
	// 		// handle the connection
	// 		// send() and recv()...
			
	// 		// send section 
	// 		/*{
	// 			size_t msgsent_len;
	// 			char *msg = "message";
	// 			msgsent_len = send(accepted_fd, msg,sizeof(msg), 0);
	// 			// evaluate msglen if needed
	// 		}*/
	// 		// recieve section 
	// 		/*{
	// 			size_t msgreaded_len;
	// 			char buffer[MSG_LENGTH];
	// 			msgreaded_len = recv(accepted_fd, buffer, sizeof(buffer), 0);
	// 			if (msgreaded_len == 0)
	// 				// this means the client has closed the connection so handle it.
	// 		}*/
	// 	}
	// 	else
	// 	{/* error ;*/}
	// 	// select();
	// }