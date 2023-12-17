/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:27:08 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/16 15:37:27 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	setupServer()
{
	struct sockaddr ServerAddress;
	struct addrinfo *res, hints;
	int l;

	memset(&hints,0,sizeof(hints));
	// hints.ai_family = AF_INET;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	// hints.ai_flags = AI_PASSIVE;

	int status = getaddrinfo("127.0.0.1", "6667", &hints, &res);

	int sfd = socket(PF_INET, SOCK_STREAM, 0);

	int b = bind(sfd, res->ai_addr, res->ai_addrlen);

	l = listen(sfd, BACKLOG);

	while(true)
	{
		int accepted_fd = accept(sfd,res->ai_addr,&res->ai_addrlen);
		if (accepted_fd != -1)
		{
			// handle the connection
			// send() and recv()...
			
			// send section 
			/*{
				size_t msgsent_len;
				char *msg = "message";
				msgsent_len = send(accepted_fd, msg,sizeof(msg), 0);
				// evaluate msglen if needed
			}*/
			// recieve section 
			/*{
				size_t msgreaded_len;
				char buffer[MSG_LENGTH];
				msgreaded_len = recv(accepted_fd, buffer, sizeof(buffer), 0);
				if (msgreaded_len == 0)
					// this means the client has closed the connection so handle it.
			}*/
		}
		else
		{/* error ;*/}
	}
	// int n = connect (sfd, &ServerAddress, sizeof(ServerAddress)); 
}
 void f(){}

 int main()
 {
	int f;
	f();
 }