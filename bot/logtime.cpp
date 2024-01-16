/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logtime.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:37:07 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/07 15:22:10 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.h"

void    loggedTime( t_server *server, Client *clnt )
{
	std::time_t jointime = clnt->getclntsrvrJointime();
	std::time_t currenttime = std::time(NULL);
	std::time_t difftime =  currenttime - jointime;
	
	int days = difftime / 86400;
	int restSeconds = difftime % 86400; 
	int hours = restSeconds / 3600;
	int minutes = (restSeconds % 3600) / 60;
	int seconds = restSeconds % 60;
	
	std::string logtime = "Logtime: " + std::to_string(days) + " days "
		+ std::to_string(hours) +":"+ std::to_string(minutes) +":"+ std::to_string(seconds);

	error_replay(server, 1, *clnt, logtime);
}