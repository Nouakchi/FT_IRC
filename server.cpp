/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:27:08 by aaoutem-          #+#    #+#             */
/*   Updated: 2023/12/16 12:42:33 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

void	setupServer()
{
	struct sockaddr ServerAddress;
	struct addrinfo *res, hints;
	int l;

	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	// hints.ai_flags = AI_PASSIVE;
	int status = getaddrinfo("127.0.0.1", "6667", &hints, &res);
	int sfd = socket(PF_INET, SOCK_STREAM, 0);
	ServerAddress.sa_family = PF_INET;
	l = listen(sfd, BACKLOG);
	int b = bind(sfd, res->ai_addr, res->ai_addrlen);
		while(true)
	{
		int accepted_fd = accept(sfd,res->ai_addr,&res->ai_addrlen);
		if (accepted_fd != -1)
		{
			// handle the connection
		}
		else
		{/* error ;*/}
	}
	// int n = connect (sfd, &ServerAddress, sizeof(ServerAddress)); 
}
