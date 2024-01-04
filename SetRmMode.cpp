/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SetRmMode.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaoutem- <aaoutem-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:38:23 by aaoutem-          #+#    #+#             */
/*   Updated: 2024/01/04 15:35:33 by aaoutem-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/irc.h"

void	SetMode( t_server *server, Client *clnt, std::vector<std::string>& cmd )
{
	std::string chnlName = cmd[1];

	int i = -1;
	while (++i < cmd[2].length())
	{
		if (cmd[2][i] == 'i')
			server->channels[chnlName]->i = true;
		else if (cmd[2][i] == 't')
			server->channels[chnlName]->t = true;
		else if (cmd[2][i] == 'k')
		{
			if (cmd.size() == 4)
				server->channels[chnlName]->k = cmd[3];
			else
				return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
		}
		else if (cmd[2][i] == 'o')
			;
		else if (cmd[2][i] == 'l')
		{
			if (cmd.size() == 4 && (cmd[3].find_first_not_of("0123456789") == std::string::npos))
				server->channels[chnlName]->l = atoi(cmd[3].c_str());
			else // not a valid arguement
				return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
		}
	}
}

void	RmMode(t_server *server, Client *clnt, std::vector<std::string>& cmd)
{
	std::string chnlName = cmd[1];


	// after setting a MODE succefully i reply with (:irc.server.com 324 <your_nick> #channel -k)
	int i = -1;
	if (cmd[2][0] == 'k')
	{
		if (cmd.size() == 3)
			server->channels[chnlName]->k = "";
		else
			return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
	}
	else if (cmd[2][0] == 'o')
		;
	else if (cmd[2][0] == 'l')
	{
		if (cmd.size() == 4 && (cmd[3].find_first_not_of("0123456789") == std::string::npos))
			server->channels[chnlName]->l = atoi(cmd[3].c_str());
		else // not a valid arguement
			return(error_replay(server, ERR_NEEDMOREPARAMS, *clnt, "MODE :Not enough parameters\r\n"));
	}
	while (++i < cmd[2].length())
	{
		if (cmd[2][i] == 'i')
			server->channels[chnlName]->i = false;
		else if (cmd[2][i] == 't')
			server->channels[chnlName]->t = false;
	}
}
